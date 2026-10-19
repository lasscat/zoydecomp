"""Restricted ARM interpreter for bounded behavior evidence, not a DS emulator.

Only explicitly implemented ARM operations are supported. Unknown instructions,
unaligned accesses, privileged effects and unmapped accesses abort the check.
No target instructions/bytes are embedded here; callers supply a legal ROM slice.
"""
from dataclasses import dataclass


class Unsupported(ValueError):
    pass


@dataclass
class Region:
    base: int
    data: bytearray
    writable: bool


class Arm:
    def __init__(self, regions):
        self.regions = regions
        self.r = [0] * 16
        self.n = self.z = self.c = self.v = False

    def region(self, address):
        if address & 3:
            raise Unsupported('unaligned access')
        for region in self.regions:
            if region.base <= address and address + 4 <= region.base + len(region.data):
                return region
        raise Unsupported(f'unmapped address {address:#x}')

    def load(self, address):
        region = self.region(address)
        off = address - region.base
        return int.from_bytes(region.data[off:off + 4], 'little')

    def store(self, address, value):
        region = self.region(address)
        if not region.writable:
            raise Unsupported('write to readonly input')
        off = address - region.base
        region.data[off:off + 4] = (value & 0xffffffff).to_bytes(4, 'little')

    def reg(self, index):
        return self.r[15] + 8 if index == 15 else self.r[index]

    def condition(self, cond):
        values = [self.z, not self.z, self.c, not self.c, self.n, not self.n,
                  self.v, not self.v, self.c and not self.z, not self.c or self.z,
                  self.n == self.v, self.n != self.v,
                  not self.z and self.n == self.v, self.z or self.n != self.v, True]
        if cond >= len(values):
            raise Unsupported('unconditional-extension instruction')
        return values[cond]

    def cmp(self, a, b):
        result = (a - b) & 0xffffffff
        self.n, self.z, self.c = bool(result & 0x80000000), result == 0, a >= b
        self.v = bool((a ^ b) & (a ^ result) & 0x80000000)

    def set_logic_flags(self, result):
        # Logical/test result flags. The shifter carry out is not modelled; V is
        # left unchanged, matching the subset needed by the checked functions.
        result &= 0xffffffff
        self.n, self.z = bool(result & 0x80000000), result == 0

    def set_add_flags(self, a, b, result):
        result &= 0xffffffff
        self.n, self.z = bool(result & 0x80000000), result == 0
        self.c = (a + b) > 0xffffffff
        self.v = bool((~(a ^ b) & (a ^ result)) & 0x80000000)

    def operand2(self, instruction):
        if instruction & (1 << 25):
            value, rotate = instruction & 255, ((instruction >> 8) & 15) * 2
            return ((value >> rotate) | (value << ((32 - rotate) & 31))) & 0xffffffff
        if instruction & (1 << 4):
            raise Unsupported('register-controlled shift')
        value = self.reg(instruction & 15)
        amount, kind = (instruction >> 7) & 31, (instruction >> 5) & 3
        if kind == 0:
            return (value << amount) & 0xffffffff
        if kind == 1:
            return value >> amount if amount else 0
        raise Unsupported('ASR/ROR operand not implemented')

    def step(self):
        pc = self.r[15]
        instruction = self.load(pc)
        next_pc = pc + 4
        if not self.condition(instruction >> 28):
            self.r[15] = next_pc
            return
        if instruction & 0x0ffffff0 == 0x012fff10:
            target = self.reg(instruction & 15)
            if target & 3:
                raise Unsupported('Thumb interworking not implemented by this bounded harness')
            next_pc = target
        elif instruction & 0x0e000000 == 0x0a000000:
            if instruction & (1 << 24):
                raise Unsupported('nested BL call outside bounded harness')
            offset = instruction & 0xffffff
            if offset & 0x800000:
                offset -= 1 << 24
            next_pc = pc + 8 + offset * 4
        elif instruction & 0x0fc000f0 == 0x00000090:
            if instruction & (1 << 20):
                raise Unsupported('multiply flags unsupported')
            dest, accumulate = (instruction >> 16) & 15, (instruction >> 12) & 15
            value = self.reg(instruction & 15) * self.reg((instruction >> 8) & 15)
            if instruction & (1 << 21):
                value += self.reg(accumulate)
            if dest == 15:
                raise Unsupported('multiply to PC')
            self.r[dest] = value & 0xffffffff
        elif instruction & 0x0c000000 == 0x04000000:
            if instruction & ((1 << 25) | (1 << 22)):
                raise Unsupported('register-offset/byte transfer unsupported')
            base, dest = (instruction >> 16) & 15, (instruction >> 12) & 15
            address = self.reg(base)
            offset = instruction & 0xfff
            updated = address + (offset if instruction & (1 << 23) else -offset)
            pre = bool(instruction & (1 << 24))
            effective = updated if pre else address
            if instruction & (1 << 20):
                value = self.load(effective)
                if dest == 15:
                    next_pc = value
                else:
                    self.r[dest] = value
            else:
                self.store(effective, self.reg(dest))
            if not pre or instruction & (1 << 21):
                if base == 15:
                    raise Unsupported('writeback to PC')
                self.r[base] = updated & 0xffffffff
        elif instruction & 0x0e000000 == 0x08000000:
            if instruction & (1 << 22):
                raise Unsupported('privileged block transfer')
            base = (instruction >> 16) & 15
            registers = [i for i in range(16) if instruction & (1 << i)]
            if base != 13 or not registers:
                raise Unsupported('only stack block transfers supported')
            up, pre = bool(instruction & (1 << 23)), bool(instruction & (1 << 24))
            start = self.r[base] + (4 if pre else 0) if up else self.r[base] - len(registers) * 4 + (0 if pre else 4)
            for index, register in enumerate(registers):
                address = start + index * 4
                if instruction & (1 << 20):
                    value = self.load(address)
                    if register == 15:
                        next_pc = value
                    else:
                        self.r[register] = value
                else:
                    self.store(address, self.reg(register))
            if instruction & (1 << 21):
                self.r[base] += len(registers) * (4 if up else -4)
        elif instruction & 0x0c000000 == 0:
            opcode, dest, base = (instruction >> 21) & 15, (instruction >> 12) & 15, (instruction >> 16) & 15
            value, left = self.operand2(instruction), self.reg(base)
            sets_flags = bool(instruction & (1 << 20))
            if opcode == 8:
                self.set_logic_flags(left & value)
            elif opcode == 10:
                self.cmp(left, value)
            elif opcode in (9, 11):
                raise Unsupported('TEQ/CMN not implemented')
            else:
                if opcode == 0:
                    result = left & value
                elif opcode == 1:
                    result = left ^ value
                elif opcode == 2:
                    result = left - value
                elif opcode == 4:
                    result = left + value
                elif opcode == 12:
                    result = left | value
                elif opcode == 13:
                    result = value
                elif opcode == 14:
                    result = left & (~value & 0xffffffff)
                else:
                    raise Unsupported('unimplemented data-processing opcode')
                if sets_flags:
                    if opcode == 2:
                        self.cmp(left, value)
                    elif opcode == 4:
                        self.set_add_flags(left, value, result)
                    else:
                        self.set_logic_flags(result)
                if dest == 15:
                    raise Unsupported('computed PC write outside bounded subset')
                self.r[dest] = result & 0xffffffff
        else:
            raise Unsupported(f'unsupported ARM instruction at {pc:#x}')
        self.r[15] = next_pc & 0xffffffff

    def run(self, stop, limit=10000):
        for count in range(limit):
            if self.r[15] == stop:
                return count
            self.step()
        raise Unsupported('instruction limit exceeded')

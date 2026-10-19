"""Bounded research-only ARM immediate BL; not a DS hardware/full CPU model."""
from arm_subset import Arm, Unsupported


class ArmCallCluster(Arm):
    VERSION = 'bounded-arm-immediate-bl-v1'

    def __init__(self, regions, call_edges):
        super().__init__(regions)
        self.call_edges = dict(call_edges)

    def step(self):
        pc = self.r[15]
        instruction = self.load(pc)
        cond = instruction >> 28
        branch = instruction & 0x0e000000 == 0x0a000000
        link = bool(instruction & (1 << 24))
        if branch and cond == 15:
            raise Unsupported(f'BLX/cond=1111 branch unsupported at {pc:#x}')
        if not (branch and link):
            return super().step()
        if not self.condition(cond):
            self.r[15] = (pc + 4) & 0xffffffff
            return
        immediate = instruction & 0xffffff
        if immediate & 0x800000:
            immediate -= 1 << 24
        target = (pc + 8 + immediate * 4) & 0xffffffff
        if self.call_edges.get(pc) != target:
            raise Unsupported(f'undeclared BL edge {pc:#x}->{target:#x}')
        self.load(target)
        self.r[14] = (pc + 4) & 0xffffffff
        self.r[15] = target

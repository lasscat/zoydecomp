"""Synthetic instruction fixtures only; no reconstructed instruction arrays."""
import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
from arm_subset import Region, Unsupported
from arm_call_cluster import ArmCallCluster


def bl(pc, target, cond=14):
    displacement = (target - (pc + 8)) // 4
    if not -(1 << 23) <= displacement < (1 << 23):
        raise ValueError('fixture target outside BL range')
    return (cond << 28) | 0x0b000000 | (displacement & 0xffffff)


def code(base, words):
    return Region(base, bytearray(b''.join(word.to_bytes(4, 'little') for word in words)), False)


class ArmCallClusterTests(unittest.TestCase):
    def test_forward_and_backward_immediate_offsets(self):
        base = 0x1000
        for pc, target in [(base, base + 8), (base + 8, base)]:
            words = [0xe12fff1e] * 3
            words[(pc - base) // 4] = bl(pc, target)
            cpu = ArmCallCluster([code(base, words)], {pc: target})
            cpu.r[14], cpu.r[15] = 0xdead0000, pc
            cpu.step()
            self.assertEqual(cpu.r[15], target)
            self.assertEqual(cpu.r[14], pc + 4)

    def test_conditional_taken_and_not_taken_preserve_flags(self):
        base = 0x2000
        for taken in (False, True):
            cpu = ArmCallCluster([code(base, [bl(base, base + 8, cond=0),
                                              0xe1a00000, 0xe12fff1e])], {base: base + 8})
            cpu.r[15], cpu.r[14] = base, 0x77770000
            cpu.z, cpu.n, cpu.c, cpu.v = taken, True, False, True
            flags = (cpu.n, cpu.z, cpu.c, cpu.v)
            cpu.step()
            self.assertEqual(cpu.r[15], base + (8 if taken else 4))
            self.assertEqual(cpu.r[14], base + 4 if taken else 0x77770000)
            self.assertEqual((cpu.n, cpu.z, cpu.c, cpu.v), flags)

    def test_nested_bl_and_stack_returns(self):
        base = 0x3000
        region = code(base, [0xe92d4000, bl(base + 4, base + 0x10),
                             0xe8bd8000, 0xe1a00000, 0xe12fff1e])
        cpu = ArmCallCluster([region, Region(0x4000, bytearray(256), True)],
                             {base + 4: base + 0x10})
        cpu.r = [0x90000000 + i * 4 for i in range(16)]
        cpu.r[13], cpu.r[14], cpu.r[15] = 0x4080, 0x5000, base
        preserved = cpu.r[4:12]
        cpu.run(0x5000)
        self.assertEqual(cpu.r[4:12], preserved)
        self.assertEqual(cpu.r[13], 0x4080)

    def test_undeclared_and_unmapped_calls_fail_closed(self):
        for edges, words, message in [({}, [bl(0x6000, 0x6008), 0, 0], 'undeclared BL'),
                                      ({0x6000: 0x7000}, [bl(0x6000, 0x7000)], 'unmapped address')]:
            cpu = ArmCallCluster([code(0x6000, words)], edges)
            cpu.r[15] = 0x6000
            with self.assertRaisesRegex(Unsupported, message):
                cpu.step()

    def test_blx_immediate_fails_closed(self):
        cpu = ArmCallCluster([code(0x8000, [0xfa000000])], {})
        cpu.r[15] = 0x8000
        with self.assertRaisesRegex(Unsupported, 'BLX'):
            cpu.step()

    def test_register_blx_and_thumb_interworking_fail_closed(self):
        for instruction in (0xe12fff3e, 0xe12fff10):
            cpu = ArmCallCluster([code(0x9000, [instruction])], {})
            cpu.r[0], cpu.r[15] = 0x9005, 0x9000
            with self.assertRaises(Unsupported):
                cpu.step()


if __name__ == '__main__':
    unittest.main()

/*
 * arm9:02006b38  (12 bytes of code; the original's literal pool follows the
 * code and lies outside the recorded extent)
 *
 * Original:
 *   ldr  r1, [pc, #4]          ; r1 = 0x04000247
 *   strb r0, [r1]              ; *(volatile unsigned char *)0x04000247 = value
 *   bx   lr
 *
 * Writes one byte into the memory-mapped register block at 0x04000240. The
 * register's meaning is unknown; `volatile` states the hardware interpretation.
 */
void pvz_02006b38_leaf(unsigned char value)
{
    *(volatile unsigned char *)0x04000247u = value;
}

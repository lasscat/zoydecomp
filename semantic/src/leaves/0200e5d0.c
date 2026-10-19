/*
 * arm9:0200e5d0  (8 bytes)
 *
 *   ldr  r0, [pc]            ; returns the literal 0x02fffe00
 *   bx   lr
 *
 * Returns a fixed address (0x02fffe00) as a 32-bit value. The original
 * spends four of its eight bytes on a literal pool word; clang reaches the
 * same value with movw/movt, which needs two instructions and no pool.
 */
void *pvz_0200e5d0(void)
{
    return (void *)0x02fffe00;
}

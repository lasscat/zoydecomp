/*
 * arm9:02005684  (20 bytes)
 *
 *   lsl  r0, r0, #2
 *   add  r0, r0, #0x2f00000
 *   add  r0, r0, #0xff000
 *   ldr  r0, [r0, #0xda0]
 *   bx   lr
 *
 * Indexed 32-bit table read: effective address 0x02fff000 + 0xda0 +
 * index * 4. The original materialises the base with two add immediates
 * (ARM cannot encode 0x02fffda0 as a single immediate); clang uses
 * movw/movt or a constant plus indexed load instead.
 */
unsigned int pvz_02005684_leaf(unsigned int index)
{
    return *(const unsigned int *)(0x02fff000 + 0xda0 + index * 4);
}

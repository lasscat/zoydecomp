/*
 * arm9:02003ad8  (12 bytes)
 *
 *   ldr  r0, [pc, #4]        ; literal 0x020fd340
 *   ldrh r0, [r0, #0xa]      ; 16-bit field at +0x0a
 *   bx   lr
 *
 * Returns one unsigned 16-bit field of the fixed global record at
 * 0x020fd340. The record contents are unknown; the literal pool word the
 * original uses is shared with the surrounding tiny getters.
 */
struct Glob_020fd340 {
    unsigned char pad_0x00[0x0a];
    unsigned short field_0x0a;
};

unsigned short pvz_02003ad8(void)
{
    return ((const struct Glob_020fd340 *)0x020fd340)->field_0x0a;
}

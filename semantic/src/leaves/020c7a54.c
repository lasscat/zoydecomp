/* Unknown output setup: packs the four bytes at offset 0x0c of each non-empty
 * 0x30-byte record of the table at 0x021de340 into the 32-bit slot array at
 * 0x021de254, then marks the state word at 0x021de250 as done. Record identity
 * and field meanings are unknown; only the observed DS value effect is modeled.
 * Independently reconstructed from BWBE-r0 ARM9 0x020c7a54. */
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;

struct PvzPacked4 {
    u8 b0;
    u8 b1;
    u8 b2;
    u8 b3;
};

void pvz_020c7a54_leaf(void)
{
    u32 state = *(volatile u32 *)0x021de250u;
    u8 (*src)[0x30] = (u8 (*)[0x30])0x021de340u;
    u32 *dst = (u32 *)0x021de254u;
    u8 *slot = (u8 *)0x021de300u;
    u16 i;

    if ((state & 1u) == 0)
        return;
    if ((state & 0x40u) == 0 && (state & 4u) != 0) {
        for (i = 0; i < 2; i++) {
            if (slot[0xd0 + i] != 0) {
                struct PvzPacked4 packed;

                packed.b0 = src[i][0xc];
                packed.b1 = src[i][0xd];
                packed.b2 = src[i][0xe];
                packed.b3 = src[i][0xf];
                dst[i] = *(u32 *)&packed;
            }
        }
    }
    *(volatile u32 *)0x021de250u |= 0x40u;
}

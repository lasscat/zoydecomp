/* Copies two 16-byte records out of the 0x30-byte base table at 0x021de340 into
 * the 16-byte record array at 0x021de298 for the two slots whose per-slot byte
 * at 0x021de3d0 is non-zero, then marks the state word at 0x021de250 as done.
 * Field meanings and the state word identity are unknown; only the observed DS
 * value effect is modeled. Independently reconstructed from BWBE-r0 ARM9
 * 0x020c768c. */
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;

void pvz_020c768c_leaf(void)
{
    u32 state = *(volatile u32 *)0x021de250u;
    int i;

    if ((state & 1u) == 0)
        return;
    if ((state & 2u) == 0 && (state & 4u) != 0) {
        const u8 *base = (const u8 *)0x021de340u;
        u32 *dst = (u32 *)0x021de298u;
        const u8 *slot = (const u8 *)0x021de300u;

        for (i = 0; i < 2; i++) {
            if (slot[0xd0 + i] != 0) {
                u16 lo = *(const u16 *)(base + i * 0x30);
                u16 hi = *(const u16 *)(base + i * 0x30 + 2);

                dst[i * 4] = lo;
                dst[i * 4 + 1] = hi;
                dst[i * 4 + 2] = 0u;
                dst[i * 4 + 3] = 0u;
            }
        }
    }
    *(volatile u32 *)0x021de250u |= 2u;
}

/* arm9:0203de10 -- stores eight words into dst[0..7] from one pointer plus
 * seven word arguments (three in registers, five on the stack).  X: natural C
 * makes MWCC batch each load with its store and reuse r1/r2 (14 insns) while
 * the original loads all five stack values into r4-r6/ip/lr first (13 insns). */
typedef unsigned int u32;

void store_eight(u32 *dst, u32 a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7)
{
    dst[0] = a0;
    dst[1] = a1;
    dst[2] = a2;
    dst[3] = a3;
    dst[4] = a4;
    dst[5] = a5;
    dst[6] = a6;
    dst[7] = a7;
}

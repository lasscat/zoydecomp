/* arm9:0200c9c0  (24 bytes = 20 code + 4 byte pool)
 *
 *   ldr  ip, [pc, #0xc]     ; -> 0x020ff5e0, pool word inside the extent
 *   ldr  r0, [ip]
 *   cmp  r0, #1
 *   beq  self+4             ; spin again while the word reads 1
 *   bx   lr
 *
 * Empty busy-wait loop: it keeps re-reading the global flag word until it no
 * longer holds the value 1.
 *
 * Tier N: the address literal, the load, the comparison, the branch back and
 * the pool placement are all byte-exact; the only difference is the register
 * that holds the flag address.  The original loads it into ip, this compiler
 * picks r1 (and r0 for the loaded value, as the original does).  Four source
 * shapes were measured (do-while, while, for(;;)/break, a named pointer plus
 * a named value) and all of them produce r1, so the ip choice comes from the
 * backend's register allocation for this profile and is not reachable from
 * the C text.  Two instructions (8 bytes) differ, inside the near threshold.
 */
void pvz_0200c9c0_wait_not_one(void)
{
    do {
    } while (*(volatile unsigned int *)0x020ff5e0 == 1);
}

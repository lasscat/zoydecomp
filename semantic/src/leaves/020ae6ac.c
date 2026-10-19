/*
 * arm9:020ae6ac  (40 bytes, no literal pool)
 *
 * Original:
 *   ldr  r2, [r0, #0x2c]       ; low half of the record's 64-bit stamp
 *   ldr  r1, [r1, #0x10]       ; low half of the other stamp
 *   ldr  r0, [r0, #0x30]       ; high half of the record's stamp
 *   subs r1, r2, r1            ; 64-bit difference (r2 holds the borrow now)
 *   sbc  r2, r0, #0
 *   subs r1, r1, #0x12c        ; ... compared against 300
 *   mov  r0, #0
 *   sbcs r1, r2, r0
 *   movlt r0, #1               ; return (difference < 300)
 *   bx   lr
 *
 * Returns 1 when the signed 64-bit value formed by (record->field_0x30,
 * record->field_0x2c) minus the zero-extended 32-bit value other->field_0x10 is
 * less than 300, else 0. Field meanings are unknown.
 *
 * Measured: N - same 40-byte extent, one differing instruction (clang folds the
 * zero high half of the 64-bit constant 300 into `sbcs r1, r2, #0` where the
 * original materialised it in r0 first).
 */
unsigned int pvz_020ae6ac_leaf(const void *record, const void *other)
{
    long long stamp = (long long)((unsigned long long)
                                  *(const unsigned int *)((const char *)record + 0x30) << 32
                                  | *(const unsigned int *)((const char *)record + 0x2c));
    long long reference = *(const unsigned int *)((const char *)other + 0x10);

    return stamp - reference < 300;
}

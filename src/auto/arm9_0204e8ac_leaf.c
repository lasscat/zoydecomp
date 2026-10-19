/*
 * arm9:0204e8ac  (28 bytes, no literal pool)
 *
 * Original:
 *   mov  r2, #0
 *   str  r2, [r0]              ; +0x00 = 0
 *   str  r2, [r0, #4]          ; +0x04 = 0
 *   str  r2, [r0, #8]          ; +0x08 = 0
 *   str  r1, [r0, #0xc]        ; +0x0c = value
 *   str  r2, [r0, #0x10]       ; +0x10 = 0
 *   bx   lr
 *
 * Zero-initializes five 32-bit fields of a record and stores `value` at +0x0c.
 *
 * Note on the `volatile` qualifier: clang's scheduler moves the +0x0c store to
 * the front of the sequence unless the fields are volatile. `volatile` here
 * only pins the store order to the observed DS sequence. Record meaning is
 * unknown.
 */
void pvz_0204e8ac_leaf(volatile unsigned int *record, unsigned int value)
{
    record[0] = 0;
    record[1] = 0;
    record[2] = 0;
    record[3] = value;
    record[4] = 0;
}

/*
 * arm9:02044ca0  (20 bytes)
 *
 * Original:
 *   ldrb r1, [r0, #0x452]      ; r1 = record->field_0x452
 *   cmp  r1, #0
 *   moveq r1, #1
 *   strbeq r1, [r0, #0x452]    ; if field was zero: field = 1
 *   bx   lr
 *
 * Sets the byte at +0x452 to 1 when it is currently zero (a one-shot flag).
 * Field meaning is unknown.
 */
void pvz_02044ca0_leaf(void *record)
{
    unsigned char *flag = (unsigned char *)record + 0x452;

    if (*flag == 0) {
        *flag = 1;
    }
}

/* arm9:020b3540  (68 bytes = 64 code + 4 byte pool)
 *
 *   ldr  r2, [pc, #0x38]    ; -> 0x020e9a2c, pool word inside the extent
 *   mov  r1, #1
 *   mov  r3, #0             ; loop index / zero value
 *   str  r2, [r0]           ; vtable
 *   strb r1, [r0, #4]       ; flag = 1
 *   str  r3, [r0, #8]
 *   mov  r2, r3             ; zero
 *   do {
 *       add r1, r0, r3, lsl #2
 *       str r2, [r1, #0x0c]
 *       str r2, [r1, #0x14]
 *       str r2, [r1, #0x1c]
 *       r3++;
 *       str r2, [r1, #0x24]
 *   } while (r3 < 2);
 *   bx   lr
 *
 * Constructs the object: installs the vtable, sets the byte flag, clears the
 * word at +0x08 and zeroes the four two-word tables at +0x0c, +0x14, +0x1c
 * and +0x24.  The loop is a do-while body (there is no pre-test branch in the
 * original); the index is incremented after the third store and the fourth
 * store follows it.
 *
 * Tier N: the seven instructions from `mov r2, r3` onwards are byte-exact, but
 * this compiler emits `mov r3, #0` one slot later than the original, i.e. the
 * original order is
 *     ... mov r1, #1 / mov r3, #0 / str r2, [r0] ...
 * while the same six statements come out as
 *     ... mov r1, #1 / str r2, [r0] / mov r3, #0 ...
 * Undoing that single scheduling difference (the two instructions are
 * independent) would make the whole function exact.
 */
struct Obj_020b3540 {
    unsigned int vtable;      /* +0x00 */
    unsigned char flag;       /* +0x04 */
    unsigned char pad_05[3];  /* +0x05 */
    int field_0x08;           /* +0x08 */
    int table_a[2];           /* +0x0c */
    int table_b[2];           /* +0x14 */
    int table_c[2];           /* +0x1c */
    int table_d[2];           /* +0x24 */
};

void pvz_020b3540_init(struct Obj_020b3540 *obj)
{
    int i;

    obj->vtable = 0x020e9a2cu;
    obj->flag = 1;
    obj->field_0x08 = 0;
    i = 0;
    do {
        obj->table_a[i] = 0;
        obj->table_b[i] = 0;
        obj->table_c[i] = 0;
        obj->table_d[i] = 0;
        i++;
    } while (i < 2);
}

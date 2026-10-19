/*
 * arm9:02046658  (20 bytes)
 *
 *   ldr ip, [pc, #0xc]       ; literal 0x020e1640
 *   str ip, [r0]             ; field 0x00 = fixed tag
 *   stmib r0, {r1, r2}       ; fields 0x04/0x08 = arg1/arg2
 *   str r3, [r0, #0xc]       ; field 0x0c = arg3
 *   bx  lr
 *
 * Initialises a record from a fixed 32-bit tag (0x020e1640, probably the
 * address of a descriptor/vtable) plus three caller-supplied values in
 * ascending field order. The tag is loaded from the literal pool by the
 * original; clang materialises it with movw/movt.
 */
struct Record_02046658 {
    unsigned int field_0x00;
    unsigned int field_0x04;
    unsigned int field_0x08;
    unsigned int field_0x0c;
};

void pvz_02046658(struct Record_02046658 *record, unsigned int arg1,
                  unsigned int arg2, unsigned int arg3)
{
    record->field_0x00 = 0x020e1640;
    record->field_0x04 = arg1;
    record->field_0x08 = arg2;
    record->field_0x0c = arg3;
}

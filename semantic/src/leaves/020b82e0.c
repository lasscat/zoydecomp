/*
 * arm9:020b82e0  (24 bytes)  -- tier X (same size, 5 differing instructions)
 *
 * Original instructions:
 *   ldr   r3, [r0, #0xc]     ; old = record->field_0x0c
 *   mov   r2, #1
 *   str   r1, [r0, #8]       ; record->field_0x08 = value
 *   strb  r2, [r0, #4]       ; record->byte_0x04 = 1
 *   mov   r0, r3
 *   bx    lr
 *
 * Stores a value at +0x08, sets the "dirty/valid" byte at +0x04 and returns the
 * previous content of +0x0c.
 *
 * volatile keeps the original's load-before-store order; without it clang sinks
 * the load to the end and returns through the argument register (20 bytes). The
 * remaining mismatch is scheduling/allocation: clang materialises the constant
 * 1 late (between the two stores, into r1) and parks the old value in r2, while
 * the original materialises 1 up front in r2 and parks the old value in r3.
 */
struct Record_020b82e0 {
    unsigned int field_0x00;
    volatile unsigned char byte_0x04;
    unsigned char pad_0x05[0x03];
    volatile unsigned int field_0x08;
    volatile unsigned int field_0x0c;
};

unsigned int pvz_020b82e0(struct Record_020b82e0 *record, unsigned int value)
{
    unsigned int old = record->field_0x0c;

    record->field_0x08 = value;
    record->byte_0x04 = 1;
    return old;
}

/*
 * arm9:0202ca40  (20 bytes of code; the original's literal pool follows the
 * code and lies outside the recorded extent)
 *
 * Original:
 *   ldr  r2, [pc, #0xc]        ; r2 = 0x021037a8 (address of a global pointer)
 *   ldr  r2, [r2]              ; r2 = *0x021037a8 (the current object)
 *   str  r0, [r2, #0x2c]       ; object->field_0x2c = first
 *   str  r1, [r2, #0x28]       ; object->field_0x28 = second
 *   bx   lr
 *
 * Stores two 32-bit values into the object referenced by the global pointer at
 * 0x021037a8, in the order +0x2c then +0x28.
 *
 * Note on the `volatile` qualifier: clang's ARM scheduler swaps the two
 * independent stores (+0x28 first) unless they are volatile. `volatile` here
 * only pins the store order to the observed DS sequence; it does not model a
 * memory-mapped location. Field meanings are unknown.
 */
struct UnknownObject {
    unsigned char unknown_00_27[0x28];
    volatile unsigned int second;   /* +0x28 */
    volatile unsigned int first;    /* +0x2c */
};

void pvz_0202ca40_leaf(unsigned int first, unsigned int second)
{
    struct UnknownObject *object = *(struct UnknownObject **)0x021037a8u;

    object->first = first;
    object->second = second;
}

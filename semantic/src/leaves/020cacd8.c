/* arm9:020cacd8
 * Reports whether the 32-bit field at +0x10 of the global object at
 * 0x021DE53C is non-zero.  The object address comes from a literal pool in
 * the original (its pool word sits in the gap after bx lr); clang loads the
 * base plus offset the same way but omits the original's moveq r0,#0 because
 * it already knows r0 is zero on that path, and keeps its pool word inside
 * .text, so sizes still agree at 24 bytes and only 4 instructions differ.
 */
int object_field_is_set(void)
{
    return *(volatile unsigned int *)(0x021DE53Cu + 0x10u) != 0;
}

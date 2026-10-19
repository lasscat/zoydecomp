/* arm9:020c5a90
 * Getter for the 32-bit field at +0x1c of the global object at 0x021DB040.
 * The object address comes from a literal pool in the original, whose pool
 * word lives in the inter-function gap after bx lr; clang keeps its own pool
 * word inside .text, so the emitted block is 4 bytes longer.
 */
unsigned int get_object_field_1c(void)
{
    return *(volatile unsigned int *)(0x021DB040u + 0x1cu);
}

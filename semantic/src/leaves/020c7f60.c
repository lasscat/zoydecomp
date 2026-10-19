/* arm9:020c7f60
 * Getter for the 32-bit field at +0x3c of the global object at 0x021DE480.
 * The object address comes from a literal pool in the original, whose pool
 * word lives in the inter-function gap after bx lr; clang keeps its own pool
 * word inside .text, so the emitted block is 4 bytes longer.
 */
unsigned int get_object_field_3c(void)
{
    return *(volatile unsigned int *)(0x021DE480u + 0x3cu);
}

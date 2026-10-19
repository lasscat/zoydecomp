/* arm9:0200f2b8
 * Returns the word at +4 of the object referenced by the global at 0x020FF6E0.
 * The original uses a literal-pool address, two plain loads and bx lr.
 */
unsigned int get_global_object_field(void)
{
    unsigned int *object = *(unsigned int **)0x020FF6E0u;

    return *(unsigned int *)((char *)object + 4);
}

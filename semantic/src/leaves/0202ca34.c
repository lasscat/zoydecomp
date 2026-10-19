/* arm9:0202ca34
 * Store two words into the object at +0x1c and +0x20.
 */
void set_pair(void *p, unsigned int a, unsigned int b)
{
    *(unsigned int *)((char *)p + 0x1c) = a;
    *(unsigned int *)((char *)p + 0x20) = b;
}

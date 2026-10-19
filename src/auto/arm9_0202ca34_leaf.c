/* arm9:0202ca34
 * Store two words into the object at +0x1c and +0x20.
 */
void pvz_0202ca34_leaf(void *p, unsigned int a, unsigned int b)
{
    *(unsigned int *)((char *)p + 0x1c) = a;
    *(unsigned int *)((char *)p + 0x20) = b;
}

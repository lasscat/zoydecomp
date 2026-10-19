/* arm9:0203e8fc
 * Zero the first two 32-bit words of the object pointed to by r0.
 */
void pvz_0203e8fc_leaf(unsigned int *p)
{
    p[0] = 0;
    p[1] = 0;
}

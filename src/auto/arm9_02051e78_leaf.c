/* arm9:02051e78
 * Stores two 32-bit values at +0 and +4 (the original uses one stm).
 */
void pvz_02051e78_leaf(unsigned int *self, unsigned int first, unsigned int second)
{
    self[0] = first;
    self[1] = second;
}

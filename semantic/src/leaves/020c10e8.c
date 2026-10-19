/* arm9:020c10e8 (16 bytes)
 *
 * Table lookup with a second dereference: returns the word pointed to by the
 * table element at the given index.
 *   r1 = 0x020f58d0
 *   r0 = *(int *)(r1 + index * 4)   ; pointer table
 *   r0 = *(int *)r0
 *   bx lr
 *
 * Unknown offset note: 0x020f58d0 is a fixed pointer table of 32-bit entries.
 */
int pvz_020c10e8_lookup(unsigned int index)
{
    int **table = (int **)0x020f58d0u;
    return *table[index];
}

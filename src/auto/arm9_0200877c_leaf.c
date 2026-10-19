/* arm9:0200877c
 * Zeroes the 8-byte pair at self, and (like the original) also zeroes an
 * 8-byte scratch area on the stack that is never read back.  Both the scratch
 * pair and the destination pair are declared volatile so the four stores
 * survive and stay in the original order (stack pair first, then the pair at
 * self); no reload is introduced by this.  The scratch pair is written high
 * word first because clang lays the two-element array out downwards, which
 * keeps the stores in ascending stack-address order like the original.
 */
void pvz_0200877c_leaf(volatile unsigned int *self)
{
    volatile unsigned int scratch[2];

    scratch[1] = 0;
    scratch[0] = 0;
    self[0] = 0;
    self[1] = 0;
}

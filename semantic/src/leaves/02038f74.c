/* arm9:02038f74
 * Stores four 32-bit values at +0/+4/+8/+0xc; the fourth arrives on the
 * stack argument area.  The fourth store is written first in the source so
 * that clang groups only the three register arguments into one stm and then
 * loads the stack value, matching the original's instruction sequence.
 * Only the scratch register differs (clang reuses r1, the original used ip).
 */
void store_quad(unsigned int *self, unsigned int a, unsigned int b,
                unsigned int c, unsigned int d)
{
    self[3] = d;
    self[0] = a;
    self[1] = b;
    self[2] = c;
}

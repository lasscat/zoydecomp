/* arm9:0203f5b4 (20 bytes)
 *
 * Stores the two trailing arguments into the first two words of the record in
 * reverse argument order.
 *   push {r2, r3}
 *   *(int *)(self + 0) = r2   ; second argument
 *   *(int *)(self + 4) = r1   ; first argument
 *   pop  {r2, r3}
 *   bx   lr
 *
 * Unknown offset note: the two words at +0/+4 are stored with the last argument
 * first. The original also brackets the stores with a push/pop of r2/r3, which
 * no natural C form of this body reproduces (see results notes).
 */
void pvz_0203f5b4_store2(int *self, int first, int second)
{
    self[0] = second;
    self[1] = first;
}

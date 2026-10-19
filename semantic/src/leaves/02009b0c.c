/* arm9:02009b0c (16 bytes)
 *
 * Returns the word at the head of the object when the signed byte flag at +3 is
 * non-zero; otherwise the object pointer itself is returned (the original never
 * materializes zero on that path, it simply falls through with r0 == self).
 *   ldrsb r1, [r0, #3]
 *   cmp   r1, #0
 *   ldrne r0, [r0]     ; return *(int *)self when flag != 0
 *   bx    lr
 *
 * Unknown offset note: +0 is a self/cached pointer word, +3 is a signed flag byte.
 */
int pvz_02009b0c_get(char *self)
{
    int value = (int)self;
    if (*(signed char *)(self + 3) != 0)
        value = *(int *)self;
    return value;
}

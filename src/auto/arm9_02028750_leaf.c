/* arm9:02028750 (36 bytes)
 *
 * Kind test. The object's own word at +0x18 is used as the kind; when it is zero
 * the kind is instead taken from +8 of the object pointed to by +0x1c. The
 * function returns 1 when the kind is 2 or 4 and 0 otherwise.
 *   r1 = *(int *)(self + 0x18)
 *   if (r1 == 0) { r0 = *(int *)(self + 0x1c); r1 = *(int *)(r0 + 8); }
 *   return (r1 == 2 || r1 == 4)
 *
 * Unknown offset note: +0x18 kind word, +0x1c fallback object pointer, +8 kind
 * word of the fallback object.
 */
int pvz_02028750_leaf(char *self)
{
    int kind = *(int *)(self + 0x18);
    if (kind == 0)
        kind = *(int *)(*(char **)(self + 0x1c) + 8);
    return kind == 2 || kind == 4;
}

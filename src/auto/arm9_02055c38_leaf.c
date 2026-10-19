/* Return 1 when the word at offset +0x658 is zero, else 0.
 * 0x658 = 1624 bytes, i.e. word element 406 of this object.
 *
 * The target lowers the test to cmp/moveq/movne (selector 1/0).  This compiler
 * instead recognizes "x == 0" and emits clz(x) >> 5, which is 4 bytes shorter;
 * no natural-C form under this profile produces the cmp/mov sequence.
 */
int pvz_02055c38_leaf(int *p) { return *(int *)((char *)p + 0x658) == 0; }

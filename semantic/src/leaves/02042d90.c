/* arm9:02042d90 (24 bytes) -- tier N (2 differing instructions)
 *
 * Zeroes the word at +0 and links the list head embedded at +4 to itself
 * (prev first, then next):
 *   add r1, r0, #4
 *   mov r2, #0
 *   *(+0x00) = 0
 *   list->prev (r1 + 4) = r1
 *   list->next (r1 + 0) = r1
 *   bx  lr
 *
 * The embedded head has its link fields at +0 (next) and +4 (prev). The two
 * link stores are volatile so the compiler does not merge the neighbouring
 * stores into one stm; the count store stays plain so its address computation
 * is scheduled first as in the original. Remaining differences: clang folds the
 * prev store to [r0 + 8] instead of [r1 + 4] and emits it before the count
 * store. The all-volatile draft (02042d90_h2.c) keeps the store order but has
 * 4 differing instructions.
 */
struct pvz_list_node {
    struct pvz_list_node *volatile next;   /* +0x0 */
    struct pvz_list_node *volatile prev;   /* +0x4 */
};

void pvz_02042d90_init(int *self)
{
    struct pvz_list_node *list = (struct pvz_list_node *)((char *)self + 4);
    self[0] = 0;
    list->prev = list;
    list->next = list;
}

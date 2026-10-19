/* arm9:02061210  (60 bytes, no literal pool)
 *
 *   push {r3, lr}
 *   ldr  lr, [r0]           ; *head
 *   mov  ip, #0
 *   str  r2, [lr]           ; (*head)->value  = arg3
 *   ldr  r2, [r0]           ; reload: the store may alias the head slot
 *   str  r3, [r2, #4]       ; (*head)->field1 = arg4
 *   ldr  r2, [r0]
 *   str  ip, [r2, #8]       ; (*head)->field2 = 0
 *   ldr  r2, [r1]
 *   add  r2, r2, #1
 *   str  r2, [r1]           ; ++*count
 *   ldr  r1, [r0]
 *   add  r1, r1, #0xc
 *   str  r1, [r0]           ; head now points one entry further
 *   pop  {r3, pc}
 *
 * Appends a 12-byte entry to a bump arena.
 */
struct Entry_02061210 {
    int value;      /* +0x00 */
    int field_0x04; /* +0x04 */
    int field_0x08; /* +0x08 */
};

void pvz_02061210_leaf(struct Entry_02061210 **head, int *count, int value, int field)
{
    (*head)->value = value;
    (*head)->field_0x04 = field;
    (*head)->field_0x08 = 0;
    *count = *count + 1;
    *head = *head + 1;
}

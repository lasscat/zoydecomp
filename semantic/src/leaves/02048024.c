/* 02048024 (24 bytes): pop the head of a singly linked list.
 *   ldr r2, [r1]   ; r2 = *head
 *   str r2, [r0]   ; *out = old head
 *   ldr r0, [r1]   ; r0 = *head   (re-read: the store may alias *head)
 *   ldr r0, [r0]   ; r0 = (*head)->next
 *   str r0, [r1]   ; *head = next
 *   bx  lr
 * Detaches the current head node from the list and returns it via *out.
 * The head slot is read twice independently; a volatile head models that
 * (a competing compiler keeps both loads). */
void leaf_pop(void **out, void *volatile *head)
{
    *out = *head;
    *head = *(void **)*head;
}

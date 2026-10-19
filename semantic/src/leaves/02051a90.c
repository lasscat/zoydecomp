/*
 * arm9:02051a90  (24 bytes, no literal pool)
 *
 * Original:
 *   ldr  r2, [r1]              ; r2 = *head
 *   str  r2, [r0]              ; *out = *head
 *   ldr  r0, [r1]              ; reload *head (independent load)
 *   ldr  r0, [r0, #4]          ; r0 = (*head)->next
 *   str  r0, [r1]              ; *head = (*head)->next
 *   bx   lr
 *
 * Pops the head node of a singly linked list: the old head is copied to *out
 * and the head pointer advances to node->next at +0x04.
 *
 * Note on the `volatile` qualifier: the original loads the head slot twice; a
 * plain form lets clang reuse the first load (20 bytes). Declaring the head
 * slot volatile keeps both loads of the observed DS sequence. Node meaning is
 * unknown.
 */

struct ListNode {
    unsigned int value;                  /* +0x00 */
    struct ListNode *next;               /* +0x04 */
};

void pvz_02051a90_leaf(struct ListNode **out, struct ListNode *volatile *head)
{
    *out = *head;
    *head = (*head)->next;
}

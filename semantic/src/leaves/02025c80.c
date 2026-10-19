/* arm9:02025c80 (28 bytes)
 *
 * Pushes a freshly built 12-byte node onto a global singly linked list.
 * The list head pointer lives at the fixed address 0x021017c8.
 *   r3 = 0x021017c8
 *   ip = *r3            ; old head
 *   node[0] = ip        ; *(int *)(node + 0) = old head
 *   node[1] = r1        ; *(int *)(node + 4) = arg1
 *   node[2] = r0        ; *(int *)(node + 8) = arg0
 *   *r3 = node          ; head = node
 *   bx  lr
 *
 * Unknown offset note: node layout +0 next, +4 first payload, +8 second payload.
 * The three stores happen in exactly this order (head read first).
 */
void pvz_02025c80_push(int payload_a, int payload_b, int *node)
{
    int *head = (int *)0x021017c8u;
    node[0] = *head;
    node[1] = payload_b;
    node[2] = payload_a;
    *head = (int)node;
}

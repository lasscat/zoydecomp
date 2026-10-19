/* Unlink node from a doubly linked list. head+4 points at the next node and
   the next node's first word points back at head. */
void f(void **head, void *node) {
    void *next = *(void **)((char *)node + 4);
    *(void **)((char *)(*head) + 4) = next;
    *(void **)next = *head;
}

/* arm9:02004564
 * Unlinks the head node of a singly linked list and returns it.
 * node->next is at +0x10; the new head's back pointer is at +0x14.
 * When the list becomes empty the tail pointer at head+4 is cleared.
 */
void *sub_02004564(void **head)
{
    void *node = *head;

    if (node != 0) {
        void *next = *(void **)((char *)node + 0x10);
        *head = next;
        if (next != 0)
            *(void **)((char *)next + 0x14) = 0;
        else
            *(void **)((char *)head + 4) = 0;
    }
    return node;
}

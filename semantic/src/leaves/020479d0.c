/* Advances the head slot past the current head node: *head = (*head)->next. */
struct UnknownNode {
    unsigned char unknown_0x00_0x03[4];
    struct UnknownNode *next_0x04;
};

void pvz_020479d0_advance_head(struct UnknownNode **head)
{
    *head = (*head)->next_0x04;
}

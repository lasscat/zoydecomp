/* Appends a node to the tail of the list rooted in a global descriptor. */
typedef struct Node {
    char pad[0x4bc];
    struct Node *next;
} Node;

typedef struct {
    char pad[0x18];
    Node *head;
} Registry;

void register_node(Node *n)
{
    Registry *reg = (Registry *)0x02100b50;
    Node *tail = reg->head;

    if (tail == 0) {
        reg->head = n;
    } else {
        Node *next = tail->next;

        if (next != 0) {
            do {
                tail = next;
                next = tail->next;
            } while (next != 0);
        }
        tail->next = n;
    }
    n->next = 0;
}

typedef struct {
    char pad[0x20];
    int field20;
} Frame;

typedef struct {
    int value;
    int field20;
    Frame *frame;
} Record;

void pvz_020611d8_leaf(Record **list, int *count, int value, Frame *frame)
{
    (*list)->value = value;
    (*list)->field20 = frame->field20;
    (*list)->frame = frame;
    (*count)++;
    *list = *list + 1;
}

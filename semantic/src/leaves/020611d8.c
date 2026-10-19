typedef struct {
    char pad[0x20];
    int field20;
} Frame;

typedef struct {
    int value;
    int field20;
    Frame *frame;
} Record;

void push_record(Record **list, int *count, int value, Frame *frame)
{
    (*list)->value = value;
    (*list)->field20 = frame->field20;
    (*list)->frame = frame;
    (*count)++;
    *list = *list + 1;
}

/* arm9:0205de40 - fill a 5x5 block of table entries with increasing ids. */

typedef struct {
    int id;
    int index;
    int value;
} Slot;

typedef struct {
    Slot slots[54];
    int count;
} SlotTable;

void slot_table_fill(int unused, SlotTable *table)
{
    Slot *slot;
    int id = 4;
    int index;

    (void)unused;
    table->count = 0;
    do {
        index = 0;
        do {
            slot = &table->slots[table->count];
            slot->id = id;
            slot->index = index;
            slot->value = 10000;
            table->count = table->count + 1;
            index++;
        } while (index <= 4);
        id++;
    } while (id < 9);
}

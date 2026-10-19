/* Adjust a saturating counter that lives at offset 0x18 of the control block
   at 0x02105F10.

   A zero argument raises the counter by one.  A non-zero argument lowers it
   by one, but never below zero.  The two paths are exclusive, so the raise
   always returns before the lowering path is entered (the original tests the
   argument once and branches to the raising block). */
struct counter_block {
    char pad[0x18];
    int counter;
};

void adjust_counter(int decrement)
{
    struct counter_block *block = (struct counter_block *)0x02105F10u;

    if (decrement != 0) {
        if (block->counter > 0)
            block->counter--;
    } else {
        block->counter++;
    }
}

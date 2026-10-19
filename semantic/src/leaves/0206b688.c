/*
 * Advances a timer/state object:
 *   - byte +0x50 is cleared,
 *   - while counter +0x8C is still zero the value at +0x58 is capped at
 *     0x190 (left unchanged when already <= 0x190),
 *   - counter +0x8C is then incremented.
 * Offsets 0x50, 0x58 and 0x8C are unverified field offsets.
 */
struct timer_state {
    unsigned char pad[0x50];
    unsigned char flag;          /* +0x50 */
    unsigned char pad2[7];       /* up to +0x58 */
    int value;                   /* +0x58 */
    unsigned char pad3[0x30];    /* up to +0x8C */
    int counter;                 /* +0x8C */
};

void timer_tick(struct timer_state *self)
{
    self->flag = 0;

    if (self->counter == 0) {
        int cap = 0x190;
        int *src = &self->value;

        if (*src > 0x190)
            src = &cap;

        self->value = *src;
    }

    self->counter++;
}

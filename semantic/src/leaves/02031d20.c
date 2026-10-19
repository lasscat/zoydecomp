/* arm9:02031d20
 * Releases a pending transfer: clears the word the pending pointer targets and
 * the stored pointer, then clears three low status bits (1, 4 and 2) of the
 * state word at +0x118.
 */
typedef struct {
    unsigned char pad0[0x118];
    unsigned int status;      /* 0x118 */
    unsigned char pad1[0x38];
    unsigned int *pending;    /* 0x154 */
} Channel;

void channel_stop(Channel *ch)
{
    if (ch->pending != 0) {
        *ch->pending = 0;
        ch->pending = 0;
    }
    ch->status &= ~1;
    ch->status &= ~4;
    ch->status &= ~2;
}

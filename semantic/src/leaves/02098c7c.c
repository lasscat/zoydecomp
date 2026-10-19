/*
 * arm9:02098c7c  (20 bytes)
 *
 *   ldrh  r0, [r0, #0x60]
 *   tst   r0, #0x68
 *   movne r0, #1
 *   moveq r0, #0
 *   bx    lr
 *
 * Tests bits 3, 5 and 6 of the 16-bit field at +0x60 and normalises the
 * result to 0/1.
 */
struct Status_02098c7c {
    unsigned char pad_0x00[0x60];
    unsigned short field_0x60;
};

int pvz_02098c7c(struct Status_02098c7c *state)
{
    return (state->field_0x60 & 0x68) != 0;
}

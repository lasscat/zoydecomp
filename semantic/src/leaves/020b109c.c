/* True while the difference between the object's timer word at 0x2c and the
   word at 0x688 -> 0x18c of its owner is below 0xe10 ticks. */
int is_due_020b109c(unsigned char *object)
{
    unsigned char *owner = *(unsigned char **)object;
    unsigned char *clock = *(unsigned char **)(owner + 0x688);
    return *(int *)(object + 0x2c) - *(int *)(clock + 0x18c) < 0xe10;
}

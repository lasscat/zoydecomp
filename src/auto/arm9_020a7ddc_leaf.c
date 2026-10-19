/* Clears two flag bytes and the two word counters between them. The four stores
   are independent; the pointer parameter is volatile so that the backend keeps
   the original store order (byte 0x48, words 0x24/0x28, byte 0x49) instead of
   hoisting the 0x49 byte store. */
void pvz_020a7ddc_leaf(volatile unsigned char *object)
{
    object[0x48] = 0;
    *(volatile unsigned int *)(object + 0x24) = 0;
    *(volatile unsigned int *)(object + 0x28) = 0;
    object[0x49] = 0;
}

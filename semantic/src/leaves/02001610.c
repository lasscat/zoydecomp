/* Reads the sub-screen DISPCNT register (0x04001008) and returns the VRAM bank
   base address selected by bits 8..12: 0x06200000 + bank * 0x800.
   Measured X: clang folds (mask, asr, lsl) into one shifted-and plus an orr and
   needs one extra literal-pool word. */
unsigned int bank_base_02001610(void)
{
    int select = *(volatile unsigned short *)0x04001008 & 0x1f00;
    return 0x06200000 + ((select >> 8) << 11);
}

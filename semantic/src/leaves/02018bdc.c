/* Merge two configuration words into the 16-bit control register at
   0x04000204 (ARM9 memory-mapped I/O).

   Bits 2-3 of the register are replaced by the low bits of cfg[0] shifted
   left by two, then bit 4 is replaced by the low bit of cfg[1] shifted left
   by four.  The register is read back before each update, and each update is
   a read-modify-write of the whole halfword. */
void update_control_bits(unsigned *cfg)
{
    volatile unsigned short *reg = (volatile unsigned short *)0x04000204u;

    *reg = (unsigned short)((cfg[0] << 2) | (*reg & ~0xCu));
    *reg = (unsigned short)((cfg[1] << 4) | (*reg & ~0x10u));
}

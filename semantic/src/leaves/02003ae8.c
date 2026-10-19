/* Halfword field at offset 0x0c of the global table at 0x020fd340.
   Measured X: the non-encodable address has to come from a literal pool, so the
   compiled .text is four bytes longer than the target extent (which stores its
   pool word outside the recorded size). */
unsigned int field_02003ae8(void)
{
    return *(volatile unsigned short *)(0x020fd340 + 0x0c);
}

/* Reads a 16-bit value from a fixed global.  Address literal 0x020e04e0 is
 * unknown (record identity not established); the offset is zero. */
unsigned short pvz_02001228_get_unknown_u16(void)
{
    return *(volatile unsigned short *)0x020e04e0;
}

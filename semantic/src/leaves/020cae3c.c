/* arm9:020cae3c
 * Clear byte 3 then byte 1 of the fixed global record at 0x021de53c.
 */
void reset_bytes(void)
{
    unsigned char *p = (unsigned char *)0x021DE53Cu;

    p[3] = 0;
    p[1] = 0;
}

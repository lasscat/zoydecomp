/* arm9:02044c88
 * If the byte flag at +0x44d is clear, set the byte at +0x450 and then the flag
 * itself to 1.
 * volatile reproduces the original's store order (+0x450 before +0x44d).
 */
void check_flag(volatile unsigned char *p)
{
    if (p[0x44d] == 0) {
        p[0x450] = 1;
        p[0x44d] = 1;
    }
}

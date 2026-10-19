/* Sets a byte flag at global+3. */
void set_flag3(void)
{
    volatile unsigned char *base = (volatile unsigned char *)0x021de53cu;
    base[3] = 1;
}

/* arm9:0203074c
 * Return field 0x8c of the object referenced by the global pointer at 0x02104240.
 */
unsigned int get_current_f8c(void)
{
    unsigned char *obj = *(unsigned char **)0x02104240u;

    return *(unsigned int *)(obj + 0x8c);
}

/* arm9:020c48c8
 * Field 0x478 of the object held at 0x021da420 + 0x28, or 0 when that pointer
 * is null.
 */
unsigned int get_active_field478(void)
{
    unsigned char *obj = *(unsigned char **)(0x021DA420u + 0x28);

    if (obj)
        return *(unsigned int *)(obj + 0x478);
    return 0;
}

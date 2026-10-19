/* Stores the argument into the fixed global at 0x021dde20. */
void pvz_020c64c8_set_global(unsigned int value)
{
    *(unsigned int *)0x021dde20 = value;
}

/* Sets the byte at 0x021de53c+1 to 1 (an enable flag of a fixed global). */
struct UnknownGlobalFlags {
    unsigned char unknown_0x00;
    unsigned char enabled_0x01;
};

void pvz_020cad94_enable(void)
{
    struct UnknownGlobalFlags *flags = (struct UnknownGlobalFlags *)0x021de53c;

    flags->enabled_0x01 = 1;
}

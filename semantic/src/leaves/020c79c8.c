void f(void)
{
    unsigned int st = *(volatile unsigned int *)0x021DE250;
    int i;

    if ((st & 1) == 0)
        return;
    if ((st & 0x20) == 0 && (st & 4) != 0) {
        for (i = 0; i < 2; i++) {
            if (*(unsigned char *)(0x021DE300 + 0xD0 + i) != 0)
                *(int *)(0x021DE25C + i * 4) = 0x021DE340 + i * 0x30 + 0x10;
            else
                *(int *)(0x021DE25C + i * 4) = 0;
        }
    }
    *(volatile unsigned int *)0x021DE250 |= 0x20;
}

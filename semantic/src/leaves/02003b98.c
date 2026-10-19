/* 0x02003b98: reset a 13-halfword scratch block at 0x020FD340 and clear
 * a control block at 0x04000240 (word, three bytes, one halfword). */
void ResetScreenBlocks(void)
{
    volatile unsigned short *scratch = (volatile unsigned short *)0x020FD340;
    volatile unsigned char *ctrl = (volatile unsigned char *)0x04000240;
    scratch[0] = 0;
    scratch[1] = 0;
    scratch[2] = 0;
    scratch[3] = 0;
    scratch[4] = 0;
    scratch[5] = 0;
    scratch[6] = 0;
    scratch[7] = 0;
    scratch[8] = 0;
    scratch[9] = 0;
    scratch[10] = 0;
    scratch[11] = 0;
    scratch[12] = 0;
    *(volatile unsigned int *)ctrl = 0;
    ctrl[4] = 0;
    ctrl[5] = 0;
    ctrl[6] = 0;
    *(volatile unsigned short *)(ctrl + 8) = 0;
}

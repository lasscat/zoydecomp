/* Arm display bank 0 and copy a hardware state byte into the pending state.
 * Global block at 0x02100b50 (unknown layout):
 *   +0x1c : pointer to the current display context
 *   +0x24 : pending byte, set to 5
 *   +0x26 : mirrored state byte
 * Display context:
 *   +0x4b0 : halfword armed flag
 *   +0x4b4 : byte hardware state
 * The context pointer is documented volatile so that it is re-read after the
 * store through it, matching the original's independent reloads.
 */
void sub_020161e0(void)
{
    unsigned char *const g = (unsigned char *)0x02100b50;
    unsigned char *p = *(unsigned char *volatile *)(g + 0x1c);
    unsigned char *armed = p + 0x400;

    *(volatile unsigned short *)(armed + 0xb0) = 1;
    *(volatile unsigned char *)(g + 0x26) =
        *(volatile unsigned char *)(*(unsigned char *volatile *)(g + 0x1c) + 0x4b4);
    *(volatile unsigned char *)(g + 0x24) = 5;
}

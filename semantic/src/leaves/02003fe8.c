/* Programs two 32-bit words of the transfer engine register block based at
   0x027e0000 (offsets 0x3f7c and 0x3580). */
void program_02003fe8(void)
{
    *(volatile unsigned int *)(0x027e0000 + 0x3f7c) = 0xfddb597d;
    *(volatile unsigned int *)(0x027e0000 + 0x3580) = 0x7bf9dd5b;
}

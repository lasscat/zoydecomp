/* Mode-registration stub followed by the small EXMEMCNT helper it installs.
   The reviewed extent at 0x020042e0 covers both the indirect tail call that
   passes (arg0, 0x02ffffe8, &clear_exmem_bit7, 1) to 0x02004238 and the
   0x02004300 helper that runs afterwards; a single MWCC .text section cannot
   hold two code chunks with a literal pool between them. */
typedef int (*Handler)(int, int, void *, int);

int install_mode(int a)
{
    Handler h = (Handler)0x02004238;

    return h(a, 0x02ffffe8, (void *)0x02004300, 1);
}

void clear_exmem_bit7(void)
{
    *(volatile unsigned short *)0x04000204 &= ~0x80;
}

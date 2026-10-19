/* arm9:0203925c (40 bytes)
 *
 * Initializes a fixed-layout record: a tag/list pointer at +0, zeroed 32-bit
 * fields at +4/+8/+0xc/+0x10 and the constant 0x15 at +0x14.
 *   r3 = 0x020e1758
 *   r2 = 0, r1 = 0x15
 *   *(+0x00) = r3 ; *(+0x04) = 0 ; *(+0x0c) = 0 ; *(+0x08) = 0
 *   *(+0x10) = 0  ; *(+0x14) = 0x15
 *   bx  lr
 *
 * Unknown offset note: 0x020e1758 is an absolute data/vtable pointer stored at
 * +0; 0x15 is a small type/id constant.
 */
void pvz_0203925c_init(char *self)
{
    *(int *)self = 0x020e1758;
    *(int *)(self + 4) = 0;
    *(int *)(self + 8) = 0;
    *(int *)(self + 0xc) = 0;
    *(int *)(self + 0x10) = 0;
    *(int *)(self + 0x14) = 0x15;
}

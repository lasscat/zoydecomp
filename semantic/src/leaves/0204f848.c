/* arm9:0204f848 (24 bytes)
 *
 * Initializes a record: word fields at +0/+4/+0xc cleared and the float
 * constant 12.0f (0x41400000) stored at +8.
 *   r1 = 0, r2 = 0x41400000
 *   *(+0x00) = 0 ; *(+0x04) = 0 ; *(+0x08) = r2 ; *(+0x0c) = 0
 *   bx  lr
 *
 * Unknown offset note: 0x41400000 is the IEEE-754 single 12.0f; +8 is a float
 * field, the other three are word fields.
 */
void pvz_0204f848_init(char *self)
{
    *(int *)self = 0;
    *(int *)(self + 4) = 0;
    *(float *)(self + 8) = 12.0f;
    *(int *)(self + 0xc) = 0;
}

/*
 * arm9:0203fd34  (28 bytes)
 *
 *   ldr  r2, [r0]
 *   lsl  r2, r2, #0x1f
 *   lsrs r2, r2, #0x1f       ; flag = word[0] & 1
 *   addeq r0, r0, #2         ; flag == 0 -> inline data at self + 2
 *   ldrne r0, [r0, #8]       ; flag != 0 -> pointer stored at self + 8
 *   add  r0, r0, r1, lsl #1  ; + short index * 2
 *   bx   lr
 *
 * Element accessor for a string/array that keeps short payloads inline:
 * bit 0 of the first word selects between the inline buffer at +0x02 and
 * the heap pointer at +0x08; the halfword index is then scaled by two.
 */
struct SmallBuffer_0203fd34 {
    unsigned int flags_0x00;
    unsigned char pad_0x04[0x04];
    unsigned char *data_0x08;
};

unsigned short *pvz_0203fd34(struct SmallBuffer_0203fd34 *buffer, int index)
{
    unsigned short *data = ((buffer->flags_0x00 & 1) != 0)
                         ? (unsigned short *)buffer->data_0x08
                         : (unsigned short *)((char *)buffer + 2);

    return data + index;
}

/*
 * arm9:02097e80  (40 bytes of code; the original's literal pool follows the
 * code and lies outside the recorded extent)
 *
 * Original:
 *   ldr  ip, [r0, #0x14]       ; ip = index (1-based counter)
 *   ldr  r1, [pc, #0x1c]       ; r1 = 0x61c (element stride)
 *   sub  r2, ip, #1            ; r2 = index - 1
 *   mul  r3, r2, r1            ; r3 = (index - 1) * 0x61c
 *   add  r1, ip, #1
 *   str  r1, [r0, #0x14]       ; counter = index + 1
 *   add  r0, r0, #0x1c         ; r0 = record->array
 *   str  ip, [r0, r3]          ; array[index - 1].field_0x00 = index
 *   add  r0, r0, r3            ; return &array[index - 1]
 *   bx   lr
 *
 * Appends an element to a 0x61c-byte-stride array at +0x1c of the record. The
 * 1-based counter at +0x14 both numbers the element written at slot
 * counter - 1 and is then pre-incremented. Record/element layout is unknown.
 */
void *pvz_02097e80_leaf(void *record)
{
    unsigned int index = *(unsigned int *)((char *)record + 0x14);
    char *element = (char *)record + 0x1c + (index - 1u) * 0x61cu;

    *(unsigned int *)((char *)record + 0x14) = index + 1u;
    *(unsigned int *)element = index;
    return element;
}

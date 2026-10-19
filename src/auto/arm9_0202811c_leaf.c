/*
 * arm9:0202811c  (16 bytes)
 *
 * Original:
 *   ldr  r1, [r0, #0x14]       ; r1 = p->field_0x14
 *   add  r1, r1, r0            ; r1 += (unsigned)p
 *   str  r1, [r0, #0x14]       ; p->field_0x14 = r1
 *   bx   lr
 *
 * Advances a stored pointer/offset field by the address of the record itself
 * (relocating a self-relative pointer). Field meaning is unknown.
 */
void pvz_0202811c_leaf(void *record)
{
    unsigned int *field = (unsigned int *)((char *)record + 0x14);

    *field = *field + (unsigned int)record;
}

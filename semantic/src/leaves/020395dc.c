/*
 * arm9:020395dc  (36 bytes, no literal pool)
 *
 * Original:
 *   ldr  ip, [r1]              ; four words are loaded from src ...
 *   ldr  r3, [r1, #4]
 *   ldr  r2, [r1, #8]
 *   ldr  r1, [r1, #0xc]
 *   str  ip, [r0]              ; ... and then stored to dst in order
 *   str  r3, [r0, #4]
 *   str  r2, [r0, #8]
 *   str  r1, [r0, #0xc]
 *   bx   lr
 *
 * Copies a 16-byte record as four independent word moves.
 *
 * Note on the `volatile` qualifiers: a plain struct assignment makes clang fold
 * the four loads into `ldm` and the four stores into `stm` (20 bytes) and it
 * also emits the stores in descending order; the DS original performs eight
 * separate word accesses in ascending order. Declaring the source and
 * destination words volatile reproduces that access sequence. Record contents
 * are unknown.
 */
void pvz_020395dc_leaf(unsigned int *destination, const unsigned int *source)
{
    unsigned int word_00 = *(volatile const unsigned int *)(source + 0);
    unsigned int word_04 = *(volatile const unsigned int *)(source + 1);
    unsigned int word_08 = *(volatile const unsigned int *)(source + 2);
    unsigned int word_0c = *(volatile const unsigned int *)(source + 3);

    *(volatile unsigned int *)(destination + 0) = word_00;
    *(volatile unsigned int *)(destination + 1) = word_04;
    *(volatile unsigned int *)(destination + 2) = word_08;
    *(volatile unsigned int *)(destination + 3) = word_0c;
}

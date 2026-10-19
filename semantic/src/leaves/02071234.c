/*
 * arm9:02071234  (36 bytes)  -- tier N (same size, 4 differing instructions, twin of arm9:0203ba04)
 *
 * Original instructions:
 *   ldr ip, [r1] / ldr r3, [r1, #4] / ldr r2, [r1, #8] / ldr r1, [r1, #0xc]
 *   str ip, [r0] / str r3, [r0, #4] / str r2, [r0, #8] / str r1, [r0, #0xc]
 *   bx lr
 *
 * Copies a 16-byte (four-word) value from the second argument to the first,
 * loading all four words before storing any of them.
 *
 * Without volatile clang recognises the copy and emits ldm/stm (a 20-byte
 * candidate). The qualifiers here only force the original's eight independent
 * ascending accesses; the remaining difference is register allocation: the
 * original loads the first word into ip, clang into r2 (positions 0 and 2 and
 * their two mirrors differ, four bytes in total).
 */
struct Block16_02071234 {
    unsigned int word_0x00;
    unsigned int word_0x04;
    unsigned int word_0x08;
    unsigned int word_0x0c;
};

void pvz_02071234(volatile struct Block16_02071234 *dest, const volatile struct Block16_02071234 *src)
{
    unsigned int w0 = src->word_0x00;
    unsigned int w1 = src->word_0x04;
    unsigned int w2 = src->word_0x08;
    unsigned int w3 = src->word_0x0c;

    dest->word_0x00 = w0;
    dest->word_0x04 = w1;
    dest->word_0x08 = w2;
    dest->word_0x0c = w3;
}

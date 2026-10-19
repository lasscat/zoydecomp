/*
 * arm9:020b8eb0  (16 bytes of code; the original's literal pool follows the
 * code and lies outside the recorded extent)
 *
 * Original:
 *   ldr  r3, [pc, #8]          ; r3 = 0x02108db4
 *   ldm  r0, {r0, r1, r2}      ; load the three words of the source block
 *   stm  r3, {r0, r1, r2}      ; store them at 0x02108db4
 *   bx   lr
 *
 * Copies a 12-byte block into the fixed triple at 0x02108db4. Block meaning is
 * unknown.
 */

struct Triple {
    unsigned int word_00;
    unsigned int word_04;
    unsigned int word_08;
};

void pvz_020b8eb0_leaf(const struct Triple *source)
{
    *(struct Triple *)0x02108db4u = *source;
}

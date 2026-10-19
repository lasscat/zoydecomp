/* 02047b58 (arm9, 24 bytes)  -- EXACT byte match with clang23-arm946-o2
 *
 * Target:
 *   ldr r2, [r1]        ; r2 = *b
 *   str r2, [r0]        ; *a = *b
 *   ldr r0, [r1]        ; r0 = *b          (reloaded)
 *   ldr r0, [r0, #4]    ; r0 = *(u32 *)(*b + 4)
 *   str r0, [r1]        ; *b = that
 *   bx  lr
 *
 * Pop: copy the head value at *b into *a, then advance *b to the next link
 * (word at offset 4 of the popped node).
 *
 * NOTE: b is a pointer to a volatile pointer. With a plain pointer the
 * compiler forwarded the stored value and skipped the reload of *b
 * (5 instructions / 20 bytes). The volatile qualifier reproduces the
 * original's reload of *b between the two accesses.
 */
void pvz_02047b58_leaf(unsigned int **a, unsigned int *volatile *b)
{
    *a = *b;
    *b = *(unsigned int **)((char *)*b + 4);
}

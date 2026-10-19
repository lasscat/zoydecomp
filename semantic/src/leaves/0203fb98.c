/*
 * arm9:0203fb98  (12 bytes)
 *
 * Original:
 *   push {r0, r1, r2, r3}
 *   add  sp, sp, #0x10
 *   bx   lr
 *
 * Saves all four argument registers and immediately discards the 16-byte save
 * area, i.e. a no-op that still clobbers the caller's 16 scratch bytes below the
 * stack pointer - the classic prologue of a *variadic* SDK stub whose body never
 * consumes any argument. Its neighbours 0x0203fba4 and 0x0203fba8 are plain
 * `bx lr` stubs, and 0x0203fbac is a `bx ip` tail-call trampoline, so this
 * address belongs to the SDK stub/thunk block.
 *
 * The C below is the closest natural source: a variadic function whose va_list
 * is initialised and dropped. It is recorded as X: with the fixed clang profile
 * the va_start register-save area is emitted as `sub sp, sp, #0x10;
 * stmib sp, {r1, r2, r3}` (16 bytes) rather than the original's single
 * `push {r0, r1, r2, r3}` (12 bytes); no natural ISO C form reproduces the
 * original prologue byte-for-byte.
 */

typedef __builtin_va_list pvz_va_list;

void pvz_0203fb98_leaf(int first, ...)
{
    pvz_va_list arguments;

    __builtin_va_start(arguments, first);
    (void)arguments;
}

/* 02053dc4 (8 bytes): constant-returning accessor.
 *   mov r0, #0
 *   bx  lr
 * Always yields 0. */
int leaf_zero(void)
{
    return 0;
}

/* arm9:02052584 (8 bytes)
 *
 * Constant predicate, byte-identical twin of arm9:02043d14.
 *   mov r0, #1
 *   bx  lr
 */
int pvz_02052584_is_enabled(void)
{
    return 1;
}

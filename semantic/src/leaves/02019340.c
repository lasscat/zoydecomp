/* arm9:02019340
 * Installs/rstalls a handler.  Stores arg into the word at 0x02101270 and
 * returns the previous value.  It also points the word at 0x020e05d0 at one
 * of two routines depending on whether arg is null.  Only the first pool
 * constant (0x02101270) lies inside the reviewed extent; the remaining two
 * addresses came from the ROM pool words at 0x02019370/0x02019374/0x02019378.
 */
void *sub_02019340(void *arg)
{
    void **slot = (void **)0x02101270;
    void *old = *slot;

    *slot = arg;
    *((void **)0x020e05d0) =
        arg ? (void *)0x02019284 : (void *)0x020198b0;
    return old;
}

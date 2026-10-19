/* Trim a byte count down to a multiple of 4 (the loop body lives in the caller
 * conventions of this build; only the decrement remains here). */
void sub_020066d0(unsigned int size)
{
    while (size >= 4)
        size -= 4;
}

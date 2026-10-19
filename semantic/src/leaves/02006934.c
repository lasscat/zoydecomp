/* Count the leading zero bits of a 32-bit value.

   The original is a single ARMv5 "clz" instruction followed by the return,
   which means the reference build had a hardware count-leading-zeros
   intrinsic available.  The reviewed MWCC 2.0 profile for the ARM946E-S
   exposes no CLZ builtin (every plausible spelling - __builtin_clz, __clz,
   _clz, __cntlz, __count_leading_zeros - is compiled as an ordinary implicit
   function call and therefore needs a relocation), so the closest natural
   ASCII C is the shift/count loop below.  It computes the same value but is
   not byte-identical (see the lane results for the measured difference). */
int count_leading_zeros(unsigned value)
{
    int n = 0;

    if (value == 0u)
        return 32;

    while ((value & 0x80000000u) == 0u) {
        value <<= 1;
        n++;
    }
    return n;
}

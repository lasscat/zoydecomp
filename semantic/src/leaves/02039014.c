/* Report whether the three leading 32-bit words of two records differ.

   The comparison is written as a short-circuit chain of inequalities, which
   is what produces the conditional (ldreq/cmpeq) sequence and the final
   "1 when different, 0 when equal" result in the original. */
int records_differ(const unsigned *a, const unsigned *b)
{
    return a[0] != b[0] || a[1] != b[1] || a[2] != b[2];
}

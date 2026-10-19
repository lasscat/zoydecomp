/* Split a second counter into hours, minutes and seconds.

   The counter is clamped into [0, 86399] (one day minus one second), then
   	out[0] receives the hours, out[1] the minutes and out[2] the seconds.

   This is the natural spelling of the operation.  The reviewed -O2 profile
   lowers a division by the non-power-of-two constant 60 to a call to the
   runtime helper _s32_div_f, which the reviewed probe rejects as an
   unsupported relocation.  The ROM's own bytes contain the inline
   reciprocal-multiply sequence (magic 0x88888889, shift 5, with the sign
   correction) for /60, so the original build inlined division; the measured
   outcome for this source under the reviewed profile is recorded as blocked
   in the lane results. */
void split_time(int *out, int seconds)
{
    if (seconds < 0)
        seconds = 0;
    if (seconds > 86399)
        seconds = 86399;

    out[0] = seconds / 60 / 60;
    out[1] = (seconds / 60) % 60;
    out[2] = seconds % 60;
}

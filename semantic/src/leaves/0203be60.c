/* Copies four 16-bit coordinates from the source rectangle to the target.
   The original loads all four values with ldrsh and stores them in ascending
   order; clang uses ldrh and ends up with a different load/store interleave. */
void copy_rect_0203be60(short *dst, const short *src)
{
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
    dst[3] = src[3];
}

/* arm9:020395b8
 * Copy four signed 16-bit fields from src to dst.
 */
void copy_four_shorts(short *dst, const short *src)
{
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
    dst[3] = src[3];
}

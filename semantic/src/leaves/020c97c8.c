/* arm9:020c97c8
 * *out = src[0] + src[1] * 4.
 */
void sum_scaled(unsigned int *out, const unsigned int *src)
{
    *out = src[0] + src[1] * 4;
}

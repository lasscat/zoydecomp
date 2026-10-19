/* arm9:020b2c00
 * Push value into the per-index buffer:
 *   counts[index] at t+0xe8, each buffer is 0x200 bytes with its array at +0x104.
 */
void buffer_push(unsigned char *t, unsigned int index, unsigned int value)
{
    unsigned int *count = (unsigned int *)(t + 0xe8 + index * 4);

    *(unsigned int *)(t + index * 0x200 + 0x104 + *count * 4) = value;
    (*count)++;
}

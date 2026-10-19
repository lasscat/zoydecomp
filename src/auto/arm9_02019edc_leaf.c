/* arm9:02019edc
 * Writes one byte through a count/pointer pair and always advances the pointer.
 * While the remaining count is non-zero, the byte is stored at the pointer and
 * the count is reduced by one; the pointer is incremented afterwards.
 */
typedef struct {
    int remaining;
    unsigned char *cursor;
} ByteSink;

void pvz_02019edc_leaf(ByteSink *sink, unsigned char value)
{
    if (sink->remaining != 0) {
        *sink->cursor = value;
        sink->remaining -= 1;
    }
    sink->cursor += 1;
}

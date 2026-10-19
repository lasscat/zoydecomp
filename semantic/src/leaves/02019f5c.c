/* Append bytes from a caller buffer into a queued write area.
   Object: { unsigned len at 0; char *ptr at 4; } where len is the number of
   bytes still available.  At most len bytes are copied; the remaining count
   shrinks by the number of bytes actually copied while the write pointer
   advances by the requested count. */
struct bytequeue {
    unsigned len;
    char *ptr;
};

void queue_write(struct bytequeue *q, const char *src, unsigned n)
{
    unsigned i;
    unsigned count;

    if (n == 0)
        return;

    count = q->len < n ? q->len : n;

    for (i = 0; i < count; i++)
        q->ptr[i] = src[i];

    q->len -= count;
    q->ptr += n;
}

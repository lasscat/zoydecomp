/* Fill up to n bytes of a queued buffer with value; consume min(count, n)
 * from count and advance the write pointer by the full n. */
struct queue02019f08 {
    unsigned int count;    /* offset 0 */
    unsigned char *ptr;    /* offset 4 */
};

void sub_02019f08(struct queue02019f08 *q, unsigned char value, unsigned int n)
{
    unsigned int i;
    unsigned int limit;
    unsigned char *p;

    if (n == 0)
        return;

    limit = q->count;
    i = 0;
    if (limit > n)
        limit = n;

    if (limit != 0) {
        p = q->ptr;
        do {
            p[i] = value;
            i++;
        } while (i < limit);
    }

    q->count -= limit;
    q->ptr += n;
}

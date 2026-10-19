/* Copies a 20-byte record. */
typedef struct {
    int w0;
    int w1;
    int w2;
    int w3;
    int w4;
} Rec20;

void copy_rec20(Rec20 *dst, const Rec20 *src)
{
    *dst = *src;
}

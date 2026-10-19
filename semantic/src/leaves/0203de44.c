/* Copies a 32-byte record. */
typedef struct {
    int w0;
    int w1;
    int w2;
    int w3;
    int w4;
    int w5;
    int w6;
    int w7;
} Rec32;

void copy_rec32(Rec32 *dst, const Rec32 *src)
{
    *dst = *src;
}

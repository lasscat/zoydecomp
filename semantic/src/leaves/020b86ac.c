/* Stores a constant pointer, two zero words and a trailing byte field. */
typedef struct {
    void *ptr;
    unsigned a;
    unsigned b;
    unsigned char c;
} Tagged;

void init_tagged(Tagged *p, unsigned char v)
{
    p->ptr = (void *)0x020f376cu;
    p->a = 0;
    p->b = 0;
    p->c = v;
}

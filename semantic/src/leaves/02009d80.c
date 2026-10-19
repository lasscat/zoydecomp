/* Resets a control block and installs its default mode word at +0xc. */
typedef struct {
    int f0;
    int f1;
    int f2;
    int f3;
    int f4;
    int f5;
    int f6;
    int f7;
} Ctl;

void init_ctl(Ctl *c)
{
    unsigned zero = 0;

    c->f2 = zero;
    c->f1 = zero;
    c->f0 = zero;
    c->f7 = zero;
    c->f6 = zero;
    c->f3 = zero | 0x2300;
    c->f4 = zero;
    c->f5 = zero;
}

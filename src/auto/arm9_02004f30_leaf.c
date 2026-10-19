/* Initialises eight 32-bit fields; fields 4 and 5 carry the arguments.
   The pointer is volatile so that the eight individual stores of the original
   are kept (clang otherwise merges them into block stores), and the statements
   are written in the store order the original emits (f1, f0, f3, f2). */
typedef struct {
    int f0;
    int f1;
    int f2;
    int f3;
    int f4;
    int f5;
    int f6;
    int f7;
} Block;

void pvz_02004f30_leaf(volatile Block *p, int a, int b)
{
    p->f1 = 0;
    p->f0 = 0;
    p->f3 = 0;
    p->f2 = 0;
    p->f4 = a;
    p->f5 = b;
    p->f6 = 0;
    p->f7 = 0;
}

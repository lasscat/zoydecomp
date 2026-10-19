/* Initialises six floats: 0, 50, 0, 0, 1, 1. */
typedef struct {
    float a;
    float b;
    float c;
    float d;
    float e;
    float f;
} Motion;

void init_motion(Motion *p)
{
    p->a = 0.0f;
    p->b = 50.0f;
    p->c = 0.0f;
    p->d = 0.0f;
    p->e = 1.0f;
    p->f = 1.0f;
}

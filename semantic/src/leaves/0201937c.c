/* arm9:0201937c - initialise a SHA-1 style context. */

typedef struct {
    unsigned int state[5];
    unsigned char buffer[64];
    unsigned int low;
    unsigned int mid;
    unsigned int high;
} Sha1Context;

void sha1_init(Sha1Context *ctx)
{
    ctx->mid = 0;
    ctx->high = 0;
    ctx->low = 0;
    ctx->state[0] = 0x67452301u;
    ctx->state[1] = 0xefcdab89u;
    ctx->state[2] = 0x98badcfeu;
    ctx->state[3] = 0x10325476u;
    ctx->state[4] = 0xc3d2e1f0u;
}

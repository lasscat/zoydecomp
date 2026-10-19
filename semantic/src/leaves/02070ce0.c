/* arm9:02070ce0 -- tests bit (n %% 8) of the byte at p + n / 8 + 0x70d
 * (the byte array member at 0x70d).  Reconstructed exactly. */
typedef unsigned char u8;
typedef struct { u8 pad[0x70d]; u8 bits[1]; } Obj;
int bit_is_set(Obj *p, int n)
{
    return (p->bits[n / 8] & (1 << (n % 8))) != 0;
}

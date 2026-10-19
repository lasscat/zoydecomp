/* arm9:0202dcb0 (40 bytes)
 * push {r4, lr}
 * ldr r4, [sp, #8]      ; r4 = byte argument d  (5th parameter)
 * str r3, [r0, #8]      ; this->f08 = c
 * strb r4, [r0, #0xc]   ; this->f0c = (byte)d
 * ldr lr, [sp, #0xc]    ; lr = 6th parameter
 * stm r0, {r1, r2}      ; this->f00 = a; this->f04 = b
 * ldr ip, [sp, #0x10]   ; ip = 7th parameter
 * str lr, [r0, #0x14]   ; this->f14 = e
 * str ip, [r0, #0x10]   ; this->f10 = f
 * pop {r4, pc}
 *
 * Stores every constructor argument into a fixed layout object. The two
 * high words are written in the order +0x14 then +0x10, and the first two
 * words are written as one paired store.
 */
struct Obj {
    unsigned int f00;      /* +0x00 */
    unsigned int f04;      /* +0x04 */
    unsigned int f08;      /* +0x08 */
    unsigned char f0c;     /* +0x0c */
    unsigned char pad0d[3];
    unsigned int f10;      /* +0x10 */
    unsigned int f14;      /* +0x14 */
};

void construct(struct Obj *this, unsigned int a, unsigned int b, unsigned int c,
               unsigned char d, unsigned int e, unsigned int f)
{
    this->f08 = c;
    this->f0c = d;
    this->f00 = a;
    this->f04 = b;
    this->f14 = e;
    this->f10 = f;
}

/* Writes four 16-bit rectangle coordinates; the fourth value is passed on the
   stack. The store order below reproduces the original emission order
   (0, 2, 4, 6); the only remaining difference is the original's sign extending
   stack load (ldrsh) versus clang's ldr. */
void set_rect_02039734(short *dst, short x, short y, short w, short h)
{
    dst[1] = y;
    dst[0] = x;
    dst[3] = h;
    dst[2] = w;
}

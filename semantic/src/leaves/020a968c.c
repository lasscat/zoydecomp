/* Publish the pixel size and the delay of one sprite variant.

    Variants 0..3 use a row of 0x78 pixels starting at 0x118 and a delay of
   0x54; higher variants step down by four rows, start at 0xdc and use a delay
   of 0xf6.  The size is written through the first out pointer and the delay
   through the second.  The first argument of the original is never read (the
   code starts by loading the row constant into r0 while the variant arrives
   in r1), so it is kept here as an unused parameter. */
void sprite_variant_size(int unused, int variant, int *out_size, int *out_delay)
{
    int delay;

    if (variant <= 3) {
        *out_size = variant * 0x78 + 0x118;
        delay = 0x54;
    } else {
        *out_size = (variant - 4) * 0x78 + 0xdc;
        delay = 0xf6;
    }
    *out_delay = delay;
}

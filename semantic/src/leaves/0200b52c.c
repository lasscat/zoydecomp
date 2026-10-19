/* Reports the length of the inner record reached through the second
 * argument+0x04 as inner+0x08 minus inner+0x04; the first argument is unused
 * and the function returns 0. */
struct UnknownInner {
    unsigned char unknown_0x00_0x03[4];
    int begin_0x04;
    int end_0x08;
};

struct UnknownOuter {
    unsigned char unknown_0x00_0x03[4];
    struct UnknownInner *inner_0x04;
};

int pvz_0200b52c_length_of_inner(unsigned int unused, struct UnknownOuter *outer,
                                 int *length_out)
{
    struct UnknownInner *inner = outer->inner_0x04;

    *length_out = inner->end_0x08 - inner->begin_0x04;
    return 0;
}

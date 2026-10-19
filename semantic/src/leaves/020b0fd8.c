/*
 * arm9:020b0fd8  (32 bytes)
 *
 *   ldr   r0, [r0]           ; *arg
 *   ldr   r0, [r0, #0x688]   ; inner pointer
 *   add   r0, r0, #0x100
 *   ldrsh r0, [r0]           ; signed 16-bit field at inner + 0x100
 *   cmp   r0, #0
 *   movne r0, #1
 *   moveq r0, #0
 *   bx    lr
 *
 * Two-level dereference: reads a signed 16-bit field 0x100 bytes into the
 * object found at +0x688 of the object found through the argument, and
 * reports whether it is non-zero.
 */
struct Inner_020b0fd8 {
    unsigned char pad_0x00[0x100];
    short field_0x100;
};

struct Outer_020b0fd8 {
    unsigned char pad_0x00[0x688];
    struct Inner_020b0fd8 *inner_0x688;
};

int pvz_020b0fd8(void **handle)
{
    struct Outer_020b0fd8 *outer = (struct Outer_020b0fd8 *)*handle;

    return outer->inner_0x688->field_0x100 != 0;
}

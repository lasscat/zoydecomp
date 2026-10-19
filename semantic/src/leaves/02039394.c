/* Tagged variant payload.  Bit 0 of variant+0x00 selects the payload word at
 * +0x08; otherwise the address one past the variant is returned (the inline
 * form stores its bytes from +0x01 on).  The original extracts bit 0 by
 * shifting the word left 31 bits and back right 31 bits, so the equivalent
 * shift pair is written out (a plain & 1 makes clang emit a byte load and a
 * test instead of the original's word load). */
struct UnknownVariant {
    unsigned int tagged_0x00;
    unsigned int unknown_0x04;
    void *payload_0x08;
};

void *pvz_02039394_payload(struct UnknownVariant *variant)
{
    unsigned int low_bit = (variant->tagged_0x00 << 31) >> 31;

    if (low_bit) {
        return variant->payload_0x08;
    }
    return (unsigned char *)variant + 1;
}

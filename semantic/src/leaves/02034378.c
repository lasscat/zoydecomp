/* arm9:02034378 (40 bytes)
 *
 * Tag check. Returns 1 when the word at +0 of the object is neither of the two
 * accepted tags, 0 when it matches either one.
 *   r1 = *(int *)self
 *   tag0 = 0x4c5a5353  ('LZSS' stored little-endian)
 *   tag1 = 0x53535a4c
 *   r2 = 1; if (r1 == tag0 || r1 == tag1) r2 = 0
 *   return (signed char)r2   ; lsl #0x18 / asr #0x18
 *
 * Unknown offset note: the return value is narrowed to 8 bits by the original
 * (lsl/asr pair), so the accepted-tag test result is a signed byte.
 */
int pvz_02034378_unknown_tag(char *self)
{
    unsigned int tag = *(unsigned int *)self;
    int unknown = !(tag == 0x4c5a5353u || tag == 0x53535a4cu);
    return (signed char)unknown;
}

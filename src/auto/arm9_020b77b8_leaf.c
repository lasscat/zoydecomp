/* Reports whether the signed word at +0x14 is greater than or equal to the
 * signed word at +0x10. */
struct UnknownProgress {
    unsigned char unknown_0x00_0x0f[0x10];
    int current_0x10;
    int limit_0x14;
};

int pvz_020b77b8_leaf(struct UnknownProgress *progress)
{
    return progress->limit_0x14 >= progress->current_0x10;
}

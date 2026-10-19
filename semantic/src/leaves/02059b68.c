/* True for the two special identifiers 0x0b and 0x0e. The original if-converts
   the two comparisons (cmp/cmpne/moveq/movne); clang emits a branchy sequence
   of 32 bytes. */
int is_special_02059b68(unsigned int id)
{
    return id == 0x0b || id == 0x0e;
}

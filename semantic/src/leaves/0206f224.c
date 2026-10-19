/* Reports whether the second argument equals 0x41; the first argument is
 * unused (the original compares r1). */
int pvz_0206f224_is_code(unsigned int unknown, unsigned int code)
{
    return code == 0x41;
}

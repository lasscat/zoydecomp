/* Reports whether a value is one of the special codes handled by the caller. */
int is_special_code(int code)
{
    return code == 8 || code == 0x18 || code == 9 || code == 0xa
        || code == 0xc || code == 0xf || code == 0xe || code == 0x1f
        || code == 0xd || code == 0x2a;
}

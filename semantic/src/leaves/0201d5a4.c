/* Unknown string copy helper: copies the NUL-terminated string at src into dst
 * and returns dst. When dst and src share the same 4-byte alignment it copies
 * whole words until a zero byte is detected, otherwise it falls back to plain
 * byte copies. Only the observed DS value effect is modeled. Independently
 * reconstructed from BWBE-r0 ARM9 0x0201d5a4. */
typedef unsigned int u32;

char *pvz_0201d5a4_copy(char *dst, const char *src)
{
    char *d = dst;
    u32 align = (u32)dst & 3u;

    if (((u32)src & 3u) != align)
        goto bytes;
    while (align != 0u) {
        char c = *src++;
        *d++ = c;
        if (c == 0)
            return dst;
        align = (u32)d & 3u;
    }
    for (;;) {
        u32 w = *(const u32 *)src;
        if (((w - 0x01010101u) & ~w & 0x80808080u) != 0u)
            break;
        *(u32 *)d = w;
        d += 4;
        src += 4;
    }
bytes:
    for (;;) {
        char c = *src++;
        *d++ = c;
        if (c == 0)
            return dst;
    }
}

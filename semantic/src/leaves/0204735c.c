/* arm9:0204735c -- reads one packed 2-byte entry: bit 0 of the flag word
 * selects either an inline 7-bit size in the first byte (and reports the
 * pointer two bytes on) or a word pair at +4/+8.  N: two instructions differ
 * (shift written into r3 instead of r0, and one ldr/str scheduling order). */
typedef unsigned int u32;
typedef unsigned char u8;
typedef struct { unsigned int flag : 1; } FlagWord;
typedef struct { u8 flag : 1; u8 size : 7; u8 pad; } Entry;
void read_entry(const FlagWord *p, u32 *out, u32 *value)
{
    u32 v;
    if (p->flag == 0) {
        const Entry *q = (const Entry *)p;
        v = q->size;
        q++;
        *out = (u32)q;
    } else {
        *out = ((const u32 *)p)[2];
        v = ((const u32 *)p)[1];
    }
    *value = v;
}

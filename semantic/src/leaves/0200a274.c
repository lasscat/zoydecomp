/* Builds an eight-byte pair: first word from a global, second word from the
   source object's field at offset 0x18.  The pair is returned by value, which
   the ARM ABI passes through a hidden destination pointer in r0. */
typedef struct {
    unsigned first;
    unsigned second;
} Pair;

Pair make_pair(void *src)
{
    Pair r;
    r.first = *(unsigned *)0x020ff51cu;
    r.second = *(unsigned *)((char *)src + 0x18);
    return r;
}

/* arm9:020c7ee4 -- reviewed extent of 52 bytes that is NOT one function.
 *
 * The original bytes contain three consecutive entries, each with its own
 * literal pool at the end of its code:
 *   0x020c7ee4  ldr r0,[pc,#4]; ldr ip,[pc,#4]; bx ip   (r0 = 0x020c7e7c,
 *                                                        ip = 0x0203763c)
 *   0x020c7ef8  ldr ip,[pc,#4]; mov r0,#0; bx ip         (ip = 0x0203763c)
 *   0x020c7f08  ldr r1,[pc,#4]; str r0,[r1,#0x44]; bx lr (r1 = 0x021de480)
 *
 * The first two are indirect tail jumps (no return address is built).  The
 * measured MWCC profile emits a returning indirect call instead -- push {lr},
 * ldr r1,<target>, bx r1, pop {pc} -- and it emits one .text section per
 * function, so a single C function cannot produce this extent.  The third
 * entry alone is expressible; it needs the base 0x021de480 to stay in the pool
 * with 0x44 as the store offset, which the struct form below provides.
 *
 * Natural C cannot express the jump thunks; recorded blocked. */
typedef unsigned int u32;

typedef struct {
    u32 pad[0x11];
    u32 field;
} Obj;

int stub_first(void)
{
    return ((int (*)(const void *))0x0203763cu)((const void *)0x020c7e7cu);
}

int stub_second(void)
{
    return ((int (*)(u32))0x0203763cu)(0u);
}

void stub_store(u32 v)
{
    ((Obj *)0x021de480u)->field = v;
}

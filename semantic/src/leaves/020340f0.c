/* Unknown heap/free-list helper: splits the block at p when at least 0x48 bytes
 * remain, links the tail block ahead of p, reduces p->size, and coalesces the
 * tail with the following block when that block is free.
 * Record identity and field meanings are unknown; only the observed DS value
 * effect is modeled. Independently reconstructed from BWBE-r0 ARM9 0x020340f0. */
typedef unsigned int u32;

struct PvzBlock {
    u32 tag;
    struct PvzBlock *prev;
    struct PvzBlock *next;
    u32 inuse;
    u32 size;
    u32 unknown_0x14;
    u32 unknown_0x18;
    u32 unknown_0x1c;
    u32 unknown_0x20;
    u32 unknown_0x24;
};

void pvz_020340f0_split(u32 *arena, struct PvzBlock *p, u32 size)
{
    struct PvzBlock *tail;
    u32 remain = p->size - size;

    if (remain < 0x48u)
        return;
    tail = (struct PvzBlock *)((char *)p + size);
    tail->size = remain;
    tail->inuse = 0u;
    tail->tag = *arena;
    tail->unknown_0x20 = 0u;
    tail->unknown_0x24 = 0xffffffffu;
    if (p->next != 0)
        p->next->prev = tail;
    tail->next = p->next;
    tail->prev = p;
    p->next = tail;
    p->size = p->size - tail->size;
    if (tail->next == 0)
        return;
    if (tail->next->inuse != 0)
        return;
    tail->size = tail->size + tail->next->size;
    tail->next = tail->next->next;
    if (tail->next != 0)
        tail->next->prev = tail;
}

/* Selftest data reused verbatim by the original at a second address: clears
 * the seven words of a slot record and sets the word at +0x14 to 1. */
struct UnknownSlot {
    unsigned int unknown_0x00;
    unsigned int unknown_0x04;
    unsigned int unknown_0x08;
    unsigned int unknown_0x0c;
    unsigned int unknown_0x10;
    unsigned int initialized_0x14;
    unsigned int unknown_0x18;
};

void pvz_02067f40_init_slot(struct UnknownSlot *slot)
{
    slot->unknown_0x00 = 0;
    slot->unknown_0x04 = 0;
    slot->unknown_0x08 = 0;
    slot->unknown_0x0c = 0;
    slot->unknown_0x10 = 0;
    slot->initialized_0x14 = 1;
    slot->unknown_0x18 = 0;
}

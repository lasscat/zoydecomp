/* Act on the lowest set bit of a 22-bit button mask.

   Bit 0 is tested first.  Each step shifts the mask right by one, advances
   the per-bit word table at 0x027E0000 by one word and advances the bit
   number.  Set bits 8..11 are remapped to action records 0..3 of the
   12-byte-record table at 0x020FD35C and set bits 3..6 to records 4..7;
   every other set bit reports the word stored in the per-bit table.  The
   routine returns 0 when no bit is set. */
struct action {
    int kind;
    int arg0;
    int arg1;
};

int button_action(unsigned buttons)
{
    int i = 0;
    const int *per_bit = (const int *)0x027e0000u;
    const struct action *actions = (const struct action *)0x020fd35cu;

    do {
        if (buttons & 1) {
            if (i >= 8 && i <= 11)
                return actions[i - 8].kind;
            if (i >= 3 && i <= 6)
                return actions[i + 1].kind;
            return *per_bit;
        }
        buttons >>= 1;
        per_bit++;
        i++;
    } while (i < 0x16);
    return 0;
}

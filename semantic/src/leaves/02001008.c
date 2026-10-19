/* Binary search for a signed 16-bit key in a four-byte-stride table.

   The searched value is the low halfword of each entry of the table at
   0x020CFA48.  A non-negative value is looked up in entries 0..0x400 and a
   negative value in entries 0xC00..0x1000, so the caller's raw value selects
   which half of the table is probed.  The routine returns the entry index
   scaled by 16, kept as a 16-bit value.

   The final scaling is written as a shift and a fixed-point divide because
   that is the spelling this build recurses to: the original emits
   (mid << 17) / 8192 with a sign correction, i.e. mid * 16.  The index is
   only defined when the range check passes; the original likewise leaves it
   undefined on the never-taken empty-range path. */
int lookup_entry(int value)
{
    const short *table = (const short *)0x020cfa48u;
    int lo;
    int hi;
    int mid;
    short key;

    if (value >= 0) {
        lo = 0;
        hi = 0x400;
    } else {
        lo = 0xc00;
        hi = 0x1000;
    }
    key = (short)value;

    if (lo <= hi) {
        do {
            mid = (lo + hi) / 2;
            if (table[mid * 2] == key)
                break;
            if (table[mid * 2] < key)
                lo = mid + 1;
            else
                hi = mid - 1;
        } while (lo <= hi);
    }
    return (unsigned short)((mid << 17) / 8192);
}

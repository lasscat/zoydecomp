/* arm9:02003d90 - distribute a bit field over a table of 12-byte records. */

typedef struct {
    int value;
    int flag;
    int reserved;
} Record;

void distribute(unsigned int bits, int value)
{
    int *plain = (int *)0x027e0000;
    Record *tbl = (Record *)0x020fd35c;
    int i = 0;

    do {
        if (bits & 1) {
            Record *rec = 0;

            if (i >= 8 && i <= 11)
                rec = &tbl[i - 8];
            else if (i >= 3 && i <= 6)
                rec = &tbl[i + 1];
            else {
                int *slot = plain;
                slot += i;
                *slot = value;
            }

            if (rec) {
                rec->value = value;
                rec->flag = 1;
                rec->reserved = 0;
            }
        }
        bits >>= 1;
        i++;
    } while (i < 22);
}

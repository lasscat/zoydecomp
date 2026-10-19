/* 0x020c0fe0: copy one 5-halfword row of a 674-row table located at
 * 0x020F6358 into out. Returns 0 for an out-of-range row, else 1. */
int ReadTableRow(short *out, unsigned int row)
{
    const short (*table)[5] = (const short (*)[5])0x020F6358;
    int k;

    if (row >= 674)
        return 0;
    for (k = 0; k < 5; k++)
        out[k] = table[row][k];
    return 1;
}

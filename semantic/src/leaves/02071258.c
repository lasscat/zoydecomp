/* Scales the argument by 0xa01/0x1000 with an arithmetic shift (about 0.625x,
   the classic 2D scale factor). */
int scale_02071258(int value)
{
    return (value * 0xa01) >> 12;
}

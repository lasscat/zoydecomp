/* index = first + third + second * 10000 (an index into a table with 10000
   entries per block). */
int index_02066858(int first, int second, int third)
{
    return second * 10000 + (first + third);
}

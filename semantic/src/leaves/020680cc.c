/* arm9:020680cc
 * Initialise a 7-word record: words 0..4 are 0, word 5 is 1, word 6 is 0.
 */
void init_record(unsigned int *p)
{
    p[0] = 0;
    p[1] = 0;
    p[2] = 0;
    p[3] = 0;
    p[4] = 0;
    p[5] = 1;
    p[6] = 0;
}

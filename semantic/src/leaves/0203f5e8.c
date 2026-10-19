/* Takes and clears the word field at offset 4. */
unsigned take_word4(unsigned *p)
{
    unsigned v = p[1];
    p[1] = 0;
    return v;
}

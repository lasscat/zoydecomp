/* Set the byte at offset +0x63 of the record to 1. */
void rec_set_flag(char *p)
{
    p[0x63] = 1;
}

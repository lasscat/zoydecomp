/* Store one word into a global integer table indexed by id.
 * Address recomputed as 0x02FF0000 + id*4, element written at +0xDA0.
 * Base 0x02FF0000 is not the object start; 0xDA0 is an offset into it. */
void set_slot(int id, int value)
{
    *(int *)(0x02FF0000 + id * 4 + 0xDA0) = value;
}

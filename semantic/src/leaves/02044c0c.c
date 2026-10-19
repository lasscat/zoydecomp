/* Publishes the address four bytes past the supplied record into the caller's
 * slot (a begin-iterator over the payload of a reference counted record). */
void pvz_02044c0c_begin(void **iterator_out, void *record)
{
    *iterator_out = (unsigned char *)record + 4;
}

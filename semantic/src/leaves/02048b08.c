/* arm9:02048b08
 * Store p[1] and p[2] into the two words of the object pointed to by p[0].
 * p[0] is read again for the second store because the first store may alias it.
 */
void set_target_pair(unsigned int *p)
{
    ((unsigned int *)p[0])[0] = p[1];
    ((unsigned int *)p[0])[1] = p[2];
}

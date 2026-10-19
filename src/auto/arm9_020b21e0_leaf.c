/* Adds the base word at table+0x08 to the `index` entry of the word table
 * pointed to by table+0x04. */
struct UnknownThing {
    unsigned int unknown_0x00;
    unsigned int *entries_0x04;
    unsigned int base_0x08;
};

unsigned int pvz_020b21e0_leaf(struct UnknownThing *thing, int index)
{
    return thing->base_0x08 + thing->entries_0x04[index];
}

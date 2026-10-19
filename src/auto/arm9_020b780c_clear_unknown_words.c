/* Unknown output record: clears four words and stores value at +0x0c.
 * Record identity and field meanings are unknown; only the observed DS effect
 * is modeled. Independently reconstructed from BWBE-r0 ARM9 0x020b780c. */
void pvz_020b780c_clear_unknown_words(void *record, unsigned int value)
{
    volatile unsigned int *words = (volatile unsigned int *)record;
    words[0] = 0u;
    words[1] = 0u;
    words[2] = 0u;
    words[3] = value;
    words[4] = 0u;
}

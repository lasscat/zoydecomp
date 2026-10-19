/* Unknown owner and slots: writes at byte offsets 0x5ad8..0x5ae0. */
void pvz_0206645c_write_unknown_slots(void *owner,
                                       unsigned int value_a,
                                       unsigned int value_b) {
    volatile unsigned int *words = (volatile unsigned int *)
        ((volatile unsigned char *)owner + 0x5000);
    words[0x2b6] = 12u;
    words[0x2b7] = value_a;
    words[0x2b8] = value_b;
}

/* Unknown owner layout: nested pointer at +0x688; nested word at +0x0c. */
int pvz_0206f360_test_unknown_nested_positive(void *owner) {
    volatile unsigned int *nested = *(volatile unsigned int **)
        ((volatile unsigned char *)owner + 0x688);
    return nested != 0 && (int)nested[3] > 0;
}

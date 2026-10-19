/* arm9:0206ee14 (8 bytes)
 *
 * Word getter whose object arrives in the *second* argument register.
 *   ldr r0, [r1, #0x208]
 *   bx  lr
 *
 * Unknown offset note: +0x208 is a 32-bit field. The first argument register
 * (r0) is not read at all, so the source keeps a leading unused parameter to
 * place the object pointer in r1.
 */
int pvz_0206ee14_leaf(int unused, char *self)
{
    (void)unused;
    return *(int *)(self + 0x208);
}

/* arm9:020bdb78 (40 bytes)
 *
 * Registers a callback pair into the fixed two-word slot at 0x020f3ae4,
 * substituting built-in defaults when either argument is NULL.
 *   r2 = 0x020f3ae4
 *   *(int *)(r2 + 0) = fn    ; also conditional on fn
 *   *(int *)(r2 + 4) = data
 *   if (fn   == 0) *(int *)(r2 + 0) = 0x020d77a4
 *   if (data == 0) *(int *)(r2 + 4) = 0x020d778c
 *   bx lr
 *
 * Unknown offset note: 0x020d77a4 / 0x020d778c are the default function and
 * default data objects; the slot is written unconditionally first, then the
 * defaults overwrite the zero arguments.
 */
void pvz_020bdb78_register(int *fn, int *data)
{
    int **slot = (int **)0x020f3ae4u;
    slot[0] = fn;
    slot[1] = data;
    if (fn == 0)
        slot[0] = (int *)0x020d77a4u;
    if (data == 0)
        slot[1] = (int *)0x020d778cu;
}

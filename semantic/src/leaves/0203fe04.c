/* arm9:0203fe04
 * Forwards the two incoming arguments to the routine at 0x0203FD50 with a zero
 * third argument.
 */
void forward_call(int a, int b)
{
    ((void (*)(int, int, int))0x0203FD50)(a, b, 0);
}

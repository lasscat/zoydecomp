/* Conditional flag update, written with the repeated dereferences the
 * original performs (each side reads its fields independently). */
void apply_flag(char *self)
{
    if (*(int *)(self + 0xc0) != -1) {
        int *sub = *(int **)(self + 0xb8);
        sub[0x88 / 4] |= 2;
        *(unsigned short *)((char *)*(int **)(self + 0xb8) + 0x8e) = *(int *)(self + 0xc0);
    } else {
        int *sub = *(int **)(self + 0xb8);
        sub[0x88 / 4] &= ~2;
    }
}

/* Zeroes the first two words and links the pointer at +0xC back to +4. */
void func_02042d78(char *p) {
    *(int *)(p + 0) = 0;
    *(int *)(p + 4) = 0;
    *(void **)(p + 0xC) = p + 4;
}

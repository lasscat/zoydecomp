/* Copies two signed bytes from the argument to +8/+9 of 0x02108970. */
void func_020b1af8(char *src) {
    char *dst = (char *)0x02108970u;
    *(signed char *)(dst + 8) = *(signed char *)(src + 0);
    *(signed char *)(dst + 9) = *(signed char *)(src + 1);
}

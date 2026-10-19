/* arm9:02044414
 * Clears the 0xff-byte buffer reached through obj+0x2a4 (first entry at +0xfc)
 * and the two flag bytes at obj+0x4de / obj+0x4df.
 *
 * The object is qualified volatile so that the original's two independent
 * reads of the +0x2a4 pointer and its two separate byte stores to +0x4de /
 * +0x4df are preserved.  Without volatile this compiler folds the two byte
 * stores into one halfword store and keeps the pointer in a register.
 * Volatile only reproduces the original store/load order; the emitted
 * instructions remain plain strb / ldr.
 */
void sub_02044414(volatile char *obj)
{
    if (*(void *volatile *)(obj + 0x2a4) != 0) {
        int i;

        for (i = 0; i < 0xff; i++)
            *((unsigned char *)*(void *volatile *)(obj + 0x2a4) + 0xfc + i) = 0;
    }
    obj[0x4de] = 0;
    obj[0x4df] = 0;
}

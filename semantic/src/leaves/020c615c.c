/* Stores a word in the field at +0x14 of the object at 0x021DB040. */
struct state_021db040 {
    char pad[0x14];
    int value;
};

void func_020c615c(int v) {
    ((struct state_021db040 *)0x021DB040u)->value = v;
}

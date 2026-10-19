/* True when the argument, biased by 0x28, lies in the eight element window
   0x28..0x2f. clang recognises the power-of-two range test and emits
   bic/sub/clz/lsr instead of the original's sub/cmp/movls/movhi. */
int pvz_0207b008_leaf(unsigned int value) { return (value - 0x28) <= 7; }

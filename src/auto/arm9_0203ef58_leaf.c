/* True when bit 0 of the word at +8 is set. */
int pvz_0203ef58_leaf(char *p) { return (*(unsigned int *)(p + 8) & 1) ? 1 : 0; }

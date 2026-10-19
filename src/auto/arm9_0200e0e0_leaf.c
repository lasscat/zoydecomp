/* Combines three base-60 fields into a single count. */
int pvz_0200e0e0_leaf(int *t) { return (t[0] * 60 + t[1]) * 60 + t[2]; }

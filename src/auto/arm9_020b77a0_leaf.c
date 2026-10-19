/* Rounds a field up to the next multiple of eight (signed division). */
int pvz_020b77a0_leaf(int *p) { return (p[4] + 7) / 8; }

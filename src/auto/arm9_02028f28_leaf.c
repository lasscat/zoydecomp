/* Returns entry 'index' of the pointer table whose first payload word sits at
   offset 8 of the argument (base[index + 2]). */
unsigned int pvz_02028f28_leaf(unsigned int *base, unsigned int index) { return base[index + 2]; }

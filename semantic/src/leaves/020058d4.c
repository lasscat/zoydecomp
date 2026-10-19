/* Read the ARM946E-S cache-configuration register (coproc 15, c9, c1, 0)
   and keep only the base-address bits (low 12 bits hold the region size /
   enable flags and are masked away). */
unsigned cache_config_base(void)
{
    unsigned val = (unsigned)__builtin_arm_rsr("cp15:0:c9:c1:0");

    return val & 0xFFFFF000u;
}

/* Tests bit 31 of the second argument and returns it as a boolean.
   The original prologue is `push {r0, r1, r2, r3}` plus a reload of [sp, #4],
   i.e. an argument save area (stack passed or variadic argument). Optimised
   clang keeps the argument in r1 and emits eight bytes instead of 28. */
int high_bit_0201ae74(int a, int b)
{
    return (b & 0x80000000) != 0;
}

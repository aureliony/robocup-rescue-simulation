#pragma once

// unsigned long long rdtsc()//seeder
// {
//     unsigned int lo,hi;
//     __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
//     return ((unsigned long long)hi << 32) | lo;
// }
// mt19937 rng(rdtsc());

#include <random>

mt19937 rng;

static inline int randint(int lower,int upper)
{
    uniform_int_distribution<mt19937::result_type> udist(lower, upper);
    return udist(rng);
}

#endif
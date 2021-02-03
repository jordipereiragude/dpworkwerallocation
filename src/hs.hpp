#pragma once

#include <boost/multi_array.hpp>

#include "instance.hpp"
#include "solution.hpp"

unsigned setupRandom(unsigned seed);
Solution optW(const Instance& I, const std::vector<unsigned>& w); // optimal for fixed permutation
Solution sample(const Instance& I, int n); // sample n permutations

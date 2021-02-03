#pragma once

#include <iostream>
#include <vector>

#include "instance.hpp"

struct Solution {
  const Instance *I;
  std::vector<unsigned> w; // worker permutation
  std::vector<unsigned> l; // number of tasks in worker's segment
  Time value;

  Solution(const Instance& I) : I(&I), value(inf_time) {}
  Solution(const Instance& I, int m) : I(&I), w(m), l(m,0), value(inf_time) {
    std::iota(w.begin(),w.end(),0);
  }

  bool isValid() const { return value < inf_time; }

  friend std::ostream& operator<<(std::ostream&, const Solution&);
};

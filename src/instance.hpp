#pragma once

#include <iostream>
#include <vector>

#include <boost/multi_array.hpp>
#include "dimensions.hpp"

const long precision = 1000000;

struct Instance {
  unsigned n;			// number of tasks
  unsigned m;			// number of workers
  unsigned c;			// cycle time
  unsigned B;			// batch size

  std::vector<Time> s;		// standard times
  boost::multi_array<Time,2> t;	// execution times; t[i,w] for task i=[0,n-1], worker w=[0,m-1]

  boost::multi_array<Time,2> T;	// prefix sums of execution times; T[i,w]=sum(t[0,i-1][w]) for (excl) task i=[0,n], worker w=[0,m-1]
  boost::multi_array<unsigned long,2> d; // prefix sums of task times, with fixed precision
  void computeD();

  void readSTD(std::istream&);	  // read from stream in STD format

  int getB();
  double segCost(int i, int j, int w) const;
};

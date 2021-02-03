#include "hs.hpp"

#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <random>
using namespace std;

#include <boost/multi_array.hpp>
using namespace boost;

mt19937 rng;

unsigned setupRandom(unsigned seed) {
  rng.seed(seed);
  return seed;
}

// optimal solution for fixed permutation
Solution optW(const Instance& I, const vector<unsigned>& w) {
  Solution result(I);
  result.w = w;
  result.l.resize(I.m);

  boost::multi_array<Time,2> C(extents[I.n+1][I.m+1]);
  boost::multi_array<int,2> l(extents[I.n+1][I.m+1]);

  for(unsigned i=0; i!=I.n; i++)
    C[i][I.m]=inf_time;
  for(unsigned j=0; j!=I.m+1; j++)
    C[I.n][j]=0;

  for(int j=I.m-1; j>=0; j--) {
    for(int i=I.n-1; i>=0; i--) {
      C[i][j]=inf_time;
      Time c = 0.0;
      for(unsigned k=i; k!=I.n+1; k++) {
	Time c_ = max(c,C[k][j+1]);
	if (c_<C[i][j]) {
	  C[i][j]=c_;
	  l[i][j]=k-i;
	}
	if (k<I.n)
	  c += I.t[k][w[j]];
      }
    }
  }
  unsigned i = 0, j = 0;
  while (i<I.n) {
    result.l[j] = l[i][j];
    i += l[i][j];
    j += 1;
  }
  result.value = C[0][0];
  return result;
}

Solution sample(const Instance& I, int n) {
  Solution S(I);

  vector<unsigned> w(I.m);
  iota(w.begin(),w.end(),0);
  while (n-->0) {
    shuffle(w.begin(),w.end(),rng);
    Solution c = optW(I,w);
    if (c.value<S.value)
      S = c;
  }
  return S;
}

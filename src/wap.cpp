#include <iostream>
#include <cstdlib>
#include <fstream>
#include <chrono>
#include <random>
using namespace std;

#include "hs.hpp"
#include "instance.hpp"
#include "dp.hpp"

int main(int argc, char *argv[]) {
  // (0) process commandline
  auto start = chrono::steady_clock::now();
  if(argc<3) {
    cout << argv[0] << " instance seed" << endl;
    return 0;
  }

  // (1) random seed
  unsigned seed = setupRandom(atoi(argv[2]));

  // (2) read the instance
  Instance I;
  ifstream in(argv[1]);
  if (!in.is_open()) {
    cerr << "Cannot open " << argv[1] << endl;
    exit(1);
  }
  I.readSTD(in);
  in.close();

  vector<int> w(I.m);
  iota(w.begin(),w.end(),0);

  //(3) compute a trivial seed solution
  Solution S = sample(I,1);
  Solution C(S);
  Time initial = S.value;

  auto startDP = chrono::steady_clock::now();
  S=iterativeApproach(I,S);
  auto finish = std::chrono::steady_clock::now();
  double dpSeconds = std::chrono::duration_cast< std::chrono::duration<double> >(finish - startDP).count();
  double totalSeconds = std::chrono::duration_cast< std::chrono::duration<double> >(finish - start).count();
  cout << "instance: " << argv[1] << " seed: " << seed << " initialSolution: " << initial << " dpSolution " << S.value << " dpTime: " << dpSeconds << " totalTime: " << totalSeconds << endl;
  return 0;
}

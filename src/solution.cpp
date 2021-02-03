#include "solution.hpp"

#include <iostream>
#include <iomanip>
using namespace std;

ostream& operator<<(ostream &o, const Solution& s) {
  o << endl;
  if (!s.isValid())
    return o << "Infeasible  cycle Inf" << endl;

  const int wd = 5;
  for(int k=0,ke=s.w.size(); k!=ke; k++)
    o << setw(wd) << k+1 << " ";
  o << endl;
  for(int k=0,ke=s.w.size(); k!=ke; k++)
    o << string(wd+1,'-');
  o << endl;
  for(int k=0,ke=s.w.size(); k!=ke; k++)
    o << setw(wd) << s.w[k]+1 << " ";
  o << endl;
  int nt = 0;
  for(int k=0,ke=s.w.size(); k!=ke; k++) {
    //o << setw(wd) << nt << " ";
    o << setw(wd) << s.l[k] << " ";
    nt+=s.l[k];
  }
  o << endl;
  nt = 0;
  for(int k=0,ke=s.w.size(); k!=ke; k++) {
    //o << setw(wd) << nt << " ";
    o << setw(wd) << s.I->segCost(nt,nt+s.l[k]-1,s.w[k]) << " ";
    nt+=s.l[k];
  }
  return o << "  cycle " << s.value << endl;
}

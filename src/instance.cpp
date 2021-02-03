#include "instance.hpp"

using namespace std;
using namespace boost;

double Instance::segCost(int i, int j, int w) const {
  return T[j+1][w]-T[i][w];
}

void Instance::readSTD(std::istream& in) {
  string line;
  in >> n; getline(in,line);
  in >> m; getline(in,line);
  getline(in,line);

  s.resize(n);
  for(unsigned i=0; i!=n; i++) in >> s[i];
  B = getB();

  vector<Time> s_(n*B);
  for(unsigned i=0; i!=n; i++)
    fill(s_.begin()+i*B,s_.begin()+i*B+B,s[i]);
  s.swap(s_);

  getline(in,line);
  getline(in,line);
  t.resize(extents[n*B][m]);
  for(unsigned w=0; w!=m; w++) {
    for(unsigned i=0; i!=n; i++) {
      Time ct;
      in >> ct;
      for(unsigned j=0; j!=B; j++) t[i*B+j][w]=ct;
    }
  }
  n *= B;
  computeD();
}

void Instance::computeD() {
  T.resize(extents[boost::multi_array_types::extent_range(0,n+1)][m]);
  d.resize(extents[boost::multi_array_types::extent_range(-1,n)][m]);
  for(unsigned j=0;j!=m;j++) { //for each worker
    T[0][j]=0.0;
    for(unsigned i=1;i<=n;i++) // accumulate over tasks
      T[i][j]=T[i-1][j]+t[i-1][j];
  }
  for(unsigned j=0;j!=m;j++) { //for each worker
    d[-1][j]=0;
    for(int i=0;i<int(n);i++) // accumulate over tasks
      d[i][j]=d[i-1][j]+t[i][j]*precision;
  }
}

int Instance::getB() {
  Time sum = accumulate(s.begin(),s.end(),0.0);
  return floor(double(60*m)/sum);
}

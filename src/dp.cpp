#include <boost/multi_array.hpp>
#include <boost/heap/pairing_heap.hpp>

#include <queue>
#include <map>

#include "hs.hpp"

using namespace std;
using namespace boost;

//macros for generating key for the map d is the data, n is the bit number
#define setbit(d,n)   ((d) |=  (1<<(n)))
#define unsetbit(d,n) ((d) &= ~(1<<(n)))
#define checkbit(d,n) ((d) &   (1<<(n)))

// shared map to use in pqOrder (should pass as a parameter to the compare function (define as a struct, etcetera)
map<unsigned long,int> avoidRepetition;  //key is an integer bitset to consider only one copy of a DP states in the exploration.

bool pqOrder(unsigned long a, unsigned long b) {
  return avoidRepetition[a]>avoidRepetition[b];
}

Solution decode(const Instance& I, unsigned long current, unsigned long currentC) {
  vector<unsigned> vWorkers(I.m);
  int t = I.n-1;
  for(int depth=I.m-1; depth>0; depth--) { // setting up worker at position depth
    for(unsigned w=0; w<I.m; w++) {
      if(checkbit(current,w)>0) {   //if assigned, it may be the worker assigned to the said position
        unsetbit(current,w);
        //look if it exists in avoidRepetition
        auto it=avoidRepetition.find(current);
        if (it!=avoidRepetition.end()) { //if it exists, it may be the worker in depth position (otherwise, we are sure that it is not the case
          if ((I.d[t][w]-I.d[it->second][w])<currentC) {   // requires less than current c, means it is possible to construct the path
            // "selected " << w << " tasks: " << t << " cost " << I.d[t][w]-I.d[it->second][w] << " currentC " << currentC
            vWorkers[depth]=w;
            t=it->second;
            //l is missing
            break; //stop loop
          }
        }
        setbit(current,w); //if it arrives here, it means it is not this worker
      }
    }
  }
  for(unsigned i=0; i<I.m; i++) {
    if (checkbit(current,i)>0) {
      vWorkers[0]=i;
      unsetbit(current,i);
      break;
    }
  }
  //sequence is ready.
  return optW(I,vWorkers);
}

Solution feasibleDP(const Instance &I, Solution &S, unsigned long currentC) {
  map<unsigned long,int>::iterator it;  //key is an integer bitset to consider only one copy of a DP state in the exploration.
  priority_queue<unsigned long,std::vector<unsigned long>, std::function<bool(unsigned long,unsigned long)>> oldStates(pqOrder); //must order from worst to best element according to value recorded in map
  vector<unsigned long> newStates;
  unsigned long current=0;	// current state (allocated workers)
  unsigned int maxValue, t;
  int performedTasks;		// number of last performed task

  avoidRepetition.clear();

  oldStates.push(current);
  avoidRepetition[current]=(-1);
  for(unsigned depth=0;depth<I.m;depth++) {
    while(!(oldStates.empty())) {
      current=oldStates.top();
      performedTasks=avoidRepetition[current];
      oldStates.pop();
      for(unsigned w=0;w<I.m;w++) { //check all workers
        if(checkbit(current,w)==0) { //unassigned
          setbit(current,w);
          //we must look at the number of tasks that the worker can perform for a given c
          maxValue=I.d[performedTasks][w]+currentC;
          for(t=performedTasks+1;(t<I.n)&&(I.d[t][w]<maxValue);t++) {  }
          t=t-1;
          //check if already exists
          it=avoidRepetition.find(current);
          if(it==avoidRepetition.end()) { //it it does not exist, save
            avoidRepetition[current]=t;
            newStates.push_back(current);
          }
          else { //if it exists, save changes to maxTasks only
            if(it->second<int(t)) it->second=t;
          }
          unsetbit(current,w);
        }
      }
    }
    //now we have to move newStates into oldStates
    for (unsigned i=0; i<newStates.size(); i++) { //for each generated stage
      oldStates.push(newStates[i]);
    }
    newStates.clear();
  }
  current=oldStates.top();
  t=avoidRepetition.find(current)->second; //check all tasks have been assigned (otherwise there is no improvement)
  if((t+1)!=I.n) return S; //no improvement. Return

  current=oldStates.top();
  S=decode(I,current,currentC);
  return S;
}

Solution iterativeApproach(const Instance& I, Solution &S) {
  unsigned int currentC=S.value*precision; //current cycle time

  while(1) { //keep trying while solution improves
    S=feasibleDP(I,S,currentC);
    if((S.value*precision)<currentC) currentC=S.value*precision;
    else break;
  }
  return S;
}

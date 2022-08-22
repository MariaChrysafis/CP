#include "game.h"
#include <bits/stdc++.h>
using namespace std;
int c[1501];
void initialize(int N){
  
}
int hasEdge(int u, int v){
  return ++c[max(u,v)]==max(u, v);
}

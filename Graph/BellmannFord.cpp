#include<bits/stdc++.h>
using namespace std;

const int N = 3e5 + 9;

struct st {
  int a, b, cost;
} e[N];

const int INF = 2e9;
//undirected & no negetive cycle-->ok
//Directted  -->ok
int32_t main() {
  int n, m;
  cin >> n >> m;
  for(int i = 0; i < m; i++) cin >> e[i].a >> e[i].b >> e[i].cost;
  int s;
  //Is there any negative cycle which is reachable from s?
  cin >> s;
  vector<int> d (n, INF);
  d[s] = 0;
  vector<int> p (n, -1);
  
  int x;
  for (int i=0; i<n; ++i) {
    x = -1;
    for (int j=0; j<m; ++j) {
      if (d[e[j].a] < INF) {
        if (d[e[j].b] > d[e[j].a] + e[j].cost) {
          //for overflow
          d[e[j].b] = max (-INF, d[e[j].a] + e[j].cost);
          p[e[j].b] = e[j].a;
          x = e[j].b;
        }
      }
    }
  }
  if (x == -1) cout << "No negative cycle from "<<s;
  else {
    int y = x; 
    //x can be on any cycle or reachable from some cycle
    for (int i=0; i<n; ++i) y = p[y];

    vector<int> path;
    for (int cur=y; ; cur=p[cur]) {
      path.push_back (cur);
      if (cur == y && path.size() > 1) break;
    }
    reverse (path.begin(), path.end());

    cout << "Negative cycle: ";
    for (int i=0; i<path.size(); ++i) cout << path[i] << ' ';
  }
  return 0;
}
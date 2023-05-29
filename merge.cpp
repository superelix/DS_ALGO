#include <bits/stdc++.h>
using namespace std;
#define int long long int
#define fast                 \
    ios::sync_with_stdio(0); \
    cin.tie(0);              \
    cout.tie(0);
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
#define F first
#define S second
#define PB push_back
#define MP make_pair
const ll mod = 1e9 + 7, N = 2e6 + 7, M = 2e6 + 7, INF = INT_MAX / 10;


struct Node{
  int llength;
  int rlength;
  char lchar;
  char rchar;
  int length;
  int tot;
};

  Node assignNode(char s){
    Node temp;
    temp.llength=1,temp.rlength=1,temp.lchar=s,temp.rchar=s,temp.length=1,temp.tot=1;
    return temp;
  }
Node tree[4*100003];

void merge(int treeIdx){
  int lidx=2*treeIdx;
  int ridx=2*treeIdx+1;
  Node lnode=tree[lidx];
  Node rnode=tree[ridx];
  tree[treeIdx].lchar=lnode.lchar;
  tree[treeIdx].rchar=rnode.rchar;
  tree[treeIdx].llength=lnode.llength;
  tree[treeIdx].rlength=rnode.rlength;
  tree[treeIdx].length=max(lnode.length,rnode.length);
  tree[treeIdx].tot=rnode.tot+lnode.tot;

  if(lnode.rchar==rnode.lchar){
    tree[treeIdx].length=
    max(tree[treeIdx].length,
    lnode.rlength+rnode.llength);
    
    if(lnode.llength==lnode.tot)
    tree[treeIdx].llength= lnode.tot+rnode.llength;

    if(rnode.rlength==rnode.tot)
    tree[treeIdx].rlength= rnode.tot+lnode.rlength;
  }
}

void updateAndQuery(int pos,int n,char c){
  pos += n;
  tree[pos] = assignNode(c);
  while (pos > 1)
  {
    pos >>= 1;
    merge(pos);
  }
}

void build(string s){
  for (int idx = 0; idx < s.length(); idx++)
    tree[s.length() + idx] = assignNode(s[idx]);

  for (int idx = s.length() - 1; idx >= 1; idx--){
    merge(idx);
  
  }
    
}
Node mergeNodes(Node lnode,Node rnode){
  Node res=assignNode('A');
    res.lchar=lnode.lchar;
    res.rchar=rnode.rchar;
    res.llength=lnode.llength;
    res.rlength=rnode.rlength;
    res.length=max(lnode.length,rnode.length);
    res.tot=rnode.tot+lnode.tot;

    if(lnode.rchar==rnode.lchar){
      res.length=
      max(res.length,
      lnode.rlength+rnode.llength);
      
      if(lnode.llength==lnode.tot)
      res.llength= lnode.tot+rnode.llength;

      if(rnode.rlength==rnode.tot)
      res.rlength= rnode.tot+lnode.rlength;
    }
    return res;
}

Node query(int l, int r,int n ){
    Node resl=assignNode('A'), resr=assignNode('A');
    int cntl=0,cntr=0;
    for(l += n, r += n; l < r; l >>= 1, r >>= 1){
        if(l&1){
          resl = mergeNodes(resl,tree[l++]);
        }
        if(r&1){
            resr = mergeNodes(tree[--r],resr);
        }
    }
    return mergeNodes(resl,resr);
}


 void solve(){
 
 }

 signed main(){
 int t;
 t=1;
 while(t--){
     solve();
 }
 return 0;
 }
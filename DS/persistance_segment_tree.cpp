#include<bits/stdc++.h>
using namespace std;

const int N=(int)(1e6);
int m,cnt=0,num=0;
int root[N],st[21*N],lc[21*N],rc[21*N];

int build(int L,int R){
   int node=++cnt;
   if(L==R){
         return node; 
   } 
   int M=(L+R)/2;
   lc[node]=build(L,M);
   rc[node]=build(M+1,R);
   return node;
}

int update(int onode,int L,int R,int pos){
    int node=++cnt;
    if(L==R){
        st[node]=st[node]+1;
        return node;
    }
    int M=(L+R)/2;
    lc[node]=lc[onode];
    rc[node]=rc[onode];
    if(pos<=M){
         lc[node]=update(lc[onode],L,M,pos);
    }
    else  rc[node]=update(rc[onode],M+1,R,pos);
    st[node]=st[lc[node]]+st[rc[node]];
    return node;
}

int query(int nodeu,int nodev,int L,int R,int pos){
    if(L==R)return L;
    int M=(L+R)/2;
    int leftval=st[lc[nodev]]-st[lc[nodeu]];
    int rightval=st[rc[nodev]]-st[rc[nodeu]];
    if(leftval>=pos)
            return query(lc[nodeu],lc[nodev],L,M,pos);
    else return query(rc[nodeu],rc[nodev],M+1,R,pos-leftval);    
}

void persistentSegTree(){
    root[0]=build(1,num);
}
  
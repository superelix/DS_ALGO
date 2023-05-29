#include<bits/stdc++.h>
using namespace std;


struct data{
    //Use required attributes.
    int mx;
    //Default values.
    data():mx(-1){};
};

struct segmentTree{
    int N;
    vector<data> st;
    vector<bool>lazyFlag;
    vector<int> lazyValue;

    void _start(int n){
        N=n;
        st.resize(4*N+7);
        lazyFlag.resize(4*N+7,false);
        lazyValue.resize(4*N+7,0);
    }
    //Write reqd merge functions
    void _merge(data &cur,data &left, data &right){
        cur.mx=max(left.mx,right.mx);
    }
   //Handle lazy propagation appriopriately
    void _propagate(int node,int l,int r){
    if(l!=r){
        lazyFlag[node*2]=1;
        lazyFlag[node*2+1]=1;
        lazyValue[node*2]=lazyValue[node];
        lazyValue[node*2+1]=lazyValue[node];   
    }
    st[node].mx=lazyValue[node];
    lazyFlag[node]=0;
    }

    void _build(int node, int L, int R)
	{
		if(L==R)
		{
			st[node].mx = -1;
			return;
		}
		int M=(L + R)/2;
		_build(node*2, L, M);
		_build(node*2 + 1, M + 1, R);
		_merge(st[node], st[node*2], st[node*2+1]);
	}

    data _Query(int node, int L, int R, int i, int j)
	{
		if(lazyFlag[node])
			_propagate(node, L, R);
		if(j<L || i>R)
			return data();
		if(i<=L && R<=j)
			return st[node];
		int M = (L + R)/2;
		data left=_Query(node*2, L, M, i, j);
		data right=_Query(node*2 + 1, M + 1, R, i, j);
		data cur;
		_merge(cur, left, right);
		return cur;
    }

    data _pQuery(int node, int L, int R, int pos)
	{
		if(lazyFlag[node])
			_propagate(node, L, R);
		if(L == R)
			return st[node];
		int M = (L + R)/2;
		if(pos <= M)
			return _pQuery(node*2, L, M, pos);
		else
			return _pQuery(node*2 + 1, M + 1, R, pos);
	}

    void _Update(int node, int L, int R, int i, int j, int val)
	{
		if(lazyFlag[node])
			_propagate(node, L, R);
		if(j<L || i>R)
			return;
		if(i<=L && R<=j)
		{
			lazyFlag[node] = 1;
			lazyValue[node] = val;
			_propagate(node, L, R);
			return;
		}
		int M = (L + R)/2;
		_Update(node*2, L, M, i, j, val);
		_Update(node*2 + 1, M + 1, R, i, j, val);
		_merge(st[node], st[node*2], st[node*2 + 1]);
	}

    void _pUpdate(int node, int L, int R, int pos, int val)
	{
		if(lazyFlag[node])
			_propagate(node, L, R);
		if(L == R)
		{
		    lazyFlag[node] = 1;
			lazyValue[node] = val;
			_propagate(node, L, R);
			return;
		}
		int M = (L + R)/2;
		if(pos <= M)
			_pUpdate(node*2, L, M, pos, val);
		else
			_pUpdate(node*2 + 1, M + 1, R, pos, val);
		_merge(st[node], st[node*2], st[node*2 + 1]);
	}

    data query(int pos)
	{
		return _pQuery(1, 1, N, pos);
	}

	data query(int l, int r)
	{
		return _Query(1, 1, N, l, r);
	}

	void update(int pos, int val)
	{
		_pUpdate(1, 1, N, pos, val);
	}

	void update(int l, int r, int val)
	{
		_Update(1, 1, N, l, r, val);
	}
};


//Used for directed graphs in find the shortest path & distance between all pair of vertices.

#include<bits/stdc++.h>
using namespace std;

const int N=2e3;
int dist[N][N];
int Next[N][N];

void FloydWarshall(int n)
{

	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
            {  if(dist[i][j]>dist[i][k]+dist[k][j])
                {
				dist[i][j]=min(dist[i][j], dist[i][k] + dist[k][j]);
                                Next[i][j]=Next[i][k];
               }
            }
}


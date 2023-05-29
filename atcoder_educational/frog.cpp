#include<bits/stdc++.h>
using namespace std;
#define ll  long long int 
const ll N=101,W=10e9+1,TV=10e5+1;


signed main(){
   ll n;
   cin>>n; 
   vector<ll> values(n);
   vector<ll> weights(n);

   for (int i=0;i<n;i++)std::cin>>weights[i]>>values[i];
   
   ll dp[N][TV];
   for (ll i=0;i<N;i++){
        for (ll j=0;j<TV;j++){
            if (j==0){
                dp[i][j]=0;
            }else if (i==0){
                dp[i][j]=((j==values[i])?weights[i]:W);
            }else dp[i][j]=W;
        }
   }

  ll maxValue=-1;
   for (ll i=1;i<n;i++){
    for(ll j=1;j<TV;j++){
        dp[i][j]=min(dp[i-1][j-values[i]]+weights[i],dp[i-1][j]);
        if (dp[i][j]<W){
           maxValue=  max(maxValue,j);
        }
    }
   }
    std::cout<<maxValue;
    return 0;
}
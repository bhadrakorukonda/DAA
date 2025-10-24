#include <bits/stdc++.h>
using namespace std;

int main(){
    vector<int> wt={1,3,4,5}, val={1,4,5,7};
    int W=7, n=wt.size();
    vector<vector<int>> dp(n+1, vector<int>(W+1,0));
    for(int i=1;i<=n;++i){
        for(int w=0; w<=W; ++w){
            dp[i][w]=dp[i-1][w];
            if(wt[i-1]<=w) dp[i][w]=max(dp[i][w], val[i-1]+dp[i-1][w-wt[i-1]]);
        }
    }
    cout<<"Max value = "<<dp[n][W]<<"\n";
}

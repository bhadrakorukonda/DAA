#include <bits/stdc++.h>
using namespace std;

int main(){
    int n=5;
    vector<vector<pair<int,int>>> g(n);
    auto add=[&](int u,int v,int w){ g[u].push_back({v,w}); g[v].push_back({u,w}); };
    add(0,1,4); add(0,2,1); add(2,1,2); add(1,3,1); add(2,3,5); add(3,4,3);

    const long long INF = 1e18;
    vector<long long> dist(n, INF);
    dist[0]=0;
    priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<>> pq;
    pq.push({0,0});
    while(!pq.empty()){
        auto [d,u]=pq.top(); pq.pop();
        if(d!=dist[u]) continue;
        for(auto [v,w]: g[u]){
            if(dist[v] > d + w){
                dist[v] = d + w;
                pq.push({dist[v], v});
            }
        }
    }
    for(int i=0;i<n;++i) cout<<"0 -> "<<i<<" = "<<dist[i]<<"\n";
}

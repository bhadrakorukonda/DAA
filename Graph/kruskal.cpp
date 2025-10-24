#include <bits/stdc++.h>
using namespace std;

struct DSU{
    vector<int> p, r;
    DSU(int n):p(n),r(n,0){ iota(p.begin(),p.end(),0); }
    int find(int x){ return p[x]==x?x:p[x]=find(p[x]); }
    bool unite(int a,int b){
        a=find(a); b=find(b);
        if(a==b) return false;
        if(r[a]<r[b]) swap(a,b);
        p[b]=a; if(r[a]==r[b]) r[a]++;
        return true;
    }
};

int main(){
    int n=4;
    vector<tuple<int,int,int>> edges = {
        {0,1,10},{0,2,6},{0,3,5},{1,3,15},{2,3,4}
    };
    sort(edges.begin(), edges.end(), [](auto &x, auto &y){
        return get<2>(x) < get<2>(y);
    });
    DSU dsu(n); int mst_w=0; vector<tuple<int,int,int>> mst;
    for(auto [u,v,w]: edges){
        if(dsu.unite(u,v)){ mst_w+=w; mst.push_back({u,v,w}); }
    }
    cout<<"MST weight = "<<mst_w<<"\nEdges:\n";
    for(auto [u,v,w]: mst) cout<<u<<"-"<<v<<" ("<<w<<")\n";
}

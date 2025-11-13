#include <bits/stdc++.h>
using namespace std;

struct DSU{
    int n; vector<int> p, r;
    DSU(int n=0):n(n),p(n),r(n,0){ iota(p.begin(),p.end(),0); }
    int find(int x){ return p[x]==x?x:p[x]=find(p[x]); }
    void reset(){ iota(p.begin(),p.end(),0); fill(r.begin(),r.end(),0); }
    void unite(int a,int b){
        a=find(a); b=find(b); if(a==b) return;
        if(r[a]<r[b]) swap(a,b);
        p[b]=a; if(r[a]==r[b]) r[a]++;
    }
};

struct Edge{ int u,v,w; };
struct Query{ int u,v,idx; };

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Demo graph (0-indexed):
    int n=6;
    vector<Edge> E = {
        {0,1,3},{1,2,5},{2,3,7},{3,4,9},{4,5,11},{0,5,100}
    };
    vector<Query> Q = { {0,2,0}, {0,5,1}, {1,4,2} };
    int m=E.size(), q=Q.size();

    // Sort edges by weight once
    sort(E.begin(), E.end(), [](auto &a, auto &b){ return a.w < b.w; });

    // Search range on "edge index" (how many lightest edges you allow)
    vector<int> lo(q, 0), hi(q, m); // answer is minimal k in [0..m] s.t. connected; m means "never"
    bool changed = true;
    DSU dsu(n);

    // Buckets per mid
    while(true){
        changed = false;
        vector<vector<int>> bucket(m+1);
        for(int i=0;i<q;++i){
            if(lo[i]<hi[i]){
                changed = true;
                int mid = (lo[i]+hi[i])/2;
                bucket[mid].push_back(i);
            }
        }
        if(!changed) break;

        dsu.reset();
        int ptr = -1; // last applied edge index
        for(int k=0; k<=m; ++k){
            // apply edges up to k-1 (i.e., first k edges)
            while(ptr < k-1){
                ++ptr;
                dsu.unite(E[ptr].u, E[ptr].v);
            }
            for(int qi: bucket[k]){
                auto [u,v,idx] = Q[qi];
                if(dsu.find(u)==dsu.find(v)) hi[qi]=k;
                else lo[qi]=k+1;
            }
        }
    }

    // Print answers (edge weight or "INF")
    vector<int> ans(q);
    for(int i=0;i<q;++i){
        if(lo[i]>=m) ans[i]=INT_MAX; // not connected
        else ans[i]=E[lo[i]].w;
    }
    cout<<"Minimum connecting weights per query:\n";
    for(int i=0;i<q;++i){
        cout<<"q"<<i<<": ";
        if(ans[i]==INT_MAX) cout<<"INF\n";
        else cout<<ans[i]<<"\n";
    }
}

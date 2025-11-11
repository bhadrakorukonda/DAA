#include <bits/stdc++.h>
using namespace std;

// ---------- DSU with Rollback ----------
struct RollbackDSU {
    int n, comps;
    vector<int> p, sz;
    vector<pair<int,int>> stk;
    RollbackDSU(int n=0): n(n), comps(n), p(n), sz(n,1){ iota(p.begin(),p.end(),0); }
    int find(int x){ while(x!=p[x]) x=p[x]; return x; }
    bool unite(int a,int b){
        a=find(a); b=find(b);
        if(a==b){ stk.emplace_back(-1,-1); return false; }
        if(sz[a]<sz[b]) swap(a,b);
        stk.emplace_back(b, sz[a]);
        p[b]=a; sz[a]+=sz[b]; comps--;
        return true;
    }
    void snapshot(){ stk.emplace_back(-2,-2); }
    void rollback(){
        while(!stk.empty()){
            auto [b, s] = stk.back(); stk.pop_back();
            if(b==-2) break;
            if(b==-1) continue;
            int a = p[b];
            sz[a] = s; p[b]=b; comps++;
        }
    }
};

// ---------- Segment tree over time holding edges ----------
struct Edge { int u,v; };
struct SegTree {
    int T;
    vector<vector<Edge>> bucket;
    SegTree(int T=0):T(T),bucket(4*T+4){}
    void add(int idx,int l,int r,int ql,int qr, Edge e){
        if(qr<=l || r<=ql) return;
        if(ql<=l && r<=qr){ bucket[idx].push_back(e); return; }
        int m=(l+r)/2;
        add(idx*2,l,m,ql,qr,e);
        add(idx*2+1,m,r,ql,qr,e);
    }
    vector<Edge>& operator[](int i){ return bucket[i]; }
};

// Demo: operations timeline
// Op types: +u v (add edge), -u v (remove), ?u v (query connected)
// We implement a tiny hand-crafted scenario to showcase answers.
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N = 5;
    // timeline of 10 steps; edges may be active on intervals
    struct Op{ char type; int u,v; };
    vector<Op> ops = {
        {'+',0,1},
        {'+',1,2},
        {'?',0,2},
        {'-',1,2},
        {'?',0,2},
        {'+',2,3},
        {'?',0,3},
        {'+',3,4},
        {'?',0,4},
        {'-',0,1}
    };
    int T = (int)ops.size();

    // Map each edge -> last add time; collect active intervals [add, remove)
    auto norm = [&](int a,int b){ if(a>b) swap(a,b); return pair<int,int>(a,b); };
    map<pair<int,int>, int> lastAdd;
    vector<tuple<int,int,Edge>> intervals; // [l,r), edge
    for(int t=0;t<T;++t){
        auto [typ,u,v] = ops[t];
        auto key = norm(u,v);
        if(typ=='+') lastAdd[key]=t;
        else if(typ=='-'){
            int l = lastAdd[key];
            intervals.push_back({l, t, Edge{u,v}});
            lastAdd.erase(key);
        }
    }
    // still-active edges go to [add, T)
    for(auto &kv: lastAdd){
        intervals.push_back({kv.second, T, Edge{kv.first.first, kv.first.second}});
    }

    // Build segment tree with edge intervals
    SegTree st(T);
    for(auto &[l,r,e]: intervals) st.add(1,0,T,l,r,e);

    // Prepare DSU and process with recursion
    RollbackDSU dsu(N);

    vector<string> answers; answers.reserve(T);

    function<void(int,int,int)> dfs = [&](int idx,int l,int r){
        dsu.snapshot();
        for(auto &e: st[idx]) dsu.unite(e.u, e.v);

        if(r-l==1){
            auto [typ,u,v] = ops[l];
            if(typ=='?'){
                bool conn = (dsu.find(u)==dsu.find(v));
                answers.push_back(string("t=")+to_string(l)+": "+(conn?"YES":"NO"));
            }
            dsu.rollback();
            return;
        }
        int m=(l+r)/2;
        dfs(idx*2,l,m);
        dfs(idx*2+1,m,r);
        dsu.rollback();
    };

    dfs(1,0,T);

    cout << "Offline dynamic connectivity answers:\n";
    for(auto &s: answers) cout << s << "\n";
}

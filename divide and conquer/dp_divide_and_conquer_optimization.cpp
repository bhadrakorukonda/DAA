#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// cost of segment (j+1..i)
struct Cost {
    vector<ll> S; // prefix sums, S[0]=0
    ll operator()(int j, int i) const { // 0<=j<i
        ll d = S[i]-S[j];
        return d*d;
    }
};

void compute_layer(int L, int R, int optL, int optR,
                   const vector<ll>& prev, vector<ll>& cur,
                   const Cost& cost){
    if(L>R) return;
    int mid = (L+R)/2;
    pair<ll,int> best = {LLONG_MAX, -1};
    int start = optL, end = min(mid-1, optR);
    for(int j=start; j<=end; ++j){
        ll cand = prev[j] + cost(j, mid);
        if(cand < best.first){ best = {cand, j}; }
    }
    cur[mid] = best.first;
    int opt = (best.second==-1? start : best.second);
    compute_layer(L, mid-1, optL, opt, prev, cur, cost);
    compute_layer(mid+1, R, opt, optR, prev, cur, cost);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Demo input: n numbers, partition into k groups with quadratic cost
    int n = 10, k = 3;
    vector<ll> a = {3,1,4,1,5,9,2,6,5,3};
    vector<ll> S(n+1,0);
    for(int i=1;i<=n;++i) S[i]=S[i-1]+a[i-1];

    Cost C{S};

    const ll INF = (1LL<<62);
    vector<ll> prev(n+1, INF), cur(n+1, INF);
    prev[0]=0;
    for(int i=1;i<=n;++i) prev[i]=C(0,i); // t=1 base (all in one segment)
    // refine layers t=2..k
    for(int t=2; t<=k; ++t){
        fill(cur.begin(), cur.end(), INF);
        compute_layer(1, n, 0, n-1, prev, cur, C);
        prev.swap(cur);
    }
    cout << "Optimal cost (k="<<k<<") = " << prev[n] << "\n";
}

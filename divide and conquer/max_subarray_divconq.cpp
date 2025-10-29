#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Node {
    ll sum, pref, suff, best;
};

Node merge_node(const Node& L, const Node& R){
    Node res;
    res.sum  = L.sum + R.sum;
    res.pref = max(L.pref, L.sum + R.pref);
    res.suff = max(R.suff, R.sum + L.suff);
    res.best = max({L.best, R.best, L.suff + R.pref});
    return res;
}

Node solve(vector<ll>& a, int l, int r){
    if(r - l == 1){
        ll x=a[l];
        return Node{x, max(x,0LL), max(x,0LL), x};
    }
    int m = (l+r)/2;
    Node left  = solve(a,l,m);
    Node right = solve(a,m,r);
    return merge_node(left,right);
}

int main(){
    vector<long long> a = {-2,1,-3,4,-1,2,1,-5,4};
    Node ans = solve(a,0,(int)a.size());
    cout << "Max subarray sum = " << ans.best << "\n"; // 6
}

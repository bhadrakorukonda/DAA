#include <bits/stdc++.h>
using namespace std;
using ll = long long;

long long merge_count(vector<ll>& a, vector<ll>& tmp, int l, int m, int r){
    long long cnt=0;
    int i=l, j=m;
    // count condition a[i] > 2*a[j]
    while(i<m){
        while(j<r && (long long)a[i] > 2LL*(long long)a[j]) ++j;
        cnt += (j - m);
        ++i;
    }
    // standard merge
    i=l; j=m; int k=l;
    while(i<m && j<r) tmp[k++] = (a[i]<=a[j]?a[i++]:a[j++]);
    while(i<m) tmp[k++]=a[i++];
    while(j<r) tmp[k++]=a[j++];
    for(int t=l;t<r;++t) a[t]=tmp[t];
    return cnt;
}

long long solve(vector<ll>& a, vector<ll>& tmp, int l, int r){
    if(r-l<=1) return 0;
    int m=(l+r)/2;
    long long res=0;
    res += solve(a,tmp,l,m);
    res += solve(a,tmp,m,r);
    res += merge_count(a,tmp,l,m,r);
    return res;
}

int main(){
    vector<long long> a = {1,3,2,3,1};
    vector<long long> tmp(a.size());
    cout << "Reverse pairs = " << solve(a,tmp,0,(int)a.size()) << "\n"; // 2
}

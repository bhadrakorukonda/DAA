#include <bits/stdc++.h>
using namespace std;

struct MergeSortTree{
    int n; vector<vector<int>> st;
    MergeSortTree(const vector<int>& a){
        n=a.size(); st.resize(4*n);
        build(1,0,n-1,a);
    }
    void build(int p,int l,int r,const vector<int>& a){
        if(l==r){ st[p]={a[l]}; return; }
        int m=(l+r)/2;
        build(p<<1,l,m,a);
        build(p<<1|1,m+1,r,a);
        st[p].resize(st[p<<1].size()+st[p<<1|1].size());
        merge(st[p<<1].begin(),st[p<<1].end(), st[p<<1|1].begin(),st[p<<1|1].end(), st[p].begin());
    }
    // count <= x on [L,R]
    int count_leq(int p,int l,int r,int L,int R,int x){
        if(R<l || r<L) return 0;
        if(L<=l && r<=R) return upper_bound(st[p].begin(),st[p].end(),x) - st[p].begin();
        int m=(l+r)/2;
        return count_leq(p<<1,l,m,L,R,x) + count_leq(p<<1|1,m+1,r,L,R,x);
    }
    int count_leq(int L,int R,int x){ return count_leq(1,0,n-1,L,R,x); }

    // kth smallest on [L,R] using value-space binary search
    int kth(int L,int R,int k){
        // collect global value range
        int lo = st[1].front(), hi = st[1].back();
        while(lo<hi){
            int mid = lo + (hi-lo)/2;
            int cnt = count_leq(L,R,mid);
            if(cnt>=k) hi=mid;
            else lo=mid+1;
        }
        return lo;
    }
};

int main(){
    vector<int> a = {5,1,2,6,3,7,4,8};
    MergeSortTree mst(a);

    cout<<"count_leq([1,6], 4) = "<<mst.count_leq(1,6,4)<<"\n"; // indices 1..6 inclusive
    cout<<"kth([0,7], 3) = "<<mst.kth(0,7,3)<<"\n";              // 3rd smallest of whole array
    cout<<"kth([2,5], 2) = "<<mst.kth(2,5,2)<<"\n";
}

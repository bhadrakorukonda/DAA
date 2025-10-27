#include <bits/stdc++.h>
using namespace std;

// Average O(n), worst O(n^2). With randomization, good in practice.

int partition(vector<int>& a, int l, int r){
    int pivot = a[r], i=l;
    for(int j=l;j<r;++j) if(a[j]<=pivot) swap(a[i++], a[j]);
    swap(a[i], a[r]);
    return i;
}

int quickselect(vector<int>& a, int l, int r, int k){ // 0-indexed k
    while(true){
        if(l==r) return a[l];
        int p = l + rand() % (r - l + 1);
        swap(a[p], a[r]);              // randomize
        int m = partition(a,l,r);
        if(k==m) return a[m];
        else if(k<m) r=m-1;
        else l=m+1;
    }
}

int main(){
    vector<int> a = {7, 10, 4, 3, 20, 15};
    int k = 2; // 0-indexed -> third smallest
    cout<<"k-th smallest = "<<quickselect(a,0,(int)a.size()-1,k)<<"\n"; // 7
}

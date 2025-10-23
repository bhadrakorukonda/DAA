#include <bits/stdc++.h>
using namespace std;

int part(vector<int>& a, int l, int r){
    int pivot = a[r], i = l-1;
    for(int j=l;j<r;++j){
        if(a[j] <= pivot) swap(a[++i], a[j]);
    }
    swap(a[i+1], a[r]);
    return i+1;
}
void quick_sort(vector<int>& a, int l, int r){
    if(l<r){
        int p = part(a,l,r);
        quick_sort(a,l,p-1);
        quick_sort(a,p+1,r);
    }
}
int main(){
    vector<int> a = {9, -1, 5, 0, 7, 2};
    quick_sort(a,0,(int)a.size()-1);
    for(int x:a) cout<<x<<" ";
    cout<<"\n";
}

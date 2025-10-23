#include <bits/stdc++.h>
using namespace std;

int binary_search_index(const vector<int>& a, int key){
    int l=0, r=(int)a.size()-1;
    while(l<=r){
        int m=l+(r-l)/2;
        if(a[m]==key) return m;
        else if(a[m]<key) l=m+1;
        else r=m-1;
    }
    return -1;
}
int main(){
    vector<int> a = {1,3,5,7,9,11};
    cout << binary_search_index(a,7) << "\n";   // 3
}

#include <bits/stdc++.h>
using namespace std;

int binary_search_index(const vector<int>& a, int key){
    int l=0, r=(int)a.size()-1;
    while(l<=r){
        int m=l+(r-l)/2;
        if(a[m]==key) return m;
        else if(a[m]<key) l=m+1;
        else r=m-1;
    }
    return -1;
}
int main(){
    vector<int> a = {1,3,5,7,9,11};
    cout << binary_search_index(a,7) << "\n";   // 3
}

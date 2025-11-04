#include <bits/stdc++.h>
using namespace std;

// Returns (row,col) of a peak using column-based divide & conquer.
pair<int,int> find_peak_2d(const vector<vector<int>>& a){
    int n=a.size(), m=a[0].size();
    int L=0, R=m-1;
    while(L<=R){
        int mid=(L+R)/2;
        // find row of column mid maximum
        int best_row=0;
        for(int i=1;i<n;++i) if(a[i][mid] > a[best_row][mid]) best_row=i;

        int left  = (mid-1>=0)   ? a[best_row][mid-1] : INT_MIN;
        int right = (mid+1<m)    ? a[best_row][mid+1] : INT_MIN;
        int cur   = a[best_row][mid];

        if(cur>=left && cur>=right) return {best_row, mid};
        if(left > cur) R = mid-1;
        else L = mid+1;
    }
    return {-1,-1}; // should not happen if matrix non-empty
}

int main(){
    vector<vector<int>> a = {
        {10,  8, 10, 10},
        {14, 13, 12, 11},
        {15,  9, 11, 21},
        {16, 17, 19, 20}
    };
    auto [r,c] = find_peak_2d(a);
    cout << "Peak at ("<<r<<","<<c<<") = " << a[r][c] << "\n";
}

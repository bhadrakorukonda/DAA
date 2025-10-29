#include <bits/stdc++.h>
using namespace std;

struct Key { int x, h; };
using Skyline = vector<Key>;

// merge two skylines
Skyline mergeSky(const Skyline& A, const Skyline& B){
    Skyline res; int i=0,j=0, ha=0,hb=0, curr=0;
    auto append = [&](int x, int h){
        if(res.empty() || res.back().h != h) res.push_back({x,h});
        else res.back().x = x; // same height, update x
    };
    while(i<(int)A.size() && j<(int)B.size()){
        int x;
        if(A[i].x < B[j].x){ x=A[i].x; ha=A[i].h; ++i; }
        else if(B[j].x < A[i].x){ x=B[j].x; hb=B[j].h; ++j; }
        else { x=A[i].x; ha=A[i].h; hb=B[j].h; ++i; ++j; }
        int h = max(ha,hb);
        if(h!=curr){ append(x,h); curr=h; }
    }
    while(i<(int)A.size()){ if(A[i].h!=curr){ append(A[i].x,A[i].h); curr=A[i].h; } ++i; }
    while(j<(int)B.size()){ if(B[j].h!=curr){ append(B[j].x,B[j].h); curr=B[j].h; } ++j; }
    // compact consecutive duplicates of x
    Skyline clean; for(auto &k: res){ if(clean.empty() || clean.back().x!=k.x) clean.push_back(k); else clean.back().h=k.h; }
    return clean;
}

// build skyline from buildings [l,r)
Skyline solve(vector<array<int,3>>& B, int l, int r){
    if(r-l==0) return {};
    if(r-l==1){
        int L=B[l][0], R=B[l][1], H=B[l][2];
        return Skyline{{{L,H},{R,0}}};
    }
    int m=(l+r)/2;
    return mergeSky(solve(B,l,m), solve(B,m,r));
}

int main(){
    // Each building: {left, right, height}
    vector<array<int,3>> buildings = {
        {2,9,10},{3,7,15},{5,12,12},{15,20,10},{19,24,8}
    };
    auto S = solve(buildings, 0, (int)buildings.size());
    cout << "Skyline key points:\n";
    for(auto &k : S) cout << "(" << k.x << "," << k.h << ") ";
    cout << "\n";
    // Expected: (2,10) (3,15) (7,12) (12,0) (15,10) (20,8) (24,0)
}

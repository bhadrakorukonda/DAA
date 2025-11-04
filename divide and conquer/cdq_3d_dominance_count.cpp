#include <bits/stdc++.h>
using namespace std;

// Fenwick for 1..MAXZ
struct BIT {
    int n; vector<int> t;
    BIT(int n=0):n(n),t(n+1,0) {}
    void add(int i,int v){ for(;i<=n;i+=i&-i) t[i]+=v; }
    int sum(int i){ int s=0; for(;i>0;i-=i&-i) s+=t[i]; return s; }
};

struct Node {
    int x,y,z, w, id;
    long long ans=0;
};

bool cmp_xyz(const Node& a, const Node& b){
    if(a.x!=b.x) return a.x<b.x;
    if(a.y!=b.y) return a.y<b.y;
    return a.z<b.z;
}
bool cmp_yz(const Node& a, const Node& b){
    if(a.y!=b.y) return a.y<b.y;
    return a.z<b.z;
}

void cdq(vector<Node>& a, int l, int r, BIT &bit){
    if(r-l<=1) return;
    int m=(l+r)/2;
    cdq(a,l,m,bit);
    cdq(a,m,r,bit);

    // merge step on y, with fenwick on z
    vector<Node> left(a.begin()+l,a.begin()+m), right(a.begin()+m,a.begin()+r);
    sort(left.begin(), left.end(), cmp_yz);
    sort(right.begin(), right.end(), cmp_yz);

    int i=0;
    for(int j=0;j<(int)right.size();++j){
        while(i<(int)left.size() && left[i].y<=right[j].y){
            bit.add(left[i].z, left[i].w); // add weights from left half
            ++i;
        }
        long long got = bit.sum(right[j].z);
        a[l + (m-l) + j].ans += got; // temporarily write; will fix after stable merge
    }
    // clear
    for(int k=0;k<i;++k) bit.add(left[k].z, -left[k].w);

    // stable merge by y,z back into a[l:r] while keeping x order
    inplace_merge(a.begin()+l, a.begin()+m, a.begin()+r, cmp_yz);
}

int main(){
    // Input example (with duplicates handled by grouping as weights)
    vector<Node> pts = {
        {1,2,3,1,0},{2,2,2,1,1},{2,3,1,1,2},{1,1,1,1,3},{2,2,3,1,4},{3,3,3,1,5}
    };
    // Coordinate compress z
    vector<int> Z; Z.reserve(pts.size());
    for(auto &p:pts) Z.push_back(p.z);
    sort(Z.begin(),Z.end()); Z.erase(unique(Z.begin(),Z.end()),Z.end());
    for(auto &p:pts) p.z = int(lower_bound(Z.begin(),Z.end(),p.z)-Z.begin())+1;

    // Sort by x,y,z; group equal (x,y,z) and accumulate weight
    sort(pts.begin(), pts.end(), cmp_xyz);
    vector<Node> b;
    for(size_t i=0;i<pts.size();){
        size_t j=i; int w=0;
        while(j<pts.size() && pts[j].x==pts[i].x && pts[j].y==pts[i].y && pts[j].z==pts[i].z){ w+=pts[j].w; ++j; }
        Node t=pts[i]; t.w=w; b.push_back(t); i=j;
    }

    // Prepare BIT on z
    BIT bit((int)Z.size());

    // Run CDQ on x (array is x-sorted; cdq merges on y and queries z)
    // We store partial results in .ans, then add own weight - 1 if needed.
    // Here we want count of dominated points INCLUDING identical; because we grouped, add w to itself later.
    cdq(b, 0, (int)b.size(), bit);

    // expand answers back to each grouped node (each group represents w points with same coords)
    // For exact dominated count including self, add (w - 1) inside the group.
    cout << "Dominated counts (including equals) per unique point:\n";
    for(auto &t: b){
        long long total = t.ans + t.w; // <= including itself (since we used <=, add w not w-1 due to grouping logic)
        cout << "("<<t.x<<","<<t.y<<","<<Z[t.z-1]<<") -> " << total << "\n";
    }
}

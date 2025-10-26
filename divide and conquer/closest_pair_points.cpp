#include <bits/stdc++.h>
using namespace std;

struct P { double x,y; };
double dist(const P& a, const P& b){ double dx=a.x-b.x, dy=a.y-b.y; return sqrt(dx*dx+dy*dy); }

double solve(vector<P>& pts, vector<P>& tmp, int l, int r){
    if(r-l<=3){
        double ans = 1e100;
        for(int i=l;i<r;i++) for(int j=i+1;j<r;j++) ans=min(ans, dist(pts[i],pts[j]));
        sort(pts.begin()+l, pts.begin()+r, [](const P&a, const P&b){ return a.y<b.y; });
        return ans;
    }
    int m=(l+r)/2; double midx=pts[m].x;
    double dl=solve(pts,tmp,l,m), dr=solve(pts,tmp,m,r);
    double d=min(dl,dr);

    merge(pts.begin()+l,pts.begin()+m,pts.begin()+m,pts.begin()+r,tmp.begin(),
          [](const P&a,const P&b){ return a.y<b.y; });
    copy(tmp.begin(), tmp.begin()+(r-l), pts.begin()+l);

    vector<P> strip; strip.reserve(r-l);
    for(int i=l;i<r;i++) if(fabs(pts[i].x - midx) < d) strip.push_back(pts[i]);

    for(size_t i=0;i<strip.size();++i){
        // Proven: check next up to 7 points in y-order
        for(size_t j=i+1;j<strip.size() && (strip[j].y - strip[i].y) < d; ++j)
            d=min(d, dist(strip[i], strip[j]));
    }
    return d;
}

int main(){
    vector<P> a = {{2.1,3.2},{12,30},{40,50},{5,1},{12,10},{3,4},{7,2.5},{9,9}};
    sort(a.begin(), a.end(), [](const P& p1, const P& p2){ return p1.x<p2.x; });
    vector<P> tmp(a.size());
    cout.setf(std::ios::fixed); cout<<setprecision(6);
    cout<<"Closest distance = "<<solve(a,tmp,0,(int)a.size())<<"\n";
}

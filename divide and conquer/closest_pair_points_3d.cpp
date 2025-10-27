#include <bits/stdc++.h>
using namespace std;

struct Point {
    double x, y, z;
};
double dist(const Point &a, const Point &b) {
    double dx=a.x-b.x, dy=a.y-b.y, dz=a.z-b.z;
    return sqrt(dx*dx + dy*dy + dz*dz);
}

double brute(vector<Point> &pts, int l, int r) {
    double d = 1e100;
    for (int i = l; i < r; ++i)
        for (int j = i + 1; j < r; ++j)
            d = min(d, dist(pts[i], pts[j]));
    return d;
}

double solve(vector<Point> &pts, vector<Point> &tmp, int l, int r) {
    if (r - l <= 3)
        return brute(pts, l, r);

    int m = (l + r) / 2;
    double midx = pts[m].x;
    double dl = solve(pts, tmp, l, m);
    double dr = solve(pts, tmp, m, r);
    double d = min(dl, dr);

    // Merge by y coordinate for efficient strip
    inplace_merge(pts.begin()+l, pts.begin()+m, pts.begin()+r,
                  [](const Point &a, const Point &b){ return a.y < b.y; });

    // Collect points in strip within distance d from mid plane
    vector<Point> strip;
    for (int i = l; i < r; ++i)
        if (fabs(pts[i].x - midx) < d)
            strip.push_back(pts[i]);

    // Compare each point to next few within y distance < d
    for (size_t i = 0; i < strip.size(); ++i) {
        for (size_t j = i + 1; j < strip.size(); ++j) {
            if (strip[j].y - strip[i].y >= d) break;
            // Also check z distance
            if (fabs(strip[j].z - strip[i].z) >= d) continue;
            d = min(d, dist(strip[i], strip[j]));
        }
    }
    return d;
}

int main() {
    vector<Point> pts = {
        {0,0,0}, {1,2,2}, {3,3,3}, {2,1,1}, {5,5,1}, {4,4,2}, {2.2,2.1,2.05}
    };
    sort(pts.begin(), pts.end(), [](auto &a, auto &b){ return a.x < b.x; });
    vector<Point> tmp(pts.size());

    cout.setf(std::ios::fixed);
    cout << setprecision(6);
    cout << "Closest distance (3D) = " << solve(pts, tmp, 0, pts.size()) << "\n";
}

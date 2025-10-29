#include <bits/stdc++.h>
using namespace std;

struct Point {
    long long x, y;
    bool operator<(const Point& p) const { return x == p.x ? y < p.y : x < p.x; }
};

long long cross(const Point& O, const Point& A, const Point& B) {
    return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

vector<Point> mergeConvexHull(vector<Point>& left, vector<Point>& right) {
    int n1 = left.size(), n2 = right.size();
    int i = n1 - 1, j = 0;
    while (i >= 0 && j < n2 && cross(left[i], left[i - 1], right[j]) < 0) i--;
    vector<Point> result = left;
    while (i < n1 && j < n2) {
        result.push_back(right[j++]);
        while (cross(result[result.size() - 2], result.back(), right[j]) > 0) result.pop_back();
    }
    return result;
}

vector<Point> convexHull(vector<Point>& points) {
    sort(points.begin(), points.end());
    if (points.size() <= 1) return points;

    int mid = points.size() / 2;
    vector<Point> left(points.begin(), points.begin() + mid);
    vector<Point> right(points.begin() + mid, points.end());

    vector<Point> leftHull = convexHull(left);
    vector<Point> rightHull = convexHull(right);

    return mergeConvexHull(leftHull, rightHull);
}

int main() {
    vector<Point> points = {{0,0}, {1,2}, {3,3}, {2,1}, {0,3}, {3,0}};
    vector<Point> hull = convexHull(points);
    
    cout << "Convex Hull: ";
    for (auto& p : hull) cout << "(" << p.x << "," << p.y << ") ";
    cout << "\n";
}

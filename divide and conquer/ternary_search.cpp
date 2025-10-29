#include <bits/stdc++.h>
using namespace std;

double func(double x) {
    // Example unimodal function: a simple quadratic function
    return -(x - 2) * (x - 2) + 5;  // Maximum at x = 2
}

double ternarySearch(double l, double r, double (*f)(double)) {
    while (r - l > 1e-9) {  // Precision up to 1e-9
        double m1 = l + (r - l) / 3;
        double m2 = r - (r - l) / 3;

        if (f(m1) > f(m2)) r = m2;
        else l = m1;
    }
    return f((l + r) / 2);  // Return maximum/minimum value
}

int main() {
    double l = 0, r = 4;
    cout << "Maximum value of the function: " << ternarySearch(l, r, func) << "\n";  // Should output close to 5
}

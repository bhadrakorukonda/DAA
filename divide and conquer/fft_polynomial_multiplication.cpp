#include <bits/stdc++.h>
using namespace std;

// ---------------- FFT Core ----------------
using cd = complex<double>;
const double PI = acos(-1.0);

// Recursive Cooley–Tukey FFT
void fft(vector<cd> &a, bool invert) {
    int n = a.size();
    if (n == 1) return;

    vector<cd> a0(n/2), a1(n/2);
    for (int i = 0; 2*i < n; ++i) {
        a0[i] = a[2*i];
        a1[i] = a[2*i+1];
    }

    fft(a0, invert);
    fft(a1, invert);

    double ang = 2 * PI / n * (invert ? -1 : 1);
    cd w(1), wn(cos(ang), sin(ang));
    for (int i = 0; 2*i < n; ++i) {
        a[i]       = a0[i] + w * a1[i];
        a[i+n/2]   = a0[i] - w * a1[i];
        if (invert) a[i] /= 2, a[i+n/2] /= 2;
        w *= wn;
    }
}

// ---------------- Polynomial Multiplication ----------------
vector<long long> multiply_poly(const vector<long long> &A, const vector<long long> &B) {
    vector<cd> fa(A.begin(), A.end()), fb(B.begin(), B.end());
    int n = 1;
    while (n < (int)A.size() + (int)B.size()) n <<= 1;

    fa.resize(n);
    fb.resize(n);

    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; ++i)
        fa[i] *= fb[i];
    fft(fa, true);

    vector<long long> result(n);
    for (int i = 0; i < n; ++i)
        result[i] = llround(fa[i].real());
    // Trim trailing zeros
    while (!result.empty() && result.back() == 0)
        result.pop_back();
    return result;
}

// ---------------- Demo ----------------
int main() {
    vector<long long> A = {3, 2, 5};     // 3 + 2x + 5x²
    vector<long long> B = {5, 1, 2};     // 5 + x + 2x²

    auto C = multiply_poly(A, B);

    cout << "Polynomial multiplication result:\n";
    for (size_t i = 0; i < C.size(); ++i)
        cout << "x^" << i << " -> " << C[i] << "\n";

    // Expected polynomial:
    // (3 + 2x + 5x²)(5 + x + 2x²) = 15 + 13x + 33x² + 9x³ + 10x⁴
}

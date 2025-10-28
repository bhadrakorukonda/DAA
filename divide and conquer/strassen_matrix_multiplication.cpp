#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

using Mat = vector<vector<i64>>;

static inline Mat make(int n, int m, i64 val=0){
    return Mat(n, vector<i64>(m, val));
}
static inline Mat add(const Mat& A, const Mat& B){
    int n=A.size(), m=A[0].size(); Mat C=make(n,m);
    for(int i=0;i<n;++i) for(int j=0;j<m;++j) C[i][j]=A[i][j]+B[i][j];
    return C;
}
static inline Mat sub(const Mat& A, const Mat& B){
    int n=A.size(), m=A[0].size(); Mat C=make(n,m);
    for(int i=0;i<n;++i) for(int j=0;j<m;++j) C[i][j]=A[i][j]-B[i][j];
    return C;
}
static inline Mat classical(const Mat& A, const Mat& B){
    int n=A.size(); Mat C=make(n,n);
    for(int i=0;i<n;++i){
        for(int k=0;k<n;++k){
            i64 aik = A[i][k];
            for(int j=0;j<n;++j) C[i][j] += aik * B[k][j];
        }
    }
    return C;
}

static Mat strassen_rec(const Mat& A, const Mat& B, int threshold){
    int n = A.size();
    if(n <= threshold) return classical(A,B);
    int k = n/2;

    // Split into quadrants
    auto split = [&](const Mat& M){
        Mat M11=make(k,k), M12=make(k,k), M21=make(k,k), M22=make(k,k);
        for(int i=0;i<k;++i) for(int j=0;j<k;++j){
            M11[i][j]=M[i][j];
            M12[i][j]=M[i][j+k];
            M21[i][j]=M[i+k][j];
            M22[i][j]=M[i+k][j+k];
        }
        return array<Mat,4>{M11,M12,M21,M22};
    };
    auto [A11,A12,A21,A22] = split(A);
    auto [B11,B12,B21,B22] = split(B);

    // 7 Strassen products
    Mat M1 = strassen_rec(add(A11,A22), add(B11,B22), threshold);
    Mat M2 = strassen_rec(add(A21,A22), B11,              threshold);
    Mat M3 = strassen_rec(A11,             sub(B12,B22),  threshold);
    Mat M4 = strassen_rec(A22,             sub(B21,B11),  threshold);
    Mat M5 = strassen_rec(add(A11,A12),    B22,           threshold);
    Mat M6 = strassen_rec(sub(A21,A11),    add(B11,B12),  threshold);
    Mat M7 = strassen_rec(sub(A12,A22),    add(B21,B22),  threshold);

    // Combine (Strassen formulas)
    Mat C11 = add(sub(add(M1, M4), M5), M7);
    Mat C12 = add(M3, M5);
    Mat C21 = add(M2, M4);
    Mat C22 = add(sub(add(M1, M3), M2), M6);

    // Stitch quadrants
    Mat C = make(n,n);
    for(int i=0;i<k;++i) for(int j=0;j<k;++j){
        C[i][j]       = C11[i][j];
        C[i][j+k]     = C12[i][j];
        C[i+k][j]     = C21[i][j];
        C[i+k][j+k]   = C22[i][j];
    }
    return C;
}

static inline int next_pow2(int n){
    int p=1; while(p<n) p<<=1; return p;
}

// Public wrapper: multiplies two n×n matrices (pads internally)
Mat strassen(const Mat& A, const Mat& B, int threshold = 64){
    int n = (int)A.size();
    int s = next_pow2(n);

    // Pad to s×s
    Mat Ap = make(s,s), Bp = make(s,s);
    for(int i=0;i<n;++i){
        for(int j=0;j<n;++j){
            Ap[i][j]=A[i][j];
            Bp[i][j]=B[i][j];
        }
    }
    Mat Cp = strassen_rec(Ap, Bp, threshold);

    // Crop back to n×n
    Mat C = make(n,n);
    for(int i=0;i<n;++i) for(int j=0;j<n;++j) C[i][j]=Cp[i][j];
    return C;
}

int main(){
    // Demo: multiply arbitrary-size (not necessarily power of two)
    int n = 5;
    Mat A = make(n,n), B = make(n,n);
    // Fill with small values
    i64 val=1;
    for(int i=0;i<n;++i) for(int j=0;j<n;++j) A[i][j]=(i+j+1), B[i][j]=(i==j)?2:1;

    Mat C = strassen(A,B, /*threshold=*/64);

    cout << "Result (A x B):\n";
    for(int i=0;i<n;++i){
        for(int j=0;j<n;++j) cout << C[i][j] << ' ';
        cout << '\n';
    }
}

#include <bits/stdc++.h>
using namespace std;
using int64 = long long;
const int64 MOD = 1'000'000'007;

struct Mat {
    vector<vector<int64>> a;
    Mat(int n=2, bool ident=false){ a.assign(n, vector<int64>(n,0)); if(ident) for(int i=0;i<n;++i) a[i][i]=1; }
    int n() const { return (int)a.size(); }
};

Mat mul(const Mat& A, const Mat& B){
    int n=A.n(); Mat C(n);
    for(int i=0;i<n;++i)
        for(int k=0;k<n;++k){
            int64 x=A.a[i][k];
            if(!x) continue;
            for(int j=0;j<n;++j)
                C.a[i][j] = (C.a[i][j] + x * B.a[k][j]) % MOD;
        }
    return C;
}

Mat mpow(Mat base, long long exp){
    int n=base.n(); Mat res(n,true);
    while(exp){
        if(exp&1) res = mul(res, base);
        base = mul(base, base);
        exp >>= 1;
    }
    return res;
}

int main(){
    // Example: nth Fibonacci via matrix power
    // [F(n+1) F(n)  ] = [1 1; 1 0]^n
    long long n = 1'000'000; // big n to show log n time
    Mat fib(2);
    fib.a = {{1,1},{1,0}};
    Mat r = mpow(fib, n);
    cout << "F("<<n<<") mod 1e9+7 = " << r.a[0][1] << "\n";
}

#include <bits/stdc++.h>
using namespace std;

// ---- FFT (complex, iterative) ----
using cd = complex<double>;
const double PI = acos(-1.0);

void fft(vector<cd>& a, bool inv){
    int n=a.size();
    for(int i=1,j=0;i<n;++i){
        int b=n>>1; for(; j&b; b>>=1) j^=b; j^=b;
        if(i<j) swap(a[i],a[j]);
    }
    for(int len=2; len<=n; len<<=1){
        double ang = 2*PI/len * (inv? -1 : 1);
        cd wlen(cos(ang), sin(ang));
        for(int i=0;i<n;i+=len){
            cd w(1);
            for(int j=0;j<len/2;++j){
                cd u=a[i+j], v=a[i+j+len/2]*w;
                a[i+j]=u+v; a[i+j+len/2]=u-v; w*=wlen;
            }
        }
    }
    if(inv) for(cd& x:a) x/=n;
}

vector<long long> multiply_poly(const vector<long long>& A, const vector<long long>& B){
    int n=1; while(n<(int)A.size()+(int)B.size()) n<<=1;
    vector<cd> fa(n), fb(n);
    for(size_t i=0;i<A.size();++i) fa[i]=cd((double)A[i],0);
    for(size_t i=0;i<B.size();++i) fb[i]=cd((double)B[i],0);
    fft(fa,false); fft(fb,false);
    for(int i=0;i<n;++i) fa[i]*=fb[i];
    fft(fa,true);
    vector<long long> C(n);
    for(int i=0;i<n;++i) C[i]=llround(fa[i].real());
    while(!C.empty() && C.back()==0) C.pop_back();
    return C;
}

// ---- D&C product tree ----
vector<vector<long long>> polys; // input polynomials (coeff vectors)

vector<long long> build(int l,int r){
    if(r-l==1) return polys[l];
    int m=(l+r)/2;
    auto L = build(l,m);
    auto R = build(m,r);
    return multiply_poly(L,R);
}

int main(){
    // Example: multiply many (1 + a_i x) factors to get generating polynomial
    vector<int> a = {1,2,3,4,5,6,7,8};
    int m = a.size();
    polys.reserve(m);
    for(int v: a) polys.push_back({1, v}); // (1 + v x)

    auto P = build(0, m);
    cout << "Product polynomial coefficients:\n";
    for(size_t i=0;i<P.size();++i)
        cout << "x^" << i << " -> " << P[i] << "\n";
    // Coeff of x^k equals sum of all k-products of distinct a_i (elementary symmetric sums).
}

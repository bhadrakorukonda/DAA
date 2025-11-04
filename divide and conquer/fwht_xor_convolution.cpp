#include <bits/stdc++.h>
using namespace std;

// In-place FWHT (XOR). invert=false for forward, true for inverse.
void fwht(vector<double>& a, bool invert){
    int n=a.size();
    for(int len=1; len<n; len<<=1){
        for(int i=0;i<n;i+=len<<1){
            for(int j=0;j<len;++j){
                double u=a[i+j], v=a[i+j+len];
                a[i+j] = u+v;
                a[i+j+len] = u-v;
            }
        }
    }
    if(invert){
        for(double &x:a) x/=n;
    }
}

vector<long long> xor_convolution(const vector<long long>& A, const vector<long long>& B){
    int n=1; while(n<(int)A.size()+(int)B.size()) n<<=1; // ensure power-of-two big enough
    vector<double> fa(A.begin(),A.end()), fb(B.begin(),B.end());
    fa.resize(n); fb.resize(n);
    fwht(fa,false); fwht(fb,false);
    for(int i=0;i<n;++i) fa[i]*=fb[i];
    fwht(fa,true);
    vector<long long> C(n);
    for(int i=0;i<n;++i) C[i] = llround(fa[i]);
    // optional: trim
    while(!C.empty() && C.back()==0) C.pop_back();
    return C;
}

int main(){
    // Example: A and B of size power-of-two (padding handled)
    vector<long long> A = {1,2,3,4}; // indices 0..3
    vector<long long> B = {5,6,7,8};

    auto C = xor_convolution(A,B);
    cout<<"XOR convolution result:\n";
    for(size_t i=0;i<C.size();++i) cout<<"idx "<<i<<": "<<C[i]<<"\n";
}

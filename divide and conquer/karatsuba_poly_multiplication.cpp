#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<ll> naive_mul(const vector<ll>& A, const vector<ll>& B){
    vector<ll> C(A.size()+B.size()-1,0);
    for(size_t i=0;i<A.size();++i)
        for(size_t j=0;j<B.size();++j)
            C[i+j] += A[i]*B[j];
    return C;
}

vector<ll> karatsuba(const vector<ll>& A, const vector<ll>& B){
    int n = A.size(), m = B.size();
    if(n==0 || m==0) return {};
    if(min(n,m) <= 32) return naive_mul(A,B);

    int k = (max(n,m)+1)/2;

    vector<ll> A0(A.begin(), A.begin()+min(k,n));
    vector<ll> A1(A.begin()+min(k,n), A.end());
    vector<ll> B0(B.begin(), B.begin()+min(k,m));
    vector<ll> B1(B.begin()+min(k,m), B.end());

    auto Z0 = karatsuba(A0,B0);
    auto Z2 = karatsuba(A1,B1);

    // (A0+A1)*(B0+B1)
    vector<ll> A01(max(A0.size(),A1.size()),0), B01(max(B0.size(),B1.size()),0);
    for(size_t i=0;i<A0.size();++i) A01[i]+=A0[i];
    for(size_t i=0;i<A1.size();++i) { if(i>=A01.size()) A01.resize(i+1,0); A01[i]+=A1[i]; }
    for(size_t i=0;i<B0.size();++i) B01[i]+=B0[i];
    for(size_t i=0;i<B1.size();++i) { if(i>=B01.size()) B01.resize(i+1,0); B01[i]+=B1[i]; }

    auto Z1 = karatsuba(A01,B01);
    // Z1 -= Z0 + Z2
    if(Z1.size()<Z0.size()) Z1.resize(Z0.size(),0);
    for(size_t i=0;i<Z0.size();++i) Z1[i]-=Z0[i];
    if(Z1.size()<Z2.size()) Z1.resize(Z2.size(),0);
    for(size_t i=0;i<Z2.size();++i) Z1[i]-=Z2[i];

    // Assemble: Z0 + (Z1 << k) + (Z2 << 2k)
    vector<ll> C(max({Z0.size(), Z1.size()+k, Z2.size()+2*k}), 0);
    for(size_t i=0;i<Z0.size();++i) C[i]+=Z0[i];
    for(size_t i=0;i<Z1.size();++i) C[i+k]+=Z1[i];
    for(size_t i=0;i<Z2.size();++i) C[i+2*k]+=Z2[i];

    // trim trailing zeros
    while(!C.empty() && C.back()==0) C.pop_back();
    return C;
}

int main(){
    vector<ll> A = {3, 2, 5, 1, 0, 4};         // degree 5
    vector<ll> B = {5, 1, 2, 0, 3};            // degree 4

    auto C = karatsuba(A,B);

    cout<<"Polynomial product C = A*B:\n";
    for(size_t i=0;i<C.size();++i)
        cout<<"x^"<<i<<" -> "<<C[i]<<"\n";
}

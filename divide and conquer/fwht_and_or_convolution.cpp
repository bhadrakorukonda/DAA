#include <bits/stdc++.h>
using namespace std;

// ----- FWT-OR -----
void fwt_or(vector<double>& a, bool invert){
    int n=a.size();
    for(int len=1; len<n; len<<=1){
        for(int i=0;i<n;i+=len<<1){
            for(int j=0;j<len;++j){
                if(!invert) a[i+j+len] += a[i+j];
                else        a[i+j+len] -= a[i+j];
            }
        }
    }
}
// ----- FWT-AND -----
void fwt_and(vector<double>& a, bool invert){
    int n=a.size();
    for(int len=1; len<n; len<<=1){
        for(int i=0;i<n;i+=len<<1){
            for(int j=0;j<len;++j){
                if(!invert) a[i+j] += a[i+j+len];
                else        a[i+j] -= a[i+j+len];
            }
        }
    }
}

vector<long long> or_convolution(const vector<long long>& A, const vector<long long>& B){
    int n=1; while(n<(int)A.size() || n<(int)B.size()) n<<=1;
    vector<double> fa(A.begin(),A.end()), fb(B.begin(),B.end());
    fa.resize(n); fb.resize(n);
    fwt_or(fa,false); fwt_or(fb,false);
    for(int i=0;i<n;++i) fa[i]*=fb[i];
    fwt_or(fa,true);
    vector<long long> C(n);
    for(int i=0;i<n;++i) C[i]=llround(fa[i]);
    while(!C.empty() && C.back()==0) C.pop_back();
    return C;
}
vector<long long> and_convolution(const vector<long long>& A, const vector<long long>& B){
    int n=1; while(n<(int)A.size() || n<(int)B.size()) n<<=1;
    vector<double> fa(A.begin(),A.end()), fb(B.begin(),B.end());
    fa.resize(n); fb.resize(n);
    fwt_and(fa,false); fwt_and(fb,false);
    for(int i=0;i<n;++i) fa[i]*=fb[i];
    fwt_and(fa,true);
    vector<long long> C(n);
    for(int i=0;i<n;++i) C[i]=llround(fa[i]);
    while(!C.empty() && C.back()==0) C.pop_back();
    return C;
}

int main(){#include <bits/stdc++.h>
using namespace std;

// ----- FWT-OR -----
void fwt_or(vector<double>& a, bool invert){
    int n=a.size();
    for(int len=1; len<n; len<<=1){
        for(int i=0;i<n;i+=len<<1){
            for(int j=0;j<len;++j){
                if(!invert) a[i+j+len] += a[i+j];
                else        a[i+j+len] -= a[i+j];
            }
        }
    }
}
// ----- FWT-AND -----
void fwt_and(vector<double>& a, bool invert){
    int n=a.size();
    for(int len=1; len<n; len<<=1){
        for(int i=0;i<n;i+=len<<1){
            for(int j=0;j<len;++j){
                if(!invert) a[i+j] += a[i+j+len];
                else        a[i+j] -= a[i+j+len];
            }
        }
    }
}

vector<long long> or_convolution(const vector<long long>& A, const vector<long long>& B){
    int n=1; while(n<(int)A.size() || n<(int)B.size()) n<<=1;
    vector<double> fa(A.begin(),A.end()), fb(B.begin(),B.end());
    fa.resize(n); fb.resize(n);
    fwt_or(fa,false); fwt_or(fb,false);
    for(int i=0;i<n;++i) fa[i]*=fb[i];
    fwt_or(fa,true);
    vector<long long> C(n);
    for(int i=0;i<n;++i) C[i]=llround(fa[i]);
    while(!C.empty() && C.back()==0) C.pop_back();
    return C;
}
vector<long long> and_convolution(const vector<long long>& A, const vector<long long>& B){
    int n=1; while(n<(int)A.size() || n<(int)B.size()) n<<=1;
    vector<double> fa(A.begin(),A.end()), fb(B.begin(),B.end());
    fa.resize(n); fb.resize(n);
    fwt_and(fa,false); fwt_and(fb,false);
    for(int i=0;i<n;++i) fa[i]*=fb[i];
    fwt_and(fa,true);
    vector<long long> C(n);
    for(int i=0;i<n;++i) C[i]=llround(fa[i]);
    while(!C.empty() && C.back()==0) C.pop_back();
    return C;
}

int main(){
    vector<long long> A = {1,2,3,4,5,6,7,8};
    vector<long long> B = {1,1,1,1,1,1,1,1};

    auto C_or  = or_convolution(A,B);
    auto C_and = and_convolution(A,B);

    cout<<"OR convolution:\n";
    for(size_t i=0;i<C_or.size();++i) cout<<"idx "<<i<<": "<<C_or[i]<<"\n";
    cout<<"\nAND convolution:\n";
    for(size_t i=0;i<C_and.size();++i) cout<<"idx "<<i<<": "<<C_and[i]<<"\n";
}

    vector<long long> A = {1,2,3,4,5,6,7,8};
    vector<long long> B = {1,1,1,1,1,1,1,1};

    auto C_or  = or_convolution(A,B);
    auto C_and = and_convolution(A,B);

    cout<<"OR convolution:\n";
    for(size_t i=0;i<C_or.size();++i) cout<<"idx "<<i<<": "<<C_or[i]<<"\n";
    cout<<"\nAND convolution:\n";
    for(size_t i=0;i<C_and.size();++i) cout<<"idx "<<i<<": "<<C_and[i]<<"\n";
}

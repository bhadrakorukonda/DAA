#include <bits/stdc++.h>
using namespace std;

// Multiply two non-negative integers given as strings using Karatsuba (base 10).
// Works for big integers; handles leading zeros.

string strip0(const string& s){
    size_t i = s.find_first_not_of('0');
    return (i==string::npos) ? "0" : s.substr(i);
}

string add_str(const string& A, const string& B){
    string a=A, b=B; reverse(a.begin(),a.end()); reverse(b.begin(),b.end());
    string c; int carry=0;
    for(size_t i=0;i<max(a.size(),b.size());++i){
        int da = i<a.size()?a[i]-'0':0;
        int db = i<b.size()?b[i]-'0':0;
        int s = da+db+carry; c.push_back(char('0'+(s%10))); carry=s/10;
    }
    if(carry) c.push_back(char('0'+carry));
    reverse(c.begin(),c.end()); return strip0(c);
}

string sub_str(const string& A, const string& B){ // assume A>=B
    string a=A, b=B; reverse(a.begin(),a.end()); reverse(b.begin(),b.end());
    string c; int borrow=0;
    for(size_t i=0;i<a.size();++i){
        int da=a[i]-'0' - borrow;
        int db= i<b.size()?b[i]-'0':0;
        if(da<db){ da+=10; borrow=1; } else borrow=0;
        c.push_back(char('0'+(da-db)));
    }
    while(c.size()>1 && c.back()=='0') c.pop_back();
    reverse(c.begin(),c.end()); return strip0(c);
}

string shift10(const string& A, int k){ if(A=="0") return "0"; return A + string(k,'0'); }

string karatsuba(const string& X, const string& Y){
    string x=strip0(X), y=strip0(Y);
    if(x.size()<y.size()) x.insert(x.begin(), y.size()-x.size(), '0');
    if(y.size()<x.size()) y.insert(y.begin(), x.size()-y.size(), '0');
    int n=x.size();
    if(n<=32){ // fallback to grade-school
        vector<int> c(n+n,0);
        for(int i=n-1;i>=0;--i){
            for(int j=n-1;j>=0;--j){
                c[i+j+1] += (x[i]-'0')*(y[j]-'0');
            }
        }
        for(int i=n+n-1;i>0;--i){ c[i-1]+=c[i]/10; c[i]%=10; }
        string s; int i=0; while(i<(int)c.size()-1 && c[i]==0) ++i;
        for(;i<(int)c.size();++i) s.push_back(char('0'+c[i]));
        return s.empty()?"0":s;
    }
    int m = n/2; // split
    string a = x.substr(0, n-m), b = x.substr(n-m);
    string c = y.substr(0, n-m), d = y.substr(n-m);

    string ac = karatsuba(a,c);
    string bd = karatsuba(b,d);
    string apb = add_str(a,b);
    string cpd = add_str(c,d);
    string mid = sub_str(sub_str(karatsuba(apb, cpd), ac), bd);

    return strip0(add_str(add_str(shift10(ac, 2*m), shift10(mid, m)), bd));
}

int main(){
    string A="123456789123456789", B="987654321987654321";
    cout<<karatsuba(A,B)<<"\n";
}

#include <bits/stdc++.h>
using namespace std;

vector<int> lps_build(const string& p){
    int n=p.size(); vector<int> lps(n,0);
    for(int i=1,len=0;i<n;){
        if(p[i]==p[len]) lps[i++]=++len;
        else if(len) len=lps[len-1];
        else lps[i++]=0;
    }
    return lps;
}

vector<int> kmp_search(const string& s, const string& p){
    vector<int> lps = lps_build(p), pos;
    for(int i=0,j=0;i<(int)s.size();){
        if(s[i]==p[j]){ i++; j++; if(j==(int)p.size()){ pos.push_back(i-j); j=lps[j-1]; } }
        else if(j) j=lps[j-1];
        else i++;
    }
    return pos;
}

int main(){
    string s="abxabcabcaby", p="abcaby";
    auto hits = kmp_search(s,p);
    for(int i: hits) cout<<"Match at "<<i<<"\n";
}

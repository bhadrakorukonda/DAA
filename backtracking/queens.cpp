#include <bits/stdc++.h>
using namespace std;

bool safe(vector<int>& col, int r, int c){
    for(int i=0;i<r;++i){
        if(col[i]==c || abs(col[i]-c)==abs(i-r)) return false;
    }
    return true;
}
void solve(int n, int r, vector<int>& col, vector<vector<string>>& ans){
    if(r==n){
        vector<string> board(n, string(n,'.'));
        for(int i=0;i<n;++i) board[i][col[i]]='Q';
        ans.push_back(board); return;
    }
    for(int c=0;c<n;++c){
        if(safe(col,r,c)){ col[r]=c; solve(n,r+1,col,ans); }
    }
}
int main(){
    int n=4;
    vector<int> col(n,-1); vector<vector<string>> ans;
    solve(n,0,col,ans);
    cout<<"Solutions: "<<ans.size()<<"\n";
    for(auto &b: ans){
        for(auto &row: b) cout<<row<<"\n";
        cout<<"-----\n";
    }
}

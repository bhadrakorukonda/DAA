#include <bits/stdc++.h>
using namespace std;

int main(){
    vector<pair<int,int>> act = {{1,3},{2,5},{4,6},{6,7},{5,8},{8,9}};
    sort(act.begin(), act.end(), [](auto &a, auto &b){ return a.second < b.second; });
    vector<pair<int,int>> chosen;
    int last_end = -1;
    for(auto &p: act){
        if(p.first >= last_end){
            chosen.push_back(p);
            last_end = p.second;
        }
    }
    cout<<"Max activities = "<<chosen.size()<<"\n";
    for(auto &p: chosen) cout<<"("<<p.first<<","<<p.second<<") ";
    cout<<"\n";
}

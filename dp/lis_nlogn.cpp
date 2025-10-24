#include <bits/stdc++.h>
using namespace std;

int main(){
    vector<int> a = {10,9,2,5,3,7,101,18};
    vector<int> tail;
    for(int x: a){
        auto it = lower_bound(tail.begin(), tail.end(), x);
        if(it==tail.end()) tail.push_back(x);
        else *it = x;
    }
    cout<<"LIS length = "<<tail.size()<<"\n";
}

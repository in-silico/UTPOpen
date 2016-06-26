#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ll;
#define endl "\n";

int main(){
    ios_base::sync_with_stdio(false);cin.tie(NULL);
    ll n;
    while(cin>>n and n){
        ll sol = ceil((-1 + sqrt(1+8*n*1.0))/2.0);
        if((sol*(sol+1))/2 == n){
            cout<<sol+1<<" "<<sol+1<<endl;
        }else{
            cout<<(((sol*(sol+1))/2)-n) << " "<<sol<<endl;
        }
    }
}

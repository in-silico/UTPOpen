#include<bits/stdc++.h>
using namespace std;

#define MOD 1000007

int mod(int a){
    while(a<0){
        a+=MOD;
        a%=MOD;
    }
    return a%MOD;
}

int main(){
    vector<long long> pascal[1003];
    int sum[1003],image[1002],l,r;
    sum[0] = 0;

    for(int i=0;i<1002;i++){
        long long suma = 0;
        for(int j=0;j<i+1;j++){
            if(j==0 or j==i){suma++;pascal[i].push_back(1);}
            else{
                //cout<<pascal[i-1][j]+pascal[i-1][j-1]<<" ";
                pascal[i].push_back(pascal[i-1][j]+pascal[i-1][j-1]);
                suma += pascal[i-1][j]+pascal[i-1][j-1];
                pascal[i][j] = pascal[i][j]%MOD;
                suma = suma%MOD;
            }
        }
        //cout<<endl;
        sum[i+1] = (sum[i]+suma)%MOD;
    }

    while(cin>>l>>r and l+r>=0){
        l++;r++;
        cout<<mod(sum[r]-sum[l-1])<<endl;
    }
}

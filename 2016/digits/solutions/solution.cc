#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 1000000007;

vector<int> primes;
bool check[5500];
ll memo[550][3][4550];

void genP(){
    primes.push_back(2);
    for(int i = 3; i < 5000; i += 2){
        if(check[i]) continue;
        primes.push_back(i);
        for(int j = i + i; j < 5000; j += i)
            check[j] = true;
    }
}


ll solve(int idx, int top, int sum, string &s){

    if(idx == s.size()){
        return binary_search(primes.begin(), primes.end(), sum);
    }

    if(memo[idx][top][sum] != -1) return memo[idx][top][sum];

    int limit = top ? s[idx] - '0' : 9;
    ll ans = 0;
    for(int i = 0; i <= limit; i++){
        ans = (ans + solve(idx + 1, top && i == limit, sum + i, s)) % mod;
    }
    return memo[idx][top][sum] = ans;
    return ans;
}

bool checkIsSumPrime(string &s){
    int sum = 0;
    for(int i = 0; i < s.size(); i++) sum += s[i] - '0';

    return binary_search(primes.begin(), primes.end(), sum);
}

int main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    genP();
    string  x, y;
    while(cin >> x >> y){
        memset(memo, -1, sizeof memo);
        ll s = solve(0, 1, 0, y);
        memset(memo, -1, sizeof memo);
        cout << (s - solve(0, 1, 0, x) + checkIsSumPrime(x) + mod + mod) % mod << endl;

    }
}



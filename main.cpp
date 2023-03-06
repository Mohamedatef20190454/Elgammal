#include <bits/stdc++.h>
#define ll long long
#define endl '\n'
using namespace std;
vector<int> dec2bin(int num){
    vector<int>arr;
    while (num>0){
        arr.push_back((num%2));
        num/=2;
    }
    return arr;
}
string dec2hex(ll n){
    ll quotient;
    int temp;
    string hexadecimalNumber;
    quotient = n;
    while(quotient!=0)
    {
        temp = (int)(quotient % 16);
        //To convert integer into character
        if( temp < 10)
            temp = temp + 48;
        else
            temp = temp + 55;
        hexadecimalNumber+= temp;
        quotient = quotient / 16;
    }
    reverse(hexadecimalNumber.begin(),hexadecimalNumber.end());
    return hexadecimalNumber;
}
ll negMod(ll a, ll b){
    return (a % b + b) % b;
}
ll random(ll low, ll high){
    return low + rand() % (high - low + 1);
}
ll squareAndMultiply( ll x,  ll H,  ll n){
    long long r;
    vector<int>bin=dec2bin((int)H);
    int i=(int)bin.size();
    i--;
    r = x;
    while(i>0){
        r = (r * r) % n;
        if( bin[--i] == 1 ){
            r = (r * x) % n;
        }
    }
    return r;
}
bool fermit (int s,ll p){
    for (int i = 1; i <= s; ++i) {
        ll a = random(2,p-2);
        if (squareAndMultiply(a,p-1,p)!=1)
            return false;
    }
    return true;
}
ll EEA(ll r0,ll r1){
    int s0=1,s1=0,t0=0,t1=1,i=1;
    vector<ll>r;
    vector<ll>s;
    vector<ll>t;
    r.push_back(r0);r.push_back(r1);s.push_back(s0);s.push_back(s1);t.push_back(t0);t.push_back(t1);
    do {
        i++;
        r.push_back(r[i-2]%r[i-1]);
        ll q = (r[i-2]-r[i])/r[i-1];
        s.push_back((s[i-2])-q*s[i-1]);
        t.push_back((t[i-2])-q*t[i-1]);

    }while(r[i]!=0);
    ll size = (ll)t.size();
    return t[size-2]<0? negMod(t[size-2],r0):t[size-2];
}
void findPrimefactors(vector<ll> v, ll n){
    for(int i=1; i <= n; i++) {
        if (n % i == 0)
            v.push_back(i);
    }
}
vector<ll>findPrimitive(ll n){
    vector <ll>v;
    vector <ll>factors;
    ll phi=n-1;
    findPrimefactors(factors,phi);
    for (int i = 2; i <= phi ; ++i) {
        bool flag= true;
        for (int j = 1; j < factors.size() ; ++j) {
            if(squareAndMultiply(i,phi/factors[j],n)==1){
                flag= false;
                break;
            }
        }
        if (flag){
            v.push_back(i);
        }
    }
    return v;
}
int main() {
    string plainText;
    getline(cin,plainText);
    int ptSize = (int)plainText.size();
    vector<ll>cipherText;
    vector<string>hexaCipherText;
    vector<ll>KEVector;
    srand((unsigned)time(nullptr));
    ll p;
    while (true) {
        p = rand();
        if(fermit(100,p))
            break;
    }
    cout<<"P = "<<p<<endl;
    vector<ll>v = findPrimitive(p);
    ll idx= random(0,v.size()-1);
    ll alpha = v[idx];
    cout<<"alpha = "<<alpha<<endl;
    ll kpr = random(2,p-2);
    cout<<"d = "<<kpr<<endl;
    ll kpub = squareAndMultiply(alpha,kpr,p);
    cout<<"beta = "<<kpub<<endl;
    for (int j = 0; j < ptSize; ++j) {
        cout << "char[" << plainText[j] << "]" << endl;
        ll i = random(2, p - 2);
        cout << "i = " << i << endl;
        ll kE = squareAndMultiply(alpha, i, p);
        cout << "KE = " << kE << endl;
        ll kM = squareAndMultiply(kpub, i, p);
        cout << "KM = " << kM << endl;
        ll y = ((int) plainText[j] * kM) % p;
        cipherText.push_back(y);
        KEVector.push_back(kE);
    }
    int cipherSZ=(int)cipherText.size();
    cout<<"cipherText = ";
    for (int i = 0; i < cipherSZ; ++i) {
        hexaCipherText.push_back(dec2hex(cipherText[i]));
        cout<<hexaCipherText[i];
    }
    cout<<endl;
    string decryptedText;
    for (int i = 0; i < ptSize; ++i) {
        ll kM = squareAndMultiply(KEVector[i], kpr, p) % p;
        ll kMinv = EEA(p, kM);
        cout<<"KMinv["<<hexaCipherText[i]<<"] = "<<kMinv<<endl;
        ll x = (cipherText[i] * kMinv) % p;
        decryptedText+=x;
    }
    cout<<"decrypted Text = "<<decryptedText;


    return 0;
}


#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll findE(ll phi) {
    for(ll i = 2; i < phi; i++) {
        if(__gcd(i, phi) == 1) {
            return i;
        }
    } return -1;
}

ll findD(ll e, ll phi) {
    for(int i = 1; i <= 500; i++) {
        if((i * e) % phi == 1) {
            return i;
        }
    } return -1;
}

ll findC(ll M, ll e, ll n) {
    ll c = M;
    for(ll i = 1; i < e; i++) {
        c = (c * M) % n;
    }
    return c;
}

ll findM(ll c, ll d, ll n) {
    ll m = c;
    for(ll i = 1; i < d; i++) {
        m = (m * c) % n;
    }
    return m;
}

int main() {
    char ch;
    do {
        ll p, q;
        cout << "\nEnter the value of p and q : ";
        cin >> p >> q;

        ll n = p * q;
        ll phi = (p - 1) * (q - 1);
        ll e = findE(phi);
        ll d = 1;
        d = findD(e, phi);

        cout << "\nValue of e and d are : " << e << " " << d << "\n";
        cout << "\nPublic key : {" << e << " " << n << "}\n";
        cout << "\nPrivate key : {" << d << " " << n << "}\n";

        string plaintext = "";
        cout << "\nEnter the Plain text to encrypt : ";
        cin >> plaintext;

        ll c = findC(plaintext.size(), e, n);
        cout << "\nEncrypted key is : " << c << "\n";

        ll m = findM(c, d, n);
        cout << "\nDecrypted key is : " << d << "\n";

        cout << "\nDO YOU WISH TO CONTINUE (y for YES and n for NO) : ";
        cin >> ch;
    } while(ch == 'y');
    cout << "\nHAPPY CODING\n";
    return 0;
}
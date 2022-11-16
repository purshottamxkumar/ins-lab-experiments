#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

bool prim_root(ll i, ll q) {
    // for q = 7, we will be storing the values in the vector from 1 to 6 (size of vector is 7)
    vector<int> v(q);
    ll tmp = q - 1;
    ll res = i;
    while(tmp--) {
        res = res % q;
        if(res >= 1 && res < q) {
            v[res]++;
        } else return false;
        res = res * i;
    }
    for(ll i = 1; i < q; i++) {
        if(v[i] != 1) {
            return false;
        }
    } return true;
}

ll findPrimRoot(ll q) {
    for(ll i = 1; i < q; i++) {
        if(prim_root(i, q)) {
            return i;
        }
    }
    return -1;
}

ll findYa(ll prim_root, ll xa, ll q) {
    ll ya = prim_root % q;
    for(ll i = 1; i < xa - 1; i++) {
        ya = (ya * prim_root) % q;
    }
    return ya;
}

ll findYb(ll prim_root, ll xb, ll q) {
    ll yb = prim_root % q;
    for(ll i = 1; i < xb - 1; i++) {
        yb = (yb * prim_root) % q;
    }
    return yb;
}

ll findKa(ll xa, ll yb, ll q) {
    ll ka = yb % q;
    for(ll i = 1; i < xa - 1; i++) {
        ka = (ka * yb) % q;
    }
    return ka;
}

ll findKb(ll xb, ll ya, ll q) {
    ll kb = ya % q;
    for(ll i = 1; i < xb - 1; i++) {
        kb = (kb * ya) % q;
    }
    return kb;
}

int main() {
    char ch;
    ll q;
    cout << "\nEnter the value of Q prime number: ";
    cin >> q;
    ll primitive_root;
    primitive_root = findPrimRoot(q);
    cout << "\nPrimitive Root is: " << primitive_root << "\n";
    do {
        srand(time(0));
        ll xa = rand() % (q - 1) + 1; // because xa must be less than Q
        ll ya = findYa(primitive_root, xa, q); // here we find public key of A
        ll xb = rand() % (q - 1) + 1; // same as xa
        ll yb = findYb(primitive_root, xb, q); // here we find public key of B

        cout << "\nPrivate Key for person A is: " << xa << "\n";
        cout << "Public Key for person A is: " << ya << "\n";
        cout << "\nPrivate Key for person B is: " << xb << "\n";
        cout << "Public Key for person B is: " << yb << "\n";

        ll ka = findKa(xa, yb, q);
        ll kb = findKb(xb, ya, q);

        if(ka == kb) {
            cout << "\nExchange is Successful!\n";
        } else cout << "\nExchange Failed!\n";
        cout << "\nDO YOU WISH TO CONTINUE (y for YES and n for NO): ";
        cin >> ch;
    } while(ch == 'y');
    cout << "\nHAPPY CODING\n";
    return 0;
}
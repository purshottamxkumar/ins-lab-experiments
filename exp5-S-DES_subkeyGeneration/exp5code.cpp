#include <bits/stdc++.h>
using namespace std;

void left_shift(string &str, int ini, int fin) {
    // left_shift by one bit!
    char ch = str[ini];
    int tmp = fin - ini;
    int i = ini;
    while(tmp--) {
        str[i] = str[i + 1];
        i++;
    }
    str[fin] = ch;
}

void shift_operations(int subkeycount, string &key, char ch) {
    int i = 0;
    while(i < key.size()) {
        int ini = i;
        while(key[i] != ' ' && i < key.size()) {
            i++;
        }
        int fin = i - 1;
        left_shift(key, ini, fin);
        i++; // previously i was pointing to ' ' <- space character
    }
    if(subkeycount != 1 && (subkeycount != 2 && (subkeycount != 9 && subkeycount != 16))) {
        int i = 0;
        while(i < key.size()) {
            int ini = i;
            while(key[i] != ' ' && i < key.size()) {
                i++;
            }
            int fin = i - 1;
            left_shift(key, ini, fin);
            i++;
        }
    }
}

void func(int subkeycount, string &left_key, string &right_key) {
    // perform shift operations
    shift_operations(subkeycount, left_key, 'L');
    shift_operations(subkeycount, right_key, 'R');
    // left_key and right_key are still 56 bits each!

    vector<vector<int> > pc2 = {
        {14, 17, 11, 24, 1, 5}, 
        {3, 28, 15, 6, 21, 10},
        {23, 19, 12, 4, 26, 8},
        {16, 7, 27, 20, 13, 2},
        {41, 52, 31, 37, 47, 55},
        {30, 40, 51, 45, 33, 48},
        {44, 49, 39, 56, 34, 53},
        {46, 42, 50, 36, 29, 32}
    };

    string join_left_right = "";
    for(int i = 0; i < left_key.size(); i++) {
        if(left_key[i] != ' ') {
            join_left_right += left_key[i];
        }
    }
    for(int i = 0; i < right_key.size(); i++) {
        if(right_key[i] != ' ') {
            join_left_right += right_key[i];
        }
    }

    string left_right = ""; // stores 48 bit final permutation of string!
    int tmp = 48;
    int row = 0;
    int col = 0;
    while(tmp) {
        while(col < 6) {
            int idx = pc2[row][col];
            left_right += join_left_right[idx - 1];
            col++;
            tmp--;
        }
        col = 0;
        row = (row + 1) % 8;
    }

    string left_key_XOR = "";
    string right_key_XOR = "";

    // now do permutation!
    int i = 0;
    int cnt = 0;
    int space = 3;
    while(i < 24) {
        if(cnt == 6 && space) {
            left_key_XOR += " ";
            cnt = 0;
            space = space - 1;
        }
        left_key_XOR += left_right[i];
        cnt++;
        i++;
    }

    cnt = 0;
    space = 3;
    while(i < 48) {
        if(cnt == 6 && space) {
            right_key_XOR += " ";
            cnt = 0;
            space = space - 1;
        }
        right_key_XOR += left_right[i];
        cnt++;
        i++;
    }

    string finalKey = "";
    finalKey += left_key_XOR + " " + right_key_XOR;
    cout << "\nSubKey K" << subkeycount << " is: " << finalKey << "\n";
}

int main() {
    string key64 = "";
    cout << "\nEnter the 64 bit key: ";
    getline(cin, key64);
    string key56 = "";
    int i = 0;
    while(i < key64.size()) {
        string tmp = "";
        int cnt = 1;
        while(key64[i] != '\0' && i < key64.size() && cnt != 8) {
            tmp += key64[i];
            i++;
            cnt++;
        }
        key56 += tmp;
        key56 += " ";
        i += 2;
    }
    cout << "\n56 Bit Key is: " << key56 << "\n";

    string left_key = "", right_key = "";
    int cnt = 0;
    i = 0;
    while(cnt < 4) {
        string tmp = "";
        while(key56[i] != ' ' && i < key56.size()) {
            tmp += key56[i];
            i++;
        }
        left_key += tmp;
        if(cnt != 3) {
            left_key += " ";
        }
        i++;
        cnt++;
    }

    cnt = 0;
    while(cnt < 4) {
        string tmp = "";
        while(key56[i] != ' ' && i < key56.size()) {
            tmp += key56[i];
            i++;
        }
        right_key += tmp;
        if(cnt != 3) {
            right_key += " ";
        }
        i++;
        cnt++;
    }

    int subkeycount = 0;
    subkeycount++;

    // 16 rounds of DES and the subkey generation in them!
    for(int i = 0; i < 16; i++) {
        func(subkeycount, left_key, right_key);
        subkeycount++;
    }
    cout << "\nHAPPY CODING!!!\n";
    return 0;
}

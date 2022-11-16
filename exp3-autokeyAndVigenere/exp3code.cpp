#include <bits/stdc++.h>
using namespace std;

string v_encryption(string &pt, string &key) {
    int cnt = 0;
    string encrypted_text = "";
    for(int i = 0; i < pt.size(); i++) {
        int a = key[cnt] - 96;
        int b = pt[i] - 96;
        int c = (a + b) % 26;
        char tmp = char(c + 97);
        encrypted_text += tmp;
        cnt = (cnt + 1) % key.size();
    }
    cout << "\nEncrypted Text is: " << encrypted_text << "\n";
    return encrypted_text;
}

void v_decryption(string &encrypted_text, string &key) {
    string decrypted_text = "";
    int cnt = 0;
    for(int i = 0; i < encrypted_text.size(); i++) {
        int a = key[cnt] - 96;
        int b = encrypted_text[i] - 96;
        int c = b - a;
        if(c < 0) c += 26;
        c = c - 1;
        if(c < 0) c += 26;
        c = c % 26;
        c += 96;
        decrypted_text += char(c);
        cnt = (cnt + 1) % key.size();
    }
    cout << "\nDecrypted Text is: " << decrypted_text << "\n";
}

int vegenere_cipher() {
    int choice;
    string pt, key, tmpkey, encrypted_text;
    pt = key = tmpkey = encrypted_text = "";
    while(1) {
        cout << "\n**** Vegenere Cipher ****";
        cout << "\n0.Exit";
        cout << "\n1.Enter the Plain Text";
        cout << "\n2.Encrypt the Plain Text";
        cout << "\n3.Decrypt the Cipher Text";
        cout << "\n4.Return to Main Menu";
        cout << "\nEnter Choice: ";
        cin >> choice;
        switch(choice) {
            case 0:
            return -1;

            case 1: cout << "\nEnter the Plain Text to be encrypted: ";
            fflush(stdin);
            cin >> pt;
            break;

            case 2: cout << "\nEnter the Key: ";
            cin >> key;
            encrypted_text = v_encryption(pt, key);
            break;

            case 3: cout << "\nEnter the Key: ";
            cin >> tmpkey;
            if(tmpkey != key) {
                cout << "\nWrong Key, Enter Key Again\n";
            } else {
                v_decryption(encrypted_text, key);
            }
            break;

            case 4: goto innerstatement;

            default:
            cout << "\nWRONG CHOICE\n";
        }
    }
    innerstatement:
    return 0;
}

string a_encryption(string &pt, string &key) {
    if(key.size() < pt.size()) {
        int tmp = pt.size() - key.size();
        int i = 0;
        while(tmp--) {
            key += pt[i++];
        }
    }
    string encrypted_text = "";
    for(int i = 0; i < pt.size(); i++) {
        int a = key[i] - 96;
        int b = pt[i] - 96;
        int c = (a + b) % 26;
        char tmp = char(c + 97);
        encrypted_text += tmp;
    }
    cout << "\nEncrypted Text is: " << encrypted_text << "\n";
    return encrypted_text;
}

void a_decryption(string &encrypted_text, string &key) {
    string decrypted_text = "";
    for(int i = 0; i < encrypted_text.size(); i++) {
        int a = key[i] - 96;
        int b = encrypted_text[i] - 96;
        int c = b - a;
        if(c < 0) c += 26;
        c = c - 1;
        if(c < 0) c += 26;
        c = c % 26;
        c += 96;
        decrypted_text += char(c);
    }
    cout << "\nDecrypted Text is: " << decrypted_text << "\n";
}

int autokey_cipher() {
    int choice;
    string pt, key, tmpkey, encrypted_text, prevkey;
    pt = key = tmpkey = encrypted_text = prevkey = "";
    while(1) {
        cout << "\n**** AutoKey Cipher ****";
        cout << "\n0.Exit";
        cout << "\n1.Enter the Plain Text";
        cout << "\n2.Encrypt the Plain Text";
        cout << "\n3.Decrypt the Cipher Text";
        cout << "\n4.Return to Main Menu";
        cout << "\nEnter Choice: ";
        cin >> choice;
        switch(choice) {
            case 0:
            return -1;

            case 1: cout << "\nEnter the Plain Text to be encrypted: ";
            fflush(stdin);
            cin >> pt;
            break;

            case 2: cout << "\nEnter the Key: ";
            cin >> key;
            prevkey = key;
            encrypted_text = a_encryption(pt, key);
            break;

            case 3: cout << "\nEnter the Key: ";
            cin >> tmpkey;
            if(tmpkey != prevkey) {
                cout << "\nWrong Key, Enter Key Again\n";
            } else {
                a_decryption(encrypted_text, key);
            }
            break;

            case 4: goto innerstatement;

            default:
            cout << "\nWRONG CHOICE\n";
        }
    }
    innerstatement:
    return 0;
}

int main() {
    int choice;
    int ans;
    while(1) {
        cout << "\nMain Menu\n";
        cout << "0.Exit\n";
        cout << "1.Perform Vegenere Cipher\n";
        cout << "2.Perform AutoKey Cipher\n";
        cout << "Enter Your Choice: ";
        cin >> choice;

        switch(choice) {
            case 0:
            goto finalstatement;

            case 1: ans = vegenere_cipher();
            if(ans == -1) {
                goto finalstatement;
            }
            break;

            case 2: ans = autokey_cipher();
            if(ans == -1) {
                goto finalstatement;
            }
            break;

            default:
            cout << "\nWRONG CHOICE\n";
        }
    }

    finalstatement:
    cout << "\nHAPPY CODING!!!\n";
    return 0;
}
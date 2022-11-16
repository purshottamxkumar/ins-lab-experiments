#include <bits/stdc++.h>
using namespace std;

void printV(vector<vector<int> > &v) {
    for(int i = 0; i < v.size(); i++) {
        for(int j = 0; j < v[i].size(); i++) {
            cout << v[i][j] << " ";
        } cout << "\n";
    }
}

string matrixMulEncryption(string tmpstr, vector<vector<int> > &v) {
    string finalstr = "";
    for(int i = 0; i < 3; i++) {
        int ans = 0;
        for(int j = 0; j < 3; j++) {
            ans += int(tmpstr[j] - 96) * v[j][i];
        }
        ans = ans % 26;
        char ch = char(ans + 96);
        finalstr += ch;
    }
    return finalstr;
}

string encrypt(string &plaintext, vector<vector<int> > &v) {
    string finalstr = "";
    cout << "\nEnter the key elements (3 X 3 matrix): \n";
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            cin >> v[i][j];
        }
    }
    int i = 0;
    while(i < plaintext.size()) {
        string tmpstr = "";
        int tmp = 3;
        int j = i;
        while(j < plaintext.size() && tmp--) {
            tmpstr += plaintext[j];
            j++;
        }
        tmpstr = matrixMulEncryption(tmpstr, v);
        finalstr += tmpstr;
        i = j;
    }
    return finalstr;
}

string matrixMulDecryption(string tmpstr, vector<vector<int> > &v) {
    string finalstr = "";
    vector<vector<int> > cofactor(3, vector<int> (3));
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            // make a new vector to remove the row and column elements of the element v[i][j]!
            vector<vector<int> > tmpv(3, vector<int> (3));
            tmpv = v;
            for(int k = 0; k < 3; k++) {
                for(int l = 0; l < 3; l++) {
                    if(k == i) {
                        tmpv[k][l] = -100;
                    } else if(l == j) {
                        tmpv[k][l] = -100;
                    }
                }
            }
            int t = 1;
            int a = 0, b = 0, c = 0, d = 0;
            for(int k = 0; k < 3; k++) {
                for(int l = 0; l < 3; l++) {
                    int ele = tmpv[k][l];
                    if(tmpv[k][l] != -100) {
                        if(t == 1) {
                            a = ele;
                        } else if(t == 2) {
                            b = ele;
                        } else if(t == 3) {
                            c = ele;
                        } else d = ele;
                        t++;
                    }
                }
            }
            int eleDeterminantValue = a * d - b * c;
            if((i + j) % 2 == 0) {
                cofactor[i][j] = eleDeterminantValue;
            } else cofactor[i][j] = -1 * eleDeterminantValue;
        }
    }

    // we have calculated the cofactor of the matrix v!
    // now find the adjoint and the inverse of the matrix v!
    vector<vector<int> > inverseMat(3, vector<int> (3));

    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            inverseMat[i][j] = cofactor[j][i];
        }
    }

    int matrixDeterminantValue = 0;
    matrixDeterminantValue += v[0][0] * cofactor[0][0] + v[0][1] * cofactor[0][1] + v[0][2] * cofactor[0][2];

    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            inverseMat[i][j] /= matrixDeterminantValue;
        }
    }

    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(inverseMat[i][j] < 0) {
                inverseMat[i][j] += 26;
            }
        }
    }

    for(int i = 0; i < 3; i++) {
        int ans = 0;
        for(int j = 0; j < 3; j++) {
            ans += int(tmpstr[j] - 96) * inverseMat[j][i];
        }
        ans = ans % 26;
        char ch = char(ans + 96);
        finalstr += ch;
    }
    return finalstr;
}

string decrypt(string &encryptedtext, vector<vector<int> > &v) {
    string finalstr = "";
    int i = 0;
    while(i < encryptedtext.size()) {
        string tmpstr = "";
        int tmp = 3;
        int j = i;
        while(j < encryptedtext.size() && tmp--) {
            tmpstr += encryptedtext[j];
            j++;
        }
        tmpstr = matrixMulDecryption(tmpstr, v);
        finalstr += tmpstr;
        i = j;
    }
    return finalstr;
}

int main() {
    int data, choice;
    string plaintext = "";
    vector<vector<int> > v (3, vector<int> (3));

    cout << "\n****** HILL CIPHER ******\n";

    while(1) {
        cout << "\nThese are the choices: ";
        cout << "\n1 : Enter the New Plain Text.";
        cout << "\n2 : Encrypt the Plain Text.";
        cout << "\n3 : Decrypt the Cipher Text.";
        cout << "\n4 : Exit.\n";
        cout << "\nEnter the Choice: ";
        cin >> choice;

        switch(choice) {
            case 1: cout << "\nEnter the Plain Text (size of the plain text must be multiple of 3): ";
            cin >> plaintext;
            break;

            case 2: plaintext = encrypt(plaintext, v);
            cout << "\nEncrypted Text is : " << plaintext << "\n";
            break;

            case 3: plaintext = decrypt(plaintext, v);
            cout << "\nDecrypted Text is : " << plaintext << "\n";
            break;

            case 4: goto finalstatement;

            default: 
            cout << "\nWrong Choice\n";
        }
    }
    finalstatement: cout << "\nHAPPY CODING!!!\n";
    return 0;
}

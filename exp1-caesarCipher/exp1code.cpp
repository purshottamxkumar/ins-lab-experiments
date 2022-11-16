#include <bits/stdc++.h>
using namespace std;

string encrypt(string &str, int k) {
	string finalstr = "";
	for(int i = 0; i < str.size(); i++) {
		char ch = str[i];
		int t = k % 26;
		while(t--) {
			if(ch == 'z') {
				ch = 'a';
			} else ch++;
		}
		finalstr += ch;
	}
	return finalstr;
}

string decrypt(string &str, int k) {
	string finalstr = "";
	for(int i = 0; i < str.size(); i++) {
		char ch = str[i];
		int t = k % 26;
		while(t--) {
			if(ch == 'a') {
				ch = 'z';
			} else ch--;
		}
		finalstr += ch;
	}
	return finalstr;
}

int main() {
	int choice, key;
	string str;
	while(1) {
		cout << "\n1.Enter the new string.";
		cout << "\n2.Encrypt the string.";
		cout << "\n3.Decrypt the string.";
		cout << "\n4.Exit.";
		cout << "\n\nEnter the choice: ";
		cin >> choice;
		
		switch(choice) {
			case 1: cout << "\nEnter the string: ";
			cin >> str;
			break;
			
			case 2: cout << "\nEnter the key: ";
			cin >> key;
			str = encrypt(str, key);
			cout << "The Encrypted text is: " << str << "\n";
			break;
			
			case 3: cout << "\nEnter the key: ";
			cin >> key;
			str = decrypt(str, key);
			cout << "The Decrypted key is: " << str << "\n";
			break;
			
			case 4: goto finalStatement;
			
			default:
			cout << "\nWrong Choice\n";
		}
	}
	finalStatement: 
	cout << "\nHAPPY CODING!!!\n";
	return 0;
}
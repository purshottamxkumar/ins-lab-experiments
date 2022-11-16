#include <bits/stdc++.h>
using namespace std;

void createNewKey(string &key, vector<vector<char> > &v, map<char, pair<int, int> > &locationChar) {
	string newstr;
	cout << "\nEnter the New Key: ";
	cin >> newstr;
	
	int row, col;
	row = col = 0;
	map<char, int> m;
	int cnt = 0;
	for(int i = 0; i < newstr.size(); i++) {
		if(newstr[i] == 'j') {
			continue;
		} else if(m[newstr[i]] == 0) {
			m[newstr[i]] = 1;
			cnt++; // counting the number of unique characters in the key!
			v[row][col] = newstr[i];
			
			pair<int, int> t;
			t.first = row;
			t.second = col;
			
			if(col == 4) {
				col = 0;
				row++;
			} else col++;
		}
	}
	
	int remcnt = 25 - cnt; // now fill the rest characters in the matrix!
	for(int i = 97; i < 123; i++) {
		if(char(i) == 'j') {
			continue;
		} else if(remcnt) {
			if(m[char(i)] == 0) {
				v[row][col] = char(i);
				remcnt--;
				
				if(col == 4) {
					col = 0;
					row++;
				} else col++;
			}
		} else break;
	}
	
	for(int i = 0; i < v.size(); i++) {
		for(int j = 0; j < v[i].size(); j++) {
			locationChar[v[i][j]].first = i;
			locationChar[v[i][j]].second = j;
		}
	}
	locationChar['j'] = locationChar['i']; // we have specified the location of 'j' same as location of 'i'
	key = newstr;
}

vector<vector<char> > createDiagram(string &str, vector<int> &pos) { // this function makes double
// of the characters in the plain text!
	vector<vector<char> > v;
	int cnt = -1;
	int i = 0;
	for(i = 0; i < str.size() - 1; i++) {
		char ch = str[i];
		vector<char> t;
		if(ch == str[i + 1]) {
			t.push_back(ch);
			t.push_back(ch + 1);
			cnt += 2; // since we are taking two characters each time!
			pos.push_back(cnt);
		} else {
			t.push_back(ch);
			t.push_back(str[i + 1]);
			cnt += 2; // since we are taking two characters each time!
			i++;
		}
		v.push_back(t);
	}
	if(i == str.size() - 1) { // for the odd character remaining in the last!
		vector<char> t;
		char ch = str[str.size() - 1];
		t.push_back(ch);
		t.push_back(ch + 1);
		v.push_back(t);
		cnt++;
		pos.push_back(cnt + 1); // pushing the position of the filler characters in the pos vector!
	}
	return v;
}

string encrypt(vector<vector<char> > &diagram, vector<vector<char> > &matrix, map<char, pair<int, int> > &locationChar, vector<int> &handleJ) {
	string finalstr = "";
	for(int i = 0; i < diagram.size(); i++) {
		vector<char> tmp = diagram[i];
		char firstChar, secondChar, a, b;
		firstChar = tmp[0];
		secondChar = tmp[1];
		
		if(firstChar == 'j') {
			handleJ.push_back(i * 2); // push the position of 'j' in the handleJ vector!
		}
		if(secondChar == 'j') {
			handleJ.push_back(i * 2 + 1); // push the position of 'j' in the handleJ vector!
		}
		
		int row1, row2, col1, col2;
		
		row1 = locationChar[firstChar].first;
		col1 = locationChar[firstChar].second;
		
		row2 = locationChar[secondChar].first;
		col2 = locationChar[secondChar].second;
		
		if(row1 == row2) {
			a = matrix[row1][(col1 + 1) % 5];
			b = matrix[row1][(col2 + 1) % 5];
		} else if(col1 == col2) {
			a = matrix[(row1 + 1) % 5][col1];
			b = matrix[(row2 + 1) % 5][col1];
		} else {
			int newcol1, newcol2;
			newcol1 = col1;
			newcol2 = col2;
			
			while(newcol1 != col2) {
				newcol1 = (newcol1 + 1) % 5;
			}
			while(newcol2 != col1) {
				newcol2 = (newcol2 + 1) % 5;
			}
			
			a = matrix[row1][newcol1];
			b = matrix[row2][newcol2];
		}
		
		finalstr += a;
		finalstr += b;
		diagram[i][0] = a;
		diagram[i][1] = b;
	}
	return finalstr;
}

string decrypt(vector<vector<char> > &diagram, vector<vector<char> > &matrix, map<char, pair<int, int> > &locationChar) {
	string finalstr = "";
	for(int i = 0; i < diagram.size(); i++) {
		vector<char> tmp = diagram[i];
		char firstChar, secondChar, a, b;
		firstChar = tmp[0];
		secondChar = tmp[1];
		
		int row1, row2, col1, col2;
		
		row1 = locationChar[firstChar].first;
		col1 = locationChar[firstChar].second;
		
		row2 = locationChar[secondChar].first;
		col2 = locationChar[secondChar].second;
		
		if(row1 == row2) {
			if(col1 == 0) {
				col1 = 4;
			} else col1 = col1 - 1;
			
			if(col2 == 0) {
				col2 = 4;
			} else col2 = col2 - 1;
			
			a = matrix[row1][col1];
			b = matrix[row1][col2];
		} else if(col1 == col2) {
			if(row1 == 0) {
				row1 = 4;
			} else row1 = row1 - 1;
			
			if(row2 == 0) {
				row2 = 4;
			} else row2 = row2 - 1;
			
			a = matrix[row1][col1];
			b = matrix[row2][col1];
		} else {
			int newcol1, newcol2;
			newcol1 = col1;
			newcol2 = col2;
			
			while(newcol1 != col2) {
				newcol1 = (newcol1 + 1) % 5;
			}
			while(newcol2 != col1) {
				newcol2 = (newcol2 + 1) % 5;
			}
			
			a = matrix[row1][newcol1];
			b = matrix[row2][newcol2];
		}
		
		finalstr += a;
		finalstr += b;
		diagram[i][0] = a;
		diagram[i][1] = b;
	}
	return finalstr;
}

string removePositions(string &str, vector<int> &pos, vector<int> &handleJ) {
	string finalstr = "";
	string tmpstr = "";
	int i, k;
	
	if(pos.size()) { // if there are filler letters in the decrypted text then remove them to get the original text.
		i = k = 0;
		while(k < str.size()) {
			if(pos[i] == k) {
				i++;
			} else {
				finalstr += str[k];
			}
			k++;
		}
		if(finalstr.size()) {
			str = finalstr;
		}
	}
	
	if(handleJ.size()) {
		// if there is any J to be handled!
		i = 0;
		k = 0;
		while(k < str.size()) {
			if(handleJ[i] == k) {
				tmpstr += 'j';
				i++;
			} else tmpstr += str[k];
			k++;
		}
		if(tmpstr.size()) {
			str = tmpstr;
		}
	}
	return str;
}

int main() {
	int choice;
	string key, str, tmpkey;
	
	vector<vector<char> > matrix(5, vector<char> (5));
	vector<vector<char> > diagram;
	map<char, pair<int, int> > locationChar;
	vector<int> pos; // contains diagram
	vector<int> handleJ;
	
	while(1) {
		cout << "\n1.Enter New Plain Text.";
		cout << "\n2.Encrypt the Plain Text.";
		cout << "\n3.Decrypt the Cipher Text.";
		cout << "\n4.Exit.";
		cout << "\n\nEnter the Choice: ";
		cin >> choice;
		
		switch(choice) {
			case 1: cout << "\nEnter the Plain Text: ";
			cin >> str;
			break;
			
			case 2: createNewKey(key, matrix, locationChar);
			diagram = createDiagram(str, pos); // create doubles from the plain text!
			str = encrypt(diagram, matrix, locationChar, handleJ);
			cout << "\nEncrypted string is : " << str << "\n";
			break;
			
			case 3: cout << "\nEnter the Key to Decrypt the Cipher Text: ";
			cin >> tmpkey;
			if(tmpkey == key) {
				str = decrypt(diagram, matrix, locationChar);
				str = removePositions(str, pos, handleJ);
				cout << "\nDecrypted string is: " << str << "\n";
			} else cout << "\nKEY DOES NOT MATCHED, TRY AGAIN!!!\n";
			break;
			
			case 4: goto finalStatement;
			
			default:
				cout << "\nWrong Choice\n";
		}
	}
	finalStatement: cout << "\nHAPPY CODING!!!\n";
	return 0;
}
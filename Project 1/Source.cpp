#include <iostream>
#include <string>
#include <map>
#include <string.h>
#include <algorithm>
#include <vector>

using namespace std;

void cut_words_twos (string src, vector<pair<char,char>> &vec){
	int len = src.size();
	for (int i = 0; i < len; i++)
	{
		pair <char,char> temp;
		temp.first = src[i];
		if (src[i+1] == src[i] || src[i+1] == '\0'){
			temp.second = 'x';
		}
		else{
			temp.second = src[i+1];
			i++;
		}
		vec.push_back(temp);	
	}
}

void cut_words_twos_with_dublication (string src, vector<pair<char,char>> &vec){
	int len = src.size();
	for (int i = 0; i < len; i++)
	{
		pair <char,char> temp;
		temp.first = src[i];
		if (src[i+1] == '\0'){
			temp.second = 'x';
		}
		else{
			temp.second = src[i+1];
			i++;
		}
		vec.push_back(temp);	
	}
}

void cut_words_threes_with_dublication (string src, vector<vector <char>> &vec){
	int len = src.size();
	for (int i = 0; i < len; i++)
	{
		vector <char> temp;
		temp.push_back(src[i]);
		if (src[i+1] == '\0'){
			temp.push_back('x');
			temp.push_back('x');
		}
		else{
			temp.push_back(src[i+1]);
			i++;
			if (src[i+1] == '\0')
				temp.push_back('x');
			else{
				temp.push_back(src[i+1]);
				i++;
			}
		}
		vec.push_back(temp);	
	}
}


string remove_space(string s){
	int i,j;
	int len = s.size();
	char *k = new char [len+1];
	for (i = 0,j = 0; i < len; i++)
	{
		if (s[i] != ' '){
			k[j] = s[i];
			j++;
		}
	}
	k[j] = '\0';
	return k;
}

string ceaser (string src){
	cout << "Input shift amount Key ";
	int n;
	cin>>n;
	int len = src.length();
	char *dst = new char [len+1];
	int i = 0;
	for ( ; i < len;i++)
		dst[i] = ((src[i]-'a' + n) % 26) + 'a';
	dst[i] = '\0';
	return dst;
}

string playFair (string src){
	cout <<  "Enter the Key Word ";
	string key,key0;
	getline(cin,key0);
	key = remove_space(key0);

	char matrix [5][5];
	bool letters [26] = {0}; //frequancy array to prevent dublication
	int row = 0;
	int col = 0;
	map <char,pair<int,int>> mp;  //for easily acess to the chars in 5*5 matrix
	//prepare the 5*5 matrix 
	for(char i : key){
		if (!letters[i-'a']){
			letters[i-'a'] = true;
			if (i == 'j' || i == 'i'){
				letters['j'-'a'] = true;
				letters['i'-'a'] = true;
			}
			if (col > 4){
				col = 0;
				row += 1;
			}
			mp[i] = make_pair(row,col);
			matrix[row][col] = i;
			col += 1;
		}
	}
	if (col > 4){
		col = 0;
		row += 1;
	}
	char k = 'a';
	for (; col < 5; col++){
		bool ok = false;
		while (!ok){
			if (!letters[k-'a']){
				ok = true;
				mp[k] = make_pair(row,col);
				matrix[row][col] = k;
				letters[k-'a'] = true;
				if (k == 'j' || k == 'i'){
					letters['j'-'a'] = true;
					letters['i'-'a'] = true;
				}
			}
			k++;
		}
	}
	if (col > 4){
		col = 0;
		row += 1;
	}
	for (; row < 5;row++){
		for (int col = 0; col < 5; col++){
			bool ok = false;
			while (!ok){
				if (!letters[k-'a']){
					ok = true;
					mp[k] = make_pair(row,col);
					matrix[row][col] = k;
					letters[k-'a'] = true;
					if (k == 'j' || k == 'i'){
						letters['j'-'a'] = true;
						letters['i'-'a'] = true;
					}
				}
				k++;
			}
		}
	}
	//--------------------------------------
	//------------printing playfair matrix------------------
	/*for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
			cout << matrix[i][j] << " ";
		cout<<endl;
	}*/
	
	//------------printing------------------

	vector <pair<char,char>> vec; 
	cut_words_twos(src, vec);
	

	//---------printing the vector----------
	/*for (int i = 0; i < vec.size(); i++)
	{
		cout<<vec[i].first<<" "<<vec[i].second<<"		";
	}
	cout<<endl;*/
	//-------------------------------------
	char *cipher = new char [(vec.size() *2) +1];
	int j = 0;
	for (int i = 0; i < vec.size(); i++){
		int row1 = mp[vec[i].first].first;
		int row2 = mp[vec[i].second].first;
		int col1 = mp[vec[i].first].second;
		int col2 = mp[vec[i].second].second;
		
		if (row1 == row2){
			cipher[j++] = matrix[row1][(col1+1) % 5];
			cipher[j++] = matrix[row1][(col2+1) % 5];
		}
		else if (col1 == col2){
			cipher[j++] = matrix[(row1+1) % 5][col1];
			cipher[j++] = matrix[(row2+1) % 5][col1];
		}
		else {
			cipher[j++] = matrix[row1][col2];
			cipher[j++] = matrix[row2][col1];
		}
	}
	cipher[j] = '\0';
	
	return cipher;
}

string Hill (string src){
	cout << "Please specify key size 2*2 or 3*3 ";
	int type;
	cin>>type;
	
	if (type == 2){
		int matrix [2][2];
		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 2; j++){
				cin>>matrix[i][j];
				matrix[i][j] %= 26;
			}

		//calculate the determinant
		int det = matrix[0][0] * matrix [1][1] - matrix[1][0]*matrix[0][1];
		if (det == 0){ //check if det has an inverse
			cout << "Matrix doesn't have an inverse "<<endl;
			return '\0';
		}
		//---the algorithm---
		vector <pair<char,char>> vec;
		cut_words_twos_with_dublication(src,vec);

		char *cipher = new char [(vec.size()*2) + 1];
		int j = 0;
		for (int i = 0; i < vec.size(); i++)
		{
			char p1 = vec[i].first - 'a';
			char p2 = vec[i].second - 'a';	

			cipher[j++] = (matrix[0][0] * p1 + matrix[1][0] * p2)%26 + 'a';
			cipher[j++] = (matrix[0][1] * p1 + matrix[1][1] * p2)%26 + 'a';
		}
		cipher[j] = '\0';
		return cipher;
	}

	//--------3*3 matrix--------
	else if (type == 3){
		int matrix [3][3];
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++){
				cin>>matrix[i][j];
				matrix[i][j] %= 26;
			}

		//calculate the determinant
		int det1 = matrix[0][0] * (matrix[1][1] * matrix [2][2] - matrix[2][1]*matrix[1][2]);
		int det2 = matrix[0][1] * (matrix[1][0] * matrix [2][2] - matrix[2][0]*matrix[1][2]);
		int det3 = matrix[0][2] * (matrix[1][0] * matrix [2][1] - matrix[2][0]*matrix[1][1]);

		int det = det1-det2+det3;

		if (det == 0){ //check if det has an inverse
			cout << "Matrix doesn't have an inverse "<<endl;
			return '\0';
		}
		//---the algorithm---
		vector <vector<char>> vec;
		cut_words_threes_with_dublication(src,vec);

		//------printing------
		//for (int i = 0; i < vec.size(); i++)
		//{
		//	for (int j = 0; j < vec[i].size(); j++)
		//		cout<<vec[i][j]<<" ";
		//	cout <<"		";
		//}
		//---------------

		char *cipher = new char [(vec.size()*2) + 1];
		int j = 0;
		for (int i = 0; i < vec.size(); i++)
		{
			char p1 = vec[i][0] - 'a';
			char p2 = vec[i][1] - 'a';
			char p3 = vec[i][2] - 'a';

			cipher[j++] = (matrix[0][0] * p1 + matrix[1][0] * p2 + p3 * matrix[2][0])%26 + 'a';
			cipher[j++] = (matrix[0][1] * p1 + matrix[1][1] * p2 + p3 * matrix[2][1])%26 + 'a';
			cipher[j++] = (matrix[0][2] * p1 + matrix[1][2] * p2 + p3 * matrix[2][2])%26 + 'a';
		}
		cipher[j] = '\0';
		return cipher;
	}
	else {
		cout << "Sorry invailed key size"<<endl;
		return '\0';
	}
}

string vigenere (string src){
	cout << "Enter the key WORD ";
	string key,keyfinal;
	getline(cin,key);
	
	cout<< "Enter the mode 1 for auto mode and 0 for repeating mode ";
	bool mode;
	cin>>mode;

	int len = src.size();
	if (!mode){
		int keylen = key.size();
		int mult = len/keylen + (len%keylen > 0);

		//prepare the key
		for (int i = 0; i < mult; i++)
			keyfinal += key;		
		keyfinal = keyfinal.substr(0,len);

		char *cipher = new char [len];
		for (int i = 0; i < len; i++)
			cipher[i] = ((keyfinal[i] -'a' + src[i] -'a') %26) + 'a';
		cipher[len] = '\0';
		return cipher;
	}
	
	else{
		keyfinal += key;
		keyfinal += src;

		keyfinal = keyfinal.substr(0,len);

		char *cipher = new char [len];
		for (int i = 0; i < len; i++)
			cipher[i] = ((keyfinal[i] -'a' + src[i] -'a') %26) + 'a';
		cipher[len] = '\0';
		return cipher;
	}


}

string vernam (string src){
	cout<< "input the key, same legnth as the plain text "<<endl;
	string key;
	getline(cin,key);
	key = remove_space(key);
	if (key.size() < src.size()){
		cout<<"Key size is smaller than the plaintext" <<endl;
		return "";
	}
	char *cipher = new char [src.size()];
	for (int i = 0; i < src.size(); i++) 
		cipher[i] = ((key[i] - 'a') ^ (src[i] - 'a'))%26 + 'a';
	cipher[src.size()] = '\0';
	return cipher;
}


int main()
{

	while (1){
		string src,src2;
		cout << "Enter the plain text "<<endl; 
		getline(cin,src);
	
		transform(src.begin(), src.end(),src.begin(),:: tolower);
		src2 = remove_space(src);

		cout << "Choose the encription method"<<endl<<endl;
		cout << "ceaser press 1"<<endl;
		cout << "PlayFair Press 2"<<endl;
		cout << "Hill press 3"<<endl;
		cout << "Vigenere press 4"<<endl;
		cout << "Vernam press 5"<<endl;
		cout <<"To Exit press 6"<<endl<<endl;

		int n;
		cin>>n;
		cin.ignore();
		cout<<endl;

		if (n == 1)
			cout<<ceaser(src2)<<endl<<endl;
		else if (n == 2)
			cout<<playFair(src2)<<endl<<endl;
		else if (n == 3)
			cout<<Hill(src2)<<endl<<endl;
		else if(n == 4)
			cout<<vigenere(src2)<<endl<<endl;
		else if (n == 5)
			cout<<vernam(src2)<<endl<<endl;
		else if (n == 6)
			break;
		else 
			cout << "please enter between 1 & 5" <<endl<<endl;

		cout<<"--------------------------------------------------"<<endl;
	}
}	
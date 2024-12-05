#include <iostream>
#include <vector>
#include <string>
using namespace std;



// utility functions
vector<int> convert_letters_to_num(string);

// encryption and decryption functions
string encrypt(string,int);
string decrypt(string,int);



int main(){

    cout << "Enter messege: "; string txt; getline(cin,txt);
    cout << "Enter shift key: "; int key; cin >> key;
    
    cout << "The encrypted text is: " << encrypt(txt,key) << endl;

    cout << "The decrypted text is: " << decrypt(encrypt(txt,key),key);

    return 0;
}


// encryption method


vector<int> convert_letters_to_num(string text) {
	vector<int> vec;

	for (char i : text) {

		int character = int(i);

		_asm {
			xor eax, eax
			mov eax, [character]

			; if
			cmp eax, 64
			jng _else
			cmp eax, 91
			jnl _else
			sub eax, 65
			jmp _skip
			_else :
			sub eax, 97
				_skip :
				mov[character], eax
		}

		vec.push_back(character);
	}
	return vec;
}



string encrypt(string plaintext, int shift) {
	 
	_asm {
		xor eax, eax
		xor edx, edx
		xor ebx, ebx

		mov ebx, 26
		mov eax, [shift]
			
		cdq 
		idiv ebx

		mov [shift], edx
	}
	
	string ciphertext = "";
	auto str_vec = convert_letters_to_num(plaintext);
	for (char i : str_vec) {
		
		int character = int(i);
		
		_asm {
			xor eax, eax
			mov eax, [character]

			add eax, [shift]
			add eax, 97

			mov [character], eax
		}

		ciphertext += char(character);
	}
	
	return ciphertext;
}


// decryption method

string decrypt(string ciphertext, int shift) {

	_asm {
		xor eax, eax
		mov eax, [shift]
		neg eax
		mov [shift], eax
	}

	return encrypt(ciphertext, shift);
}
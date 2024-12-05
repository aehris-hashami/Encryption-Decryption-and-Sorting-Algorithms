  #include <iostream>
#include <string>

using namespace std; 

// utility functions
string convert_lower(string&);                 // conversion of capital letters to lewer case

// encryption function
string encrypt(string,string);      // normal encryption
string encrypt(string,string,int);  // encrypting each letter recursively

// decryption function

string decrypt(string,string);



int main(){
    string txt = "ABCd";
    string ctxt = encrypt(txt,convert_lower(txt));
    cout << "Encrypted text: " << ctxt << endl;

    cout << "Decrypted text: " << decrypt(ctxt,txt) << endl;

    return 0;
}

// utility function 

string convert_lower(string& txt) {
	for (int i = 0; i <int(txt.size()); i++) {

		int character = int(txt[i]);

		__asm {
			xor eax, eax
			mov eax, [character]

			; if
			cmp eax, 97
			jl _skip
			cmp eax, 123
			jnl _skip
				xor eax, 32
				mov[character], eax
			_skip :
		}
	}
	return txt;
}

// encryption algorithm 
// ============================================================================================

// original encryption function

string encrypt(string plaintext, string key) {
	plaintext = convert_lower(plaintext); key = convert_lower(key);

	string ctxt = "";

	for (int i = 0; i < int(plaintext.length()); i++) {

		int
			character = 0,
			p = int(plaintext[i]),
			k = int(key[i % key.length()]);
		
		_asm {
			xor eax, eax
			xor ebx, ebx
			xor ecx, ecx
			xor edx, edx

			mov eax, [p]

			; if
				cmp eax, 32
				jz skip
					mov ebx, [k]
					sub eax, 97
					sub ebx, 97

					add eax, ebx

					mov ecx, 26

					div ecx
					add edx, 97

					mov[character], edx
			skip:
		}

		ctxt += char(character);
	}
	return ctxt;
}


// decrypton algorithm 
// =============================================================================================


string decrypt(string ciphertext, string key) {
	ciphertext = convert_lower(ciphertext); key = convert_lower(key);

	string plaintext = "";

	for (int i = 0; i < ciphertext.length(); i++) {
		int
			character = 0,
			c = int(ciphertext[i]),
			k = int(key[i % key.length()]);

		//   plaintext += (ciphertext[i] == ' ')? (' ') : char((int(ciphertext[i]) - int(key[i%key.length()]) + 26)%26 + 97);

		_asm {
			xor eax, eax
			xor ecx, ecx
			xor edx, edx
			
			mov eax, [c]

			; if
				cmp eax, 32
				jz skip

					sub eax, [k]
					add eax, 26

					mov ecx, 26

					div ecx
					add edx, 97
					mov[character], edx
			skip:
		}

		plaintext += char(character);
	}

	return plaintext;
}
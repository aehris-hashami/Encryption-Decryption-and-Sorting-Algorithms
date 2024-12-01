#include <iostream>
#include <string>
#include <vector>
using namespace std; 

// utility functions
string convert_lower(string&);                 // conversion of capital letters to lewer case

// encryption function
string vegenier_cipher(string,string);      // normal encryption
string vegenier_cipher(string,string,int);  // encrypting each letter recursively

// decryption function

string decrypt_vegenier_cipher(string,string);



int main(){
    cout << "Enter text: "; string txt; getline(cin,txt);

    string ctxt = vegenier_cipher(txt,"key");
    cout << "Encrypted text: " << ctxt << endl;

    cout << "Decrypted text: " << decrypt_vegenier_cipher(ctxt,"key") << endl;

    return 0;
}

// utility function 
string convert_lower(string& txt){
    for(int i=0; i<txt.size(); i++) 
        if(65 <= int(txt[i]) && int(txt[i]) < 65+26) txt[i] = char(int(txt[i])^32);
    return txt;
}

// encryption algorithm 
// ============================================================================================

// original encryption function
string vegenier_cipher(string plaintext, string key){
    plaintext = convert_lower(plaintext); key = convert_lower(key);

    string ctxt = ""; 
    
    for(int i=0; i<plaintext.length(); i++) 
        ctxt += (plaintext[i] == ' ')? (' ') : char((int(plaintext[i])+int(key[i%key.length()])- 2*97)%26 + 97); 
    
    return ctxt;
}

// encrypt each letter recursively (optional)
string vegenier_cipher(string ptxt, string key, int itr){
    if(itr == key.length()) return "";
    // given that all letters are in lower case
    return char(int(ptxt[itr]) + (int(ptxt[itr])+int(key[itr%key.length()])- 2*97)%26) + vegenier_cipher(ptxt,key,itr+1);
}

// decrypton algorithm 
// =============================================================================================

string decrypt_vegenier_cipher(string ciphertext, string key){
    ciphertext = convert_lower(ciphertext); key = convert_lower(key);

    string plaintext = "";

    for(int i=0; i<ciphertext.length(); i++){
        plaintext += (ciphertext[i] == ' ')? (' ') : char((int(ciphertext[i]) - int(key[i%key.length()]) + 26)%26 + 97);
    }
    
    return plaintext;
}
#include <iostream>
#include <string>
#include <vector>
using namespace std; 

// utility functions
string convert_lower(string&);                 // conversion of capital letters to lewer case

// encryption function
string encrypt(string,string);      // normal encryption

// decryption function
string decrypt(string,string);



int main(){
    cout << "Enter text: "; string txt; getline(cin,txt);

    string ctxt = encrypt(txt,"key");
    cout << "Encrypted text: " << ctxt << endl;

    cout << "Decrypted text: " << decrypt(ctxt,"key") << endl;

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
string encrypt(string plaintext, string key){
    plaintext = convert_lower(plaintext); key = convert_lower(key);

    string ctxt = ""; 
    
    for(int i=0; i<plaintext.length(); i++) 
        ctxt += (plaintext[i] == ' ')? (' ') : char((int(plaintext[i])+int(key[i%key.length()])- 2*97)%26 + 97); 
    
    return ctxt;
}


// decrypton algorithm 
// =============================================================================================

string decrypt(string ciphertext, string key){
    ciphertext = convert_lower(ciphertext); key = convert_lower(key);

    string plaintext = "";

    for(int i=0; i<ciphertext.length(); i++){
        plaintext += (ciphertext[i] == ' ')? (' ') : char((int(ciphertext[i]) - int(key[i%key.length()]) + 26)%26 + 97);
    }
    
    return plaintext;
}
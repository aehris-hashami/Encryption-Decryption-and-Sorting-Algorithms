#include <iostream>
#include <string>

using namespace std; 

// utility functions
string convert_cap(string);                 // conversion of capital letters to lewer case

// encryption function
string vegenier_cipher(string,string);      // normal encryption
string vegenier_cipher(string,string,int);  // encrypting each letter recursively

// decryption function

string decrypt_vegenier_cipher(string,string);



int main(){
    string txt = "ABCd";
    string ctxt = vegenier_cipher(txt,convert_cap(txt));
    cout << ctxt << endl;

    ctxt = vegenier_cipher(txt,convert_cap(txt),0);
    cout << ctxt << endl;

    return 0;
}

// utility function 
// ==============================================================================================
string convert_cap(string txt){
    for(int i=0; i<txt.size(); i++) 
        if(65 <= int(txt[i]) && int(txt[i]) < 65+26) txt[i] = char(int(txt[i])^32);
    return txt;
}

// encryption algorithm 
// ============================================================================================

// original encryption function
string vegenier_cipher(string ptxt, string key){
    string ctxt = ""; 
    for(int i=0; i<=ptxt.length(); i++) 
        ctxt += char(int(ptxt[i]) + (int(ptxt[i])+int(key[i%key.length()])- 2*97)%26); 
        // given that all letters are in lower case
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

}
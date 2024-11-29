  #include <iostream>
#include <string>

using namespace std; 

// utility functions
string convert_cap(string&);                 // conversion of capital letters to lewer case

// encryption function
string vegenier_cipher(string,string);      // normal encryption
string vegenier_cipher(string,string,int);  // encrypting each letter recursively

// decryption function

string decrypt_vegenier_cipher(string,string);



int main(){
    string txt = "ABCd";
    string ctxt = vegenier_cipher(txt,convert_cap(txt));
    cout << "Encrypted text: " << ctxt << endl;

    cout << "Decrypted text: " << decrypt_vegenier_cipher(ctxt,txt) << endl;

    return 0;
}

// utility function 
string convert_cap(string& txt){
    for(int i=0; i<txt.size(); i++){
        
        int ch = int(txt[i]);

        __asm{
            xor eax, eax
            mov ax, [ch]
            
            ; if
                cmp eax, 97
                jl _skip
                cmp eax, 123
                jnl _skip
                    xor eax, 32
                    mov [ch], ax
            _skip:
        }
    }
    return txt;
}

// encryption algorithm 
// ============================================================================================

// original encryption function
string vegenier_cipher(string plaintext, string key){
    plaintext = convert_cap(plaintext); key = convert_cap(key);

    string ctxt = ""; 
    
    for(int i=0; i<plaintext.length(); i++) 
        ctxt += 
        char((int(plaintext[i])+int(key[i%key.length()])- 2*65)%26 + 65); 
    
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
    ciphertext = convert_cap(ciphertext); key = convert_cap(key);

    string plaintext = "";

    for(int i=0; i<ciphertext.length(); i++){
        // cout << (int(ciphertext[i]) - (int(key[i%key.length()]) - 65) +  26 - 65)%26 + 65 << endl;
        plaintext += char((int(ciphertext[i]) - int(key[i%key.length()]) + 26)%26 + 65);
    }
    
    return plaintext;
}
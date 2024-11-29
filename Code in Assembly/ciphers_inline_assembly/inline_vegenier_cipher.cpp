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
    
    for(int i=0; i<plaintext.length(); i++){

        int 
            ch = 0,
            p = char(plaintext[i]),
            k = char(key[i%key.length()]);
        
        __asm{
            xor eax, eax 
            xor ebx, ebx 

            mov ax, [p]
            mov bx, [k]

            sub ax, 65
            sub bx, 65

            add eax, ebx
            div 26
            add edx, 65

            mov [ch], edx
        }
    
        ctxt += char(ch);
    } 
    return ctxt;
}


// decrypton algorithm 
// =============================================================================================


string decrypt_vegenier_cipher(string ciphertext, string key){
    ciphertext = convert_cap(ciphertext); key = convert_cap(key);

    string plaintext = "";

    for(int i=0; i<ciphertext.length(); i++){
        int 
            ch = 0,
            c = int(ciphertext[i]),
            k = int(key[i%key.length()]);

        __asm{
            xor eax, eax 

            mov ax, [c]
            sub ax, [k]
            add eax, 26

            div 26
            add edx, 65

            mov [ch], dx
        }

        plaintext += char(ch);
    }
    
    return plaintext;
}
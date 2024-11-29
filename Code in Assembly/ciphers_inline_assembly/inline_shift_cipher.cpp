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

vector<int> convert_letters_to_num(string text){
    vector<int> vec;
     
    for(char i:text){

        int ch = int(i);
        
        __asm{
            xor eax, eax
            mov ax, [ch]

            ;if
                cmp ax, 64
                jng _else
                cmp ax, 91
                jnl _else
                    sub eax, 65
                jmp _skip
            _else:
                    sub eax, 97
            _skip:
                mov [ch], ax
        }

        vec.push_back(ch);
    } 
    return vec;
}

string encrypt(string plaintext, int shift){
    auto str_vec = convert_letters_to_num(plaintext); string ciphertext = "";

    for(auto i:str_vec){

        __asm{
            xor eax, eax

            mov ax, [i]
            add ax, [shift]
            div 26
            add edx, 65

            mov [i], edx
        }

        ciphertext += char(i);
    }  
    
    return ciphertext;
}


// decryption method

string decrypt(string ciphertext, int shift){

    __asm{
        xor eax, eax 

        mov ax, [shift]
        neg ax 
        mov [shift], ax
    }

    return encrypt(ciphertext,shift);
}

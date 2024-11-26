#include <iostream>
#include <vector>
using namespace std;

// utility functions
vector<int> convert_letters_to_num(string);

// encryption and decryption functions
string encrypt(string,short int);
string decrypt(string,short int);


int main(){
    cout << "Enter messege: "; string txt; getline(cin,txt);
    cout << "Enter shift key: "; int key; cin >> key;
    
    cout << "The encrypted text is: " << encrypt(txt,key) << endl;

    cout << "The decrypted text is: " << decrypt(encrypt(txt,key),key);

    return 0;
}

vector<int> convert_letters_to_num(string text){
    vector<int> vec;
     
    for(char i:text) vec.push_back
    (
        __asm{
            mov eax, [i]

            ; if condition
                cmp eax, 64
                jle _else
                cmp eax, 91
                jg _else
                    sub eax, 65
            _else:
                sub eax, 97
        }
    );
    
    return vec;
}

string encrypt(string plaintext, short int shift){
    auto str_vec = convert_letters_to_num(plaintext);
    string ciphertext = "";
    
    for(auto i:str_vec){
        __ams{
            mov eax, [i]
                add eax, [shift]
                div 26
                add edx, 65
            mov [i], edx
        }

        ciphertext += char(i);
    } return ciphertext;
}

string decrypt(string ciphertext, short int shift_key){
    __asm{
        mov eax, [shift_key]
            neg eax
        mov [shift_key], eax
    } return encrypt(ciphertext,shift_key);
}
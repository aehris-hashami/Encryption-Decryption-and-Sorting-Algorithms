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
     
    for(char i:text) vec.push_back((64 < int(i) && int(i) < 91)?(int(i)-65):(int(i)-97));
    
    return vec;
}

string encrypt(string plaintext, int shift){
    shift %= 26;
    auto str_vec = convert_letters_to_num(plaintext); string ciphertext = "";

    for(char i:str_vec) {i = i+shift + 97; ciphertext += char(i);}  
    
    return ciphertext;
}


// decryption method

string decrypt(string ciphertext, int shift){
    return encrypt(ciphertext,(-1)*shift);
}

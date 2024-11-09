#include <iostream>
#include <string>
using namespace std;

string shift_cipher
(string plaintext, int shift)
{
    string ciphertext = ""; 
    shift %= 26;
    for(auto i:plaintext) 
        ciphertext += char(int(i) + shift);
    return ciphertext;
}

int main(){
    cout << "Enter messege: "; 
    string txt; getline(cin,txt);
    
    cout << "Enter shift key: "; 
    int key; cin >> key;
    
    string ctxt = shift_cipher(txt,key);
    cout << "The encrypted text is: " << ctxt;

    return 0;
}
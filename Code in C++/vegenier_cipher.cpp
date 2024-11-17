#include <iostream>
#include <string>

using namespace std; 

string convert_cap(string);

string vegenier_cipher(string,string);
string vegenier_cipher(string,string,int);


int main(){
    string txt = "ABCd";
    string ctxt = vegenier_cipher(txt,convert_cap(txt));
    cout << ctxt << endl;

    ctxt = vegenier_cipher(txt,convert_cap(txt),0);
    cout << ctxt << endl;

    return 0;
}

string convert_cap(string txt){
    for(int i=0; i<txt.size(); i++) 
        if(65 <= int(txt[i]) && int(txt[i]) < 65+26) txt[i] = char(int(txt[i])^32);
    return txt;
}

string vegenier_cipher(string ptxt, string key){
    string ctxt = ""; 
    for(int i=0; i<=ptxt.length(); i++) 
        ctxt += char(int(ptxt[i])+int(key[i%key.length()])- 97);
    return ctxt;
}

string vegenier_cipher(string ptxt, string key, int itr){
    if(itr == key.length()) return "";
    return char(int(ptxt[itr]) + int(key[itr%key.length()] - 97)) + vegenier_cipher(ptxt,key,itr+1);
}
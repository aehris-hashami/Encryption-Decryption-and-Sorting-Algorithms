#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>


using namespace std;


bool find(vector<int> vec, int srchval){
    for(auto i:vec) if(i == srchval) return true;
    return false; 
}

vector<int> random_permutation(){
    vector<int> ranper(26); int rval;
    for(int i=0; i < ranper.size();){
        rval = rand()%26+1; 
        if(!find(ranper,rval)){ranper[i] = rval; i++;}
    }return ranper;
}

char shift(char letter, int shift){
    int letter_case; (letter & 32)? letter_case = 97 : letter_case = 65;
    return char(((int(letter) - letter_case + shift)%26) + letter_case);
}

string subs_cipher(string ptxt, vector<int> ranper, int itr){   
    if(itr == ptxt.length()) return "";
    int letter_case; (ptxt[itr] & 32)? letter_case = 97 : letter_case = 65;
    return shift(ptxt[itr],ranper[int(ptxt[itr]) - letter_case]) + subs_cipher(ptxt,ranper,1+itr);
}


int main(){
    vector<int> vec = random_permutation();
    string ptxt = "zyx";
    cout << subs_cipher(ptxt,vec,0);

    return 0;
}
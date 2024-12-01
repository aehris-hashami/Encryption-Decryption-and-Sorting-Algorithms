#include <iostream>
using namespace std;

int main(){



    return 0;
}

vector<string> string_sharding(string ptxt, int lps){
    // lps stands for "letters per segment".
    vector<string> shards; int itr = 0;

    if(ptxt.length()%lps != 0) itr++; 
    itr += ptxt.length()/lps;
    for(int i=1; i <= itr; i++){
        int start, end;
        __asm{
            mov eax, [lps]
                mov ebx, [i]
                dec ebx  i2p
                mul ebx
                inc eax
            mov [lps], eax
        }


        string temp = substring(ptxt,lps*(i - 1) + 1,lps*i);
        shards.push_back(temp);
    } return shards;
}
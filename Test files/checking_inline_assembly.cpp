#include <iostream>
using namespace std;

void count(short int num){
    if(num == 0) return; cout << num << ' ';

    __asm{
        mov ax, [num]
        dec ax
        mov [num], ax
    } 
    
    count(num);
}


int main(){
    count(3);
    return 0;
}
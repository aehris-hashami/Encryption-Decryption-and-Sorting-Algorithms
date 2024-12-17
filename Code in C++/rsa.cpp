#include <iostream>
using namespace std;

int pow(int a, int b);
int calc_coprime(int a, int b);
int gcd(int a, int b);
int modulo_invers(int a, int modul_num);

int encrytp(int p, int q, int msg){
    int n = p*q;
    int e = calc_coprime(p-1,q-1);
    return pow(msg,e)%n;
} 




int main(){


    return 0;
}


int pow(int a, int b){if(b == 0) return 0; return a*pow(a,b-1);}
int gcd(int a, int b){if(b == 0) return a; return gcd(b,a%b);}
int modulo_invers(int a, int modulo){
    if(gcd(a,modulo) != 1) return -1; 



}


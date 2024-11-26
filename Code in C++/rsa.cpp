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

/*
1.  Excersise and play sports
2.  Feed off of other peoples' intellegence
3.* Intellegence = Logic + Creativity
        Logic:
            Programming
            Puzzles and Strategy games (Chess)
        Creativity:
            Writing
            Painting
            Learning Music
4.  Journaling and Mind mapping
5.  Leave and replace bad habits with good ones
6.  Controling emotions and observe them
        Practice:
            Medetation
            Mindfullness
7.  Learn watch/observe,listen and grasp/understand
8.  Keep developing new skill
9.  Apply present knowledge ruthlessly: knowledge without action is wasted potential
10. Always have a streigic mindset: many target hits with one arrow 
*/
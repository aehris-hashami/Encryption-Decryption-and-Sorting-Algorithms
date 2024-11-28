            #include <iostream>
using namespace std;

int main(){

    return 0;
}


// utility function 
string convert_cap(string txt){s
    for(int i=0; i<txt.size(); i++){ 
            __asm{
                mov eax, [txt[i]]
                    ; if condition
                        cmp eax, 65
                        jl skip
                        cmp eax, 91
                        jg skip
                            xor eax, 32
                    skip:
                mov [txt[i]], eax
            }
        } 
    return txt;
}

string vegenier_cipher(string ptxt, string key){
    string ctxt = ""; int length = key.length();
    for(int i=0; i<=ptxt.length(); i++){

        char ch;

        _asm{
            mov eax, [i]
                
                div [length]
                
                mov eax, [key + edx]
                
                    sub eax, 97
                    sub eax, 97
                
                mov [ch], eax

            mov eax, [i]   

            mov eax, [ptxt + eax]

                add eax, [ch]
                div 26

                    mov eax, [i]

                        add edx, [ptxt + eax]
        
            mov [ch], edx
        } 
        
        ctxt += ch;
    }

        // given that all letters are in lower case
    return ctxt;
}
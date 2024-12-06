#include <iostream>
#include <cstring>
#include <vector>
#include <string>
#include <cstdlib>
#include <fstream>
#include <cstring>

using namespace std;
extern "C" int __fastcall Cipher_UI();
extern "C" void __fastcall SignUp_UI(char*, char*);
extern "C" void __fastcall Login_UI();


// shift cipher
// ===================================================

// utility functions
vector<int> convert_letters_to_num(string);

// encryption and decryption functions
string shift_encrypt(string, int);
string shift_decrypt(string, int);

// ===================================================
// vegenier cipher
// ===================================================

// utility functions
string convert_lower(string&);                \

string vgr_encrypt(string, string); 
string vgr_decrypt(string, string);

// ===================================================
// permutation cipher
// ===================================================

// utility functions
bool find(vector<int>, int);
vector<int> gen_rand_indicies(int);
vector<vector<int>> gen_shuffling_transformation_mat(vector<int>, int);
string substring(string, int, int);
vector<string> string_sharding(string, int);
string applying_transformation(vector<vector<int>>, string);
vector<vector<int>> transpose(vector<vector<int>>);
bool check_identity_mat(vector<vector<int>>);
void adjusting_length(string&, int);
void trim_right(string&);
vector<vector<int>> gen_permutaing_matrix(int);

// encrypting & decryption algorithm 
string permute_ncrypt(string, vector<vector<int>>);
string permute_decrypt(string, vector<vector<int>>);

// ===================================================

int main(int argc, char** argv) {
    char*
        pass_str = new char[100],
        * user_str = new char[100];

    // Run Sign Up UI
    int cipher_type = Cipher_UI();
    SignUp_UI(pass_str, user_str);

  
    // encrypt user password with cipher according to switch case/user input

    
    
    switch (cipher_type) {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
    }
    

    // write encrypted password to 
    string usr_password = pass_str;
    writeUsernamePassword(user_str, usr_password.c_str());

    // read encrypted password from file
    usr_password = getPassword(user_str);
  
    // decrypt read ciphertext
    //string dec_password = decrypt(usr_password, matrix);

    // Run Login UI, passing decrypted plaintext as argument

    return 0;
}


// Cipher and utility function definitions

// shift cipher
// ===================================================


// encryption method

vector<int> convert_letters_to_num(string text) {
    vector<int> vec;

    for (char i : text) {

        int character = int(i);

        _asm {
            xor eax, eax
            mov eax, [character]

            ; if
            cmp eax, 64
            jng _else
            cmp eax, 91
            jnl _else
            sub eax, 65
            jmp _skip
            _else :
            sub eax, 97
                _skip :
                mov[character], eax
        }

        vec.push_back(character);
    }
    return vec;
}



string shift_encrypt(string plaintext, int shift) {

    _asm {
        xor eax, eax
        xor edx, edx
        xor ebx, ebx

        mov ebx, 26
        mov eax, [shift]

        cdq
        idiv ebx

        mov[shift], edx
    }

    string ciphertext = "";
    auto str_vec = convert_letters_to_num(plaintext);
    for (char i : str_vec) {

        int character = int(i);

        _asm {
            xor eax, eax
            mov eax, [character]

            add eax, [shift]
            add eax, 97

            mov[character], eax
        }

        ciphertext += char(character);
    }

    return ciphertext;
}


// decryption method

string shift_decrypt(string ciphertext, int shift) {

    _asm {
        xor eax, eax
        mov eax, [shift]
        neg eax
        mov[shift], eax
    }

    return encrypt(ciphertext, shift);
}

// ===================================================
// vegenier cipher
// ===================================================


// utility function 

string convert_lower(string& txt) {
    for (int i = 0; i <int(txt.size()); i++) {

        int character = int(txt[i]);

        __asm {
            xor eax, eax
            mov eax, [character]

            ; if
            cmp eax, 97
            jl _skip
            cmp eax, 123
            jnl _skip
            xor eax, 32
            mov[character], eax
            _skip :
        }
    }
    return txt;
}

// encryption algorithm 
// ============================================================================================

// original encryption function

string vrg_encrypt(string plaintext, string key) {
    plaintext = convert_lower(plaintext); key = convert_lower(key);

    string ctxt = "";

    for (int i = 0; i < int(plaintext.length()); i++) {

        int
            character = 0,
            p = int(plaintext[i]),
            k = int(key[i % key.length()]);

        _asm {
            xor eax, eax
            xor ebx, ebx
            xor ecx, ecx
            xor edx, edx

            mov eax, [p]

            ; if
            cmp eax, 32
            jz skip
            mov ebx, [k]
            sub eax, 97
            sub ebx, 97

            add eax, ebx

            mov ecx, 26

            div ecx
            add edx, 97

            mov[character], edx
            skip :
        }

        ctxt += char(character);
    }
    return ctxt;
}


// decrypton algorithm 


string vrg_decrypt(string ciphertext, string key) {
    ciphertext = convert_lower(ciphertext); key = convert_lower(key);

    string plaintext = "";

    for (int i = 0; i < ciphertext.length(); i++) {
        int
            character = 0,
            c = int(ciphertext[i]),
            k = int(key[i % key.length()]);

        //   plaintext += (ciphertext[i] == ' ')? (' ') : char((int(ciphertext[i]) - int(key[i%key.length()]) + 26)%26 + 97);

        _asm {
            xor eax, eax
            xor ecx, ecx
            xor edx, edx

            mov eax, [c]

            ; if
            cmp eax, 32
            jz skip

            sub eax, [k]
            add eax, 26

            mov ecx, 26

            div ecx
            add edx, 97
            mov[character], edx
            skip :
        }

        plaintext += char(character);
    }

    return plaintext;
}

// ===================================================

// permutation cipher
// ===================================================


// encryptions methods

bool check_identity_mat(vector<vector<int>> matrix) {
    for (int i = 0; i < matrix.size(); i++) if (matrix[i][i] != 1) return false;
    return true;
}

bool find(vector<int> vec, int search_key) {

    int
        boolean_val = 0,
        len = vec.size(),
        * arr = vec.data();

    _asm {
        xor eax, eax
        xor ecx, ecx

        mov esi, [arr]
        mov ecx, [len]

        ; if
        cmp ecx, 0
        jnz _not_empty

        mov[boolean_val], ecx
        jmp _break_from_loop

        _not_empty :

    _for:

        mov eax, [esi]
            ; if
            cmp eax, [search_key]
            jnz _skip

            mov eax, [boolean_val]
            inc eax
            mov[boolean_val], eax
            jmp _break_from_loop

            _skip :

        add esi, 4
            loop _for
            _break_from_loop :
    }

    return bool(boolean_val);
}


vector<int> gen_rand_indicies(int dimensions) {
    vector<int> vec; srand(time(0));

    for (int i = 0; i < dimensions;) {
        int r = rand();

        _asm {
            xor eax, eax
            xor ecx, ecx

            mov eax, [r]
            mov ecx, [dimensions]
            cdq
            div ecx
            mov[r], edx
        }

        if (!find(vec, r)) {
            vec.push_back(r);

            _asm {
                mov eax, [i]
                inc eax
                mov[i], eax
            }
        }
    }

    return vec;
}

vector<vector<int>> gen_shuffling_transformation_mat(vector<int> randind_vec, int dimensions) {
    vector<vector<int>> shuffling_matrix(dimensions, vector<int>(dimensions, 0)); // initializing matrix

    for (int i = 0; i < dimensions; i++) {
        int temp = shuffling_matrix[randind_vec[i]][i];
        _asm {
            xor eax, eax
            mov eax, [temp]
            inc eax
            mov[temp], eax
        }
        shuffling_matrix[randind_vec[i]][i] = temp;
    }
    return shuffling_matrix;
}

string substring(string str, int start, int end) {
    string substr = "";

    for (int i = start - 1; i < end; i++) substr += str[i];

    return substr;
}

vector<string> string_sharding(string ptxt, int lps) {
    // lps stands for "letters per segment".
    vector<string> shards; int itr = 0;

    if (ptxt.length() % lps != 0) itr++; itr += ptxt.length() / lps;

    for (int i = 1; i <= itr; i++) {
        string temp = substring(ptxt, lps * (i - 1) + 1, lps * i);
        shards.push_back(temp);
    } return shards;
}

string applying_transformation(vector<vector<int>> mat, string str) {
    string result = "";
    for (int i = 0; i < mat.size(); i++) {
        for (int j = 0; j < mat.size(); j++)
            if (char(mat[i][j] * (int(str[j]))) != '\0') result += char(mat[i][j] * (int(str[j])));
    }return result;
}

void adjusting_length(string& str, int length) {
    for (int i = 0; i < length; i++) str += " ";
}

vector<vector<int>> gen_permutaing_matrix(int dimension) {
    srand(time(0)); vector<vector<int>> matrix;

    while (1) {
        matrix = gen_shuffling_transformation_mat(gen_rand_indicies(dimension), dimension);
        if (!check_identity_mat(matrix)) break;
    }

    return matrix;
}

string permute_encrypt(string plaintext, vector<vector<int>> matrix) {

    // adjusting the length of the plaintext for ease of encrypting and decrypting
    adjusting_length(plaintext, matrix.size() - plaintext.length() % matrix.size());

    // shard the plaintext into peices
    vector<string> shards = string_sharding(plaintext, matrix.size());

    // shuffle the letters within the shards
    vector<string> shuffled_shards;
    for (auto i : shards) shuffled_shards.push_back(applying_transformation(matrix, i));

    // concatenate all shuffled shards to a single ciphered string
    string cipher_text = ""; for (auto i : shuffled_shards) cipher_text += i;
    return cipher_text;

}

// decrypting method

vector<vector<int>> transpose(vector<vector<int>> matrix) {
    vector<vector<int>> transpose(matrix.size(), vector<int>(matrix.size(), 0));

    for (int i = 0; i < matrix.size(); i++) for (int j = 0; j < matrix.size(); j++) {
        int
            temp = matrix[i][j],
            size = matrix.size(),
            * arr = transpose[j].data();

        _asm {
            ; geting the index of 2D
            mov eax, [i]

            ; calculating the address at that index
            mov ecx, 4
            mul ecx

            ; assignig the value
            mov ecx, [temp]

            mov esi, [arr]
            add esi, eax

            mov[esi], ecx
        }
    }

    return transpose;
}

void trim_right(string& str) { str.erase(str.find_last_not_of(" ") + 1); }


string permute_decrypt(string ciphertext, vector<vector<int>> mat) {
    // get the transpose of the matrix
    vector<vector<int>> transpose_mat = transpose(mat);

    for (int i = 0; i < mat.size(); i++) { for (auto i : transpose_mat[i]) cout << i << ' '; cout << endl; } cout << endl;

    // break down the cipher text into apropriate segments
    vector<string> cipher_shards = string_sharding(ciphertext, mat.size());

    // apply transformation to individual cipher segments
    vector<string> plain_shards; for (auto i : cipher_shards) plain_shards.push_back(applying_transformation(transpose_mat, i));

    // concatenate all the transformed segments and return it
    string plaintext = ""; for (auto i : plain_shards) plaintext += i;

    // triming the extra added white spaces (if there is present)
    trim_right(plaintext);


    return plaintext;
}

// ====================================================


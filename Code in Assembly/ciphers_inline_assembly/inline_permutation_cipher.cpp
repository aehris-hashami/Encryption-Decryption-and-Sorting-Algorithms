#include <iostream>
#include <string>
#include <vector>

using namespace std;

// UI (userinterface function)

string get_text() {
  // getting plaint text input from user
  cout << "Enter text: ";
  string text;
  getline(cin, text);
  return text;
}

// utility functions
bool find(vector<int>, int);
vector<int> gen_rand_indicies(int);
vector<vector<int>> gen_shuffling_transformation_mat(vector<int>, int);
string substring(string, int, int);
vector<string> string_sharding(string, int);
string applying_transformation(vector<vector<int>>, string);
vector<vector<int>> transpose(vector<vector<int>>);
bool check_identity_mat(vector<vector<int>>);
void adjusting_length(string &, int);
void trim_right(string &);
vector<vector<int>> gen_permutaing_matrix(int);

// encrypting & decryption algorithm
string encrypt(string, vector<vector<int>>);
string decrypt(string, vector<vector<int>>);

int main() { // testing

  string plaintext = get_text(); // geting text from the user

  // generating random shuffled identiy matrix
  int dimension = rand() % plaintext.length();
  vector<vector<int>> matrix = gen_permutaing_matrix(dimension);

  // displaying the permutation matrix
  for (int i = 0; i < dimension; i++) {
    for (auto i : matrix[i])
      cout << i << ' ';
    cout << endl;
  }
  cout << endl;

  // encrypt the plain text
  string ciphertext = encrypt(plaintext, matrix);
  cout << "Cipher text generated: " << ciphertext << endl;

  // dycrypt the cipher text
  string deciphertext = decrypt(ciphertext, matrix);
  cout << "Decrypted text generated: " << deciphertext << endl;

  return 0;
}

// encryptions methods

bool check_identity_mat(vector<vector<int>> matrix) {
    for (int i = 0; i < matrix.size(); i++) if (matrix[i][i] != 1) return false;
    return true;
}

bool find(vector<int> vec, int search_key) {

    int
        boolean_val = 0,
        len = vec.size(),
        *arr = vec.data();

    _asm {
        xor eax, eax
        xor ecx, ecx

        mov esi, [arr]
        mov ecx, [len]

        ; if 
            cmp ecx, 0
            jnz _not_empty

                mov [boolean_val], ecx
                jmp _break_from_loop

            _not_empty:
        
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
            mov [r], edx
        }

        if (!find(vec, r)) { 
            vec.push_back(r); 
            
            _asm {
                mov eax, [i]
                inc eax
                mov [i], eax
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
            mov [temp], eax
        }
        shuffling_matrix[randind_vec[i]][i] = temp ;
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
        shards.push_back(substring(ptxt, lps * (i - 1) + 1, lps * i));
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

string encrypt(string plaintext, vector<vector<int>> matrix) {

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
            *arr = transpose[j].data();

        _asm {
            ; geting the index of 2D 
            mov eax, [i]

            ; calculating the address at that index
            mov ecx, 4
            mul ecx

<<<<<<< HEAD
      _asm {
          xor esi, esi
          mov esi, [mat]
          mov [trans], esi
      }
=======
            ; assignig the value
            mov ecx, [temp]

            mov esi, [arr]
            add esi, eax

            mov [esi], ecx
        }
>>>>>>> 75e38cbbf69472c9eb5a1395e672576475215427
    }

    return transpose;
}

void trim_right(string& str) { str.erase(str.find_last_not_of(" ") + 1); }


string decrypt(string ciphertext, vector<vector<int>> mat) {
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



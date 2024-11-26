#include <iostream>
#include <vector>
#include <string>

using namespace std;

// utility functions

//      string appending functions
string substring(string,int,int);
vector<string> string_sharding(string,int);
vector<int> convert_letters_to_num(string);

//      matrix operational functions
vector<vector<int>> gen_square_matrix(int);
int determinant(vector<vector<int>>);
vector<vector<int>> adjugate_matrix(vector<vector<int>>);
vector<vector<int>> inverse_matrix(vector<vector<int>>&);
vector<int> apply_transformation(vector<vector<int>>,string);


// encryption & decryption 
string encrypt(string,vector<vector<int>>);
string decrypt(string,vector<vector<int>>);


int main(){

    vector<vector<int>>  keymatrix = gen_square_matrix(4);
    for(auto i:keymatrix){for(auto j:i) cout << j << ' '; cout << endl;} cout << endl;

    string plaintext = "abcdefgh"; cout << "Plain text: " << plaintext << endl;
    string ciphertext = encrypt(plaintext,keymatrix); cout << "Cipher text: " << ciphertext << endl;

    return 0;
}


// encryption method
// ==============================================================================================
string substring(string str, int start, int end){
    string substr = "";

    for(int i=start-1; i < end; i++) substr += str[i];
  
    return substr; 
}

vector<string> string_sharding(string ptxt, int lps){
    vector<string> shards; int itr = 0;
  
    if(ptxt.length()%lps != 0) itr++; itr += ptxt.length()/lps;  
    for(int i=1; i <= itr; i++){
        auto temp = substring(ptxt,lps*(i - 1) + 1,lps*i);
        shards.push_back(temp);
    } return shards;
}

vector<int> apply_transformation(vector<vector<int>> mat, vector<int> vec){ 
    vector<int> result(vec.size(),0);

    for(int i=0; i<mat.size(); i++) for(int j=0; j<mat.size() && j<vec.size(); j++) result[i] += mat[i][j]*vec[j];
    
    return result;
} 

vector<vector<int>> gen_square_matrix(int dimension){
    vector<vector<int>> matrix(dimension, vector<int>(dimension,0)); srand(time(0));
    
    for(int i=0; i<dimension; i++) for(int j=0; j<dimension; j++) matrix[i][j] = rand()%9 + 1;
     
    return matrix; 
}

vector<int> convert_letters_to_num(string text){
    vector<int> char_positional_val;
    
    for(auto i:text) char_positional_val.push_back((64 < i && i < 91)?(i-65):(i-97));
    
    return char_positional_val;
}

string encrypt(string plaintext, vector<vector<int>> matrix){
    // apply sharding
    vector<string> plain_shards = string_sharding(plaintext,matrix.size());
    vector<vector<int>> plain_vec; for(auto i:plain_shards) plain_vec.push_back(convert_letters_to_num(i));

    // apply transformation and take modulo 26, and then convert the numbers to capital letters
    vector<vector<int>> cipher_vec; 
    for(auto i:plain_vec) cipher_vec.push_back(apply_transformation(matrix,i));
    for(int i=0; i<cipher_vec.size(); i++) for(int j=0; j<cipher_vec[i].size(); j++) cipher_vec[i][j] = cipher_vec[i][j]%26 + 65;

    // concatenate all the cipher shards into one cipher string
    string cipher_text = ""; for(auto i:cipher_vec) for(auto j:i) cipher_text += char(j);
    return cipher_text;
}


// decryption
// ==============================================================================================


int determinant(vector<vector<int>> mat) {
    int n = mat.size();
    if (n == 1) return mat[0][0];
    if (n == 2) return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];

    int det = 0;
    for (int col = 0; col < n; ++col) {
        vector<vector<int>> minor;
        for (int i = 1; i < n; ++i) {
            vector<int> row;
            for (int j = 0; j < n; ++j) {
                if (j != col) row.push_back(mat[i][j]);
            }
            minor.push_back(row);
        }
        det += (col % 2 == 0 ? 1 : -1) * mat[0][col] * determinant(minor);
    }
    return det;
}

// Function to compute the adjugate matrix
vector<vector<int>> adjugate_matrix(vector<vector<int>> mat){
    int n = mat.size();
    vector<vector<int>> adj(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            vector<vector<int>> minor;
            for (int x = 0; x < n; ++x) {
                if (x == i) continue;
                vector<int> row;
                for (int y = 0; y < n; ++y) {
                    if (y == j) continue;
                    row.push_back(mat[x][y]);
                }
                minor.push_back(row);
            }
            adj[j][i] = determinant(minor) * ((i + j) % 2 == 0 ? 1 : -1); // Transpose
        }
    }
    return adj;
}

// Function to compute the inverse matrix
vector<vector<int>> inverse_matrix(vector<vector<int>>& mat) {
    int n = mat.size();
    int det = determinant(mat);
    if (!det) throw invalid_argument("Matrix is singular and has no inverse.");

    vector<vector<int>> adj = adjugate_matrix(mat);
    vector<vector<int>> inverse(n, vector<int>(n));
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << "inverse[" << i << "][" << j << "] = " << inverse[i][j] << endl;

            inverse[i][j] = adj[i][j] / det;
        }
    }
    return inverse;
}

string decrypt(string cipher_text, vector<vector<int>> mat){
    // get the inverse matrix
    vector<vector<int>> inverse_mat = inverse_matrix(mat);
    for(int i=0; i<mat.size(); i++){for(auto i:inverse_mat[i]) cout << i << ' '; cout << endl;} cout << endl; 

    // break down the cipher text into apropriate segments
    vector<string> cipher_shards = string_sharding(cipher_text,mat.size());

    // convert the letters to characters positional values after applying transformation
    vector<vector<int>> plain_vec; for(auto i:plain_vec) plain_vec.push_back(apply_transformation(inverse_mat,i));
    for(auto i:plain_vec) for(auto j:i) j = (j%26) + 65; 
    for(int i=0; i<plain_vec.size(); i++) for(int j=0; j<plain_vec.size(); j++) 
        cipher_shards[i][j] = char(plain_vec[i][j]);

    // concatenate all the transformed segments and return it
    string plaintext = ""; for(auto i:cipher_shards) plaintext += i;
    return plaintext;
}
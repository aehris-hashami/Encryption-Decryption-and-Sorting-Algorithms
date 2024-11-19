#include <iostream>
#include <vector>
#include <string>

using namespace std;

// transformational cipher

// utility functions

string substring(string str, int start, int end){
    string substr = "";
    for(int i=start-1; i < end; i++) substr += str[i];
    return substr; 
}

vector<string> string_sharding(string ptxt, int lps){
    vector<string> shards; int itr = 0;
    if(ptxt.length()%lps != 0) itr++; itr += ptxt.length()/lps;
    
    for(int i=1; i <= itr; i++){
        string temp = substring(ptxt,lps*(i - 1) + 1,lps*i);
        shards.push_back(temp);
    } return shards;
}

string applying_transformation(vector<vector<int>> mat, string str){
    string result = "";
    for(int i=0; i<mat.size(); i++){
        for(int j=0; j<mat.size(); j++)
            if(char(mat[i][j]*(int(str[j]))) != '\0') result += char(mat[i][j]*(int(str[j])));
    }return result;
}   

// encryption

vector<vector<int>> gen_square_matrix(int dimension);

 vector<int> apply_transformation(vector<vector<int>> matrix, string text);

string encrypt(string plaintext);

// decryption

 vector<string> apply_transformation(vector<vector<int>> matrix, vector<int> vec);

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

string decrypt(vector<int> cipher_vec, vector<vector<int>> mat){
    // get the inverse matrix
    vector<vector<int>> inverse_mat = inverse_matrix(mat);
    for(int i=0; i<mat.size(); i++){for(auto i:inverse_mat[i]) cout << i << ' '; cout << endl;} cout << endl; 

    // break down the cipher text into apropriate segments
    vector<string> cipher_shards = string_sharding(cipher_vec,mat.size());

    // apply transformation to individual cipher segments
    vector<string> plain_shards; for(auto i:cipher_shards) plain_shards.push_back(applying_transformation(inverse_mat,i));

    // concatenate all the transformed segments and return it
    string plaintext = ""; for(auto i:cipher_shards) plaintext += i;
    return plaintext;
}
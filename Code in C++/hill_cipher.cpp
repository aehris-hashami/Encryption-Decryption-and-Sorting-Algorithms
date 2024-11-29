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
vector<int> apply_transformation(vector<vector<int>>,vector<int>);


// encryption & decryption 
vector<int> encrypt(string,vector<vector<int>>);
string decrypt(vector<int>,vector<vector<int>>);


int main(){
    // generating and checking transformational matrix
    vector<vector<int>>  keymatrix = gen_square_matrix(2); 
    if(determinant(keymatrix) == 0) return 0; else cout << "Invertebale matrix is slected" << endl;
    for(auto i:keymatrix){for(auto j:i) cout << j << ' '; cout << endl;} cout << endl;

    // sample plaintext and testing encryption function
    string plaintext = "abcdefgh"; cout << "Plain text: " << plaintext << endl;
    vector<int> cipher_vec = encrypt(plaintext,keymatrix); 

    // displaying encrypted values
    cout << "Encryted letter values: ";
    for(auto i:cipher_vec) cout << i << ' '; cout << endl;

    // checking inverted matrix
    vector<vector<int>> invmat = inverse_matrix(keymatrix);
    for(auto i:invmat){for(auto j:i) cout << j << ' '; cout << endl;} cout << endl;

    // decrypting the encrypted cipher text
    cout << "After decryption: " << decrypt(cipher_vec,keymatrix) << endl;

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


vector<vector<int>> gen_square_matrix(int dim){ 
    vector<vector<int>> matrix(dim, vector<int>(dim,0)); srand(time(0));
    
    do{ 
        for(int i=0; i<dim; i++) for(int j=0; j<dim; j++) matrix[i][j] = rand();
    }while(determinant(matrix) != 1 && determinant(matrix) != -1);
    
    cout << endl << "det(mat) = " << determinant(matrix) << endl;

    return matrix; 
}

vector<int> convert_letters_to_num(string text){
    vector<int> char_positional_val;
    
    for(auto i:text) char_positional_val.push_back((64 < i && i < 91)?(i-65):(i-97));
    
    return char_positional_val;
}

vector<int> encrypt(string plaintext, vector<vector<int>> matrix){
    // apply sharding
    vector<string> plain_shards = string_sharding(plaintext,matrix.size());
    vector<vector<int>> plain_vec; for(auto i:plain_shards) plain_vec.push_back(convert_letters_to_num(i));

    // apply transformation
    vector<vector<int>> cipher_vec;
    for(auto i:plain_vec) cipher_vec.push_back(apply_transformation(matrix,i));
    vector<int> transform_vec; for(auto i:cipher_vec) for(auto j:i) transform_vec.push_back(j);
    return transform_vec;

}


// decryption
// ==============================================================================================



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
    
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) inverse[i][j] = adj[i][j] / det;
         
    return inverse;
}

vector<int> segment(vector<int> vec, int start, int end){
    vector<int> segment; 
    for(int i=start-1; i<end; i++) segment.push_back(vec[i]);
    return segment;
}

vector<vector<int>> sharding(vector<int> vec, int lps){
    // lps means line per segment
    vector<vector<int>> shards;
    for(int i=1; i<vec.size()/lps; i++) shards.push_back(segment(vec,i*lps,(i+1)*lps));
    return shards;
}

string decrypt(vector<int> ciphertext, vector<vector<int>> mat){
    // get the inverse matrix
    vector<vector<int>> inverse_mat = inverse_matrix(mat);
    //for(auto i:inverse_mat) for(auto j:i){cout << j << ' '; cout << endl;} cout << endl;

    // get individual vectors and apply transformation by inverse matrix
    vector<vector<int>> cipher_vec = sharding(ciphertext,inverse_mat.size());

    cout << endl;
    for(auto i:cipher_vec){for(auto j:i) cout << j << ' '; cout << endl;} cout << endl;

    // applying transformation to all the cipher vectors
    vector<vector<int>> plain_vec; 
    for(auto i:cipher_vec) plain_vec.push_back(apply_transformation(inverse_mat,i));

    // concatenating all the characters into one string
    string plaintext = "";
    for(int i=0; i<plain_vec.size(); i++) for(int j=0; j<plain_vec[i].size(); j++) 
        plaintext += char(plain_vec[i][j] + 65);
    return plaintext;
} 

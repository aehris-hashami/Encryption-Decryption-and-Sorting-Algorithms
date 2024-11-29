#include <iostream>
#include <string>
#include <vector>
using namespace std;

// utility functions
bool find(vector<int>,int);
vector<int> gen_rand_indicies(int);
vector<vector<int>> gen_shuffling_transformation_mat(vector<int>,int);
string substring(string,int,int);
vector<string> string_sharding(string,int);
string applying_transformation(vector<vector<int>>,string);
vector<vector<int>> transpose(vector<vector<int>>);

// encrypting & decryption algorithm 
string encrypt(string,vector<vector<int>>);
string decrypt(string,vector<vector<int>>);



int main(){     // testing
    
    // generating random shuffled identiy matrix    
    srand(time(0)); int dimension = rand()%4 + 2;
    vector<vector<int>> matrix = gen_shuffling_transformation_mat(gen_rand_indicies(dimension),dimension);

    for(int i=0; i<dimension; i++){for(auto i:matrix[i]) cout << i << ' '; cout << endl;} cout << endl; 


    // getting plaint text input from user
    cout << "Enter text: "; string plaintext; getline(cin,plaintext);

    // encrypt the plain text
    string ciphertext = encrypt(plaintext,matrix);
    cout << "Cipher text generated: " << ciphertext << endl;

    // dycrypt the cipher text
    string deciphertext = decrypt(ciphertext,matrix);
    cout << "Decrypted text generated: " << deciphertext << endl;

    return 0;
}

// encryptions methods


bool find(vector<int> vec, int search_key){
    for(auto i:vec) if(i == search_key) return true; 
    return false;
}

vector<int> gen_rand_indicies(int dimensions){
    vector<int> vec; srand(time(0));

    for(int i=0; i<dimensions;){
        int r = rand();

        __asm{
            xor eax, eax 
            mov ax, [r]
            div [dimensions]
            mov [r], edx
        }

        if(!find(vec,r)){vec.push_back(r); i++;}
    } 

    return vec;
}

vector<vector<int>> gen_shuffling_transformation_mat(vector<int> randind_vec, int dimensions){
    vector<vector<int>> shuffling_matrix(dimensions, vector<int>(dimensions,0)); // initializing matrix

    for(int i=0; i<dimensions; i++) shuffling_matrix[randind_vec[i]][i] = 1;

    return shuffling_matrix;
}   

string substring(string str, int start, int end){
    string substr = "";

    for(int i=start-1; i < end; i++) substr += str[i];

    return substr; 
}

vector<string> string_sharding(string ptxt, int lps){
    // lps stands for "letters per segment".
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

string encrypt(string plaintext, vector<vector<int>> matrix){
    // shard the plaintext into peices
    vector<string> shards = string_sharding(plaintext,matrix.size()); 

    // shuffle the letters within the shards
    vector<string> shuffled_shards;
    for(auto i:shards) shuffled_shards.push_back(applying_transformation(matrix,i));

    // concatenate all shuffled shards to a single ciphered string
    string cipher_text = ""; for(auto i:shuffled_shards) cipher_text += i;
    return cipher_text;

}

// decrypting method

vector<vector<int>> transpose(vector<vector<int>> matrix){
    vector<vector<int>> transpose(matrix.size(),vector<int>(matrix.size(),0));

    for(int i=0; i<matrix.size(); i++) for(int j=0; j<matrix.size(); j++) transpose[i][j] = matrix[j][i];

    return transpose;
}

string decrypt(string ciphertext, vector<vector<int>> mat){
    // get the transpose of the matrix
    vector<vector<int>> transpose_mat = transpose(mat);

    for(int i=0; i<mat.size(); i++){for(auto i:transpose_mat[i]) cout << i << ' '; cout << endl;} cout << endl; 

    // break down the cipher text into apropriate segments
    vector<string> cipher_shards = string_sharding(ciphertext,mat.size());

    // apply transformation to individual cipher segments
    vector<string> plain_shards; for(auto i:cipher_shards) plain_shards.push_back(applying_transformation(transpose_mat,i));

    // concatenate all the transformed segments and return it
    string plaintext = ""; for(auto i:plain_shards) plaintext += i;

    
    return plaintext;
}


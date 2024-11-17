#include <iostream>
#include <string>
#include <vector>
using namespace std;

// encrypting method 

bool find(vector<int> vec, int search_key){
    for(auto i:vec) if(i == search_key) return true; 
    return false;
}

vector<int> gen_rand_indicies(int dimensions){
    vector<int> vec; srand(time(0));

    for(int i=0; i<dimensions; i++){
        int r = rand()%dimensions; 
        if(!find(vec,r)) vec.push_back(r); else i--;
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
    vector<string> shards; int itr = 0;
    if(ptxt.length()%lps != 0) itr++; itr += ptxt.length()/lps;
    
    for(int i=1; i <= itr; i++){
        string temp = substring(ptxt,lps*(i - 1) + 1,lps*i);
        shards.push_back(temp);
    } return shards;
}

void applying_transformation(vector<vector<int>> matrix, vector<int> vec){
    if(matrix[0].size() != vec.size()) return;
    
    vector<int> result(vec.size(),0);

    for(int i=0; i<vec.size(); i++) for(int j=0; j<vec.size(); j++) result[i] += matrix[i][j]*vec[j]; 

    cout << "- -" << endl;
    for(auto i:result) cout << '|' << i << '|' << endl;
    cout << "- -" << endl;
}



string applying_transformation(vector<vector<int>> mat, string str){
    string result = "";
    for(int i=0; i<mat.size(); i++){
        for(int j=0; j<mat.size(); j++) 
            if(mat[i][j]*(int(str[j])) != 0) result += char(mat[j][i]*(int(str[j])));
    } return result;
}   

 

// decrypting method

vector<vector<int>> inverse_matrix(vector<vector<int>> matrix){}

int main(){
    cout << "Shuffled identity matrix" << endl;
    vector<vector<int>> mat = gen_shuffling_transformation_mat(gen_rand_indicies(4),4);
    for(int i=0; i<mat.size(); i++){for(auto j:mat[i]) cout << j << ' '; cout << endl;} 
    /*
    */
   
    cout << "Sharding the plaint text" << endl;
    string str = "asdfewtdszdgsfgnhdjh"; // asdf ewtd szdg sfgn hdjh /0
    vector<string> sharding = string_sharding(str,4);
    for(auto i:sharding) cout << i << ' '; cout << endl;

    cout << "Applying transformation" << endl;
    string b = applying_transformation(mat,sharding[0]);
    cout << sharding[0] << ' ' << b ;
    // for(auto i:b) cout << i << ' '; cout << endl;

    // vector<int> vec = 
    // {
    // 4,
    // 2,
    // 5,
    // 1
    // };

    // applying_transformation(mat,vec);


    return 0;
}
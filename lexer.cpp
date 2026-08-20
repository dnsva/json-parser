#include "include/lexer.h"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>

namespace fs = std::filesystem;

/* MAIN IS FOR TESTING */
int main(){

    fs::path json_file_path = {"test.json"};

    //write json contents into json_string 
    ifstream json_file(json_file_path, ios::in | ios::binary); //double check if binary is needed

    const auto size_of_file = fs::file_size(json_file_path);
    string json_string(size_of_file, '\0');

    json_file.read(json_string.data(), size_of_file);


    //cout<<json_string<<"\n";

    string_view json_strview {json_string};

    cout<<json_strview<<"\n";

    vector<Token> tokenstream = get_token_stream(json_strview);

    cout<<"----------------------------------------------------\n";
    cout<<"(R, C)\t|\tToken\n";
    cout<<"----------------------------------------------------\n";
    for(auto t:tokenstream){
        cout<<"("<<t.location.row<<","<<t.location.col<<")\t|\t";
        cout<<t<<"\n";
    }
    cout<<"\n";
}
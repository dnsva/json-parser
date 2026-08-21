#include <iostream>
#include "../include/number_valid_checks.h"


using namespace std;

vector<char> str_to_vec_chars(string s){
    return {s.begin(), s.end()};
}

int main(){

    //valid:
    cout<<"VALID NUMBERS:\n";
    cout<<is_valid_number({'4','4','4'})<<"\n";
    cout<<is_valid_number(str_to_vec_chars("0"))<<"\n";
    cout<<is_valid_number(str_to_vec_chars("-0"))<<"\n";
    cout<<is_valid_number(str_to_vec_chars("123"))<<"\n";
    cout<<is_valid_number(str_to_vec_chars("-123"))<<"\n";
    cout<<is_valid_number(str_to_vec_chars("3.14"))<<"\n";
    cout<<is_valid_number(str_to_vec_chars("-3.14"))<<"\n";
    cout<<is_valid_number(str_to_vec_chars("0.5"))<<"\n";
    cout<<is_valid_number(str_to_vec_chars("1e+10"))<<"\n";
    cout<<is_valid_number(str_to_vec_chars("1E-10"))<<"\n";
    cout<<is_valid_number(str_to_vec_chars("0.3E+3"))<<"\n";
    cout<<is_valid_number(str_to_vec_chars("11111"))<<"\n";

    //invalid:
    cout<<"INVALID NUMBERS:\n";
    cout<<is_valid_number(str_to_vec_chars("01"))<<"\n";
    cout<<is_valid_number(str_to_vec_chars(".1"))<<"\n";
    cout<<is_valid_number(str_to_vec_chars("-01"))<<"\n";
    cout<<is_valid_number(str_to_vec_chars("+5"))<<"\n";
    cout<<is_valid_number(str_to_vec_chars("5."))<<"\n";
    cout<<is_valid_number(str_to_vec_chars("1E+"))<<"\n";
    cout<<is_valid_number(str_to_vec_chars("3e"))<<"\n";
    cout<<is_valid_number(str_to_vec_chars("--1"))<<"\n";
    cout<<is_valid_number(str_to_vec_chars("3ee9"))<<"\n";
    cout<<is_valid_number(str_to_vec_chars(""))<<"\n";
    cout<<is_valid_number(str_to_vec_chars("1.2.3"))<<"\n";
    cout<<is_valid_number(str_to_vec_chars("1..2"))<<"\n";
    cout<<is_valid_number(str_to_vec_chars("01.5"))<<"\n";


}
/*

planning/notes:

note to self: dont think of it as OOP. this isnt a tree like that

you just have one VALUE. and VALUE can be object, array, number, string, boolean, null type

store in variant 

return:
value of variant is string or array or object or whatever 
- could also output the json contents in the data structures

basically
json (a bunch of chars) -> data structures

VALUE (options)
array: [VALUE, VALUE, VALUE]
object: {"string": VALUE, "string": VALUE}
or just VALUE

how to store:

object - unordered_map<string, value>
array - vector of VALUES (this is legal)
number - double (evaluate the Es)
string - string
true/false - bool 
null - null_type (make an empty struct for this just to have the keyword)

*/

#include <iostream>
#include <variant>
#include <unordered_map>
#include <vector>

using namespace std;

//define a type for null:

struct NULL_TYPE{};

std::variant<unordered_map<string, VALUE>,vector<VALUE>, double, string, bool, NULL_TYPE> VALUE; 
#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include <unordered_set>
#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void wordleHelper(
    const std::string& in,
    const std::string& floating, // floating letters 
    const std::set<std::string>& dict,
    std::set<std::string>& answers, // set to store the results
    std::string curr_combo, // current combination we are making
    size_t pos, // position in the word that we are currently at
    const std::unordered_set<std::string>& prefixes
);


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    set<std::string> answers; // set to store the answers
    std::string curr_combo = ""; // string to build new words

    // filter dictionary based on length of word

    //std::set<std::string> filtered_dict;
    std::unordered_set<std::string> prefixes;
    for(const auto& word: dict){
        if(word.length() == in.length()){
          //filtered_dict.insert(word);
        
          for(size_t len = 1; len <= word.length(); ++len){
            prefixes.insert(word.substr(0,len));
        }
      }
    }

    

    // call helper function
    wordleHelper(in, floating, dict, answers, curr_combo, 0, prefixes);
    
    // return answers set
    return answers;

}

// Define any helper functions here
void wordleHelper(
    const std::string& in,
    const std::string& floating, // floating letters that can still be placed and will be continuously updated 
    const std::set<std::string>& dict,
    std::set<std::string>& answers, // set to store the results
    std::string curr_combo, // current combination we are making
    size_t pos, // position in the word that we are currently at
    const std::unordered_set<std::string>& prefixes
    )
{

    // we hit the base case if our position reaches the end of the word
    if(pos == in.size()){
        // check if the word is in the dictionary AND that the floating is empty
        if(dict.find(curr_combo) != dict.end() && floating.empty()){
            answers.insert(curr_combo);
        }
        return;
    }

    // // checking if the prefixes exist early on
    // bool prefix_exists = false;
    // for(const std::string& word : dict){
    //   if(word.length() == in.length()&& word.substr(0, pos) == curr_combo){
    //     prefix_exists = true;
    //     break;
    //   }
    // }

    // if(pos > 0 && !prefix_exists){
    //   return;
    //   // we do not need to keep checking
    // }

    if(prefixes.find(curr_combo) == prefixes.end() && pos > 0){
      return;
    }

    if(in.size() - pos < floating.size()){
      return;
    }

    // if the current character is a dash, we need to fill it
    if(in[pos] == '-'){
        
        for(size_t i = 0; i < floating.size(); i++){
            char floating_letter = floating[i];
            std::string updated_floating = floating;
            updated_floating.erase(i, 1);
            wordleHelper(in, updated_floating, dict, answers, curr_combo + floating_letter, pos +1, prefixes );
        }
        // iterate through a to z
        for (char letter = 'a'; letter <= 'z'; letter++){
            size_t pos_floating = floating.find(letter);
            if(pos_floating == std::string::npos){ 
                wordleHelper(in, floating, dict, answers, curr_combo+letter, pos +1, prefixes);
            }
        }
        
    }
    // if the current character is already fixed, use it and move on
    else{
        curr_combo = curr_combo + in[pos];
        wordleHelper(in, floating, dict, answers, curr_combo, pos+1, prefixes);
    }
}


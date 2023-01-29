#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>
#include<bits/stdc++.h>

using namespace std;

vector<string> tokenize(const string& filename){
  ifstream file(filename);
  vector<string> tokens;
  string line;
  while(getline(file, line)){
    stringstream lineStream(line);
    string token;
    while (lineStream >> token){
      transform(token.begin(), token.end(), token.begin(), ::tolower);
      tokens.push_back(token);
    }
  }
  return tokens;
}

int levenshteinDistance(const std::string& s1, const std::string& s2) {
  // Create a table to store results of sub-problems
  int dp[s1.size() + 1][s2.size() + 1];

  // Initialize the distance for empty strings
  for (int i = 0; i <= s1.size(); i++) {
    dp[i][0] = i;
  }
  for (int j = 0; j <= s2.size(); j++) {
    dp[0][j] = j;
  }

  // Fill the table
  for (int i = 1; i <= s1.size(); i++) {
    for (int j = 1; j <= s2.size(); j++) {
      if (s1[i - 1] == s2[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1];
      } else {
        dp[i][j] = std::min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]}) + 1;
      }
    }
  }

  // Return the distance
  return dp[s1.size()][s2.size()];
}


/**
 * Reads a file line by line and inserts each line into a hash table
 * 
 * @param filename the name of the file to read
 * @param dictionary a hash table that contains all the words in the dictionary
 */
void readDictionary(const string& filename, unordered_set<string>& dictionary){
  ifstream file(filename);
  string line;
  while(getline(file, line)){
    dictionary.insert(line);
  }
}


/**
 * The function takes in a vector of strings, an unordered set of strings, and a vector of strings. It
 * uses a queue and a stack to check each word in the tokens vector agaisnt the words in the dictionary.
 * If the word is not found in the dictionary, it is added to the misspelled vector. After all words have been checked, 
 * the words in the tokens vector are added by popping them off the stack and pushing them back onto the queue.
 * 
 * @param tokens a vector of strings, each string is a word from the text
 * @param dictionary a set of words that are spelled correctly
 * @param misspelled a vector of strings that will contain the misspelled words
 */
void checkWords(vector<string> tokens, unordered_set<string> dictionary, vector<string>& misspelled){
  queue<string> q;
  stack<string> s;
  for(int i = 0; i < tokens.size(); i++){
    q.push(tokens[i]);
  }
  while(!q.empty()){
    string word = q.front();
    q.pop();
    s.push(word);
    if(dictionary.find(word) == dictionary.end()){
      misspelled.push_back(word);
    }
  }
  while(!s.empty()){
    string word = s.top();
    s.pop();
    q.push(word);
  }
}

/**
 * For each misspelled word, find the closest word in the dictionary
 * 
 * @param misspelled a vector of strings that are misspelled
 * @param dictionary a set of words that are in the dictionary
 * @param closest a vector of strings that will be take in the closest words to the misspelled
 * words
 */
void findClosest(vector<string> misspelled, unordered_set<string> dictionary, vector<string>& closest){
  for(int i = 0; i < misspelled.size(); i++){
    int min = 100000;
    string closestWord;
    for(auto it = dictionary.begin(); it != dictionary.end(); it++){
      int dist = levenshteinDistance(misspelled[i], *it);
      if(dist < min){
        min = dist;
        closestWord = *it;
      }
    }
    closest.push_back(closestWord);
  }
}


/**
 * It takes a vector of strings and a stack of strings as parameters and asks the user if they meant
 * any of the strings in the vector. If they did, it pushes the string onto the stack
 * 
 * @param closest a vector of strings that contains the closest words to the misspelled word
 * @param final the stack that will hold the final word
 */
void selectWord(vector<string> closest, stack<string>& final){
  for(int i = 0; i < closest.size(); i++){
    cout << "Did you mean " << closest[i] << "?" << endl;
    cout << "1. Yes" << endl;
    cout << "2. No" << endl;
    cout << "3. None of the above" << endl;
    int choice;
    cin >> choice;
    if(choice == 1){
      final.push(closest[i]);
    }
    else if(choice == 2){
      final.push(closest[i]);
    }
    else if(choice == 3){
      final.push(closest[i]);
    }
  }
}

/**
 * This function takes a stack of strings and a filename and writes the strings in the stack to the
 * file
 * 
 * @param final the stack that contains the final output
 * @param filename the name of the file to be read
 */
void writeToFile(stack<string> final, const string& filename){
  ofstream file(filename);
  while(!final.empty()){
    string word = final.top();
    final.pop();
    file << word << " ";
  }
}

int main(){
  unordered_set<string> dictionary;

  readDictionary("dict.txt", dictionary);

  vector<string> tokens = tokenize("test.txt");

  vector<string> misspelled;

  checkWords(tokens, dictionary, misspelled);
  
  vector<string> closest;
  
  findClosest(misspelled, dictionary, closest);

//     for(int i = 0; i < misspelled.size(); i++){
//         cout << misspelled[i] << " " << closest[i] << endl;
//     }

    for(int i = 0; i < misspelled.size(); i++){
        cout << misspelled[i] << endl;
    }

  stack<string> final;
  selectWord(closest, final);
  
  writeToFile(final, "final.txt");
  
  return 0;
}
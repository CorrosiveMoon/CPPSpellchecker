#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>
#include<bits/stdc++.h>

using namespace std;

vector<string> tokenize(const string& filename) {
  ifstream file(filename);
  vector<string> tokens;
  string line;
  
  while (getline(file, line)) {
    stringstream lineStream(line);
    string token;
    while (lineStream >> token) {
      // Transform the token to lower case
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

//function that reads correct words from dict.txt and stores it in a hash table
void readDictionary(const string& filename, unordered_set<string>& dictionary){
  ifstream file(filename);
  string line;
  while (getline(file, line)){
    stringstream lineStream(line);
    string token;
    while (lineStream >> token){
      dictionary.insert(token);
    }
  }
}


void printDictionary(const unordered_set<string>& dictionary){
  for (const string& word : dictionary){
    cout << word << endl;
  }
}

void spellCheck(const string& filename, const unordered_set<string>& dictionary){
  ifstream file(filename);
  string line;
  while (getline(file, line)){
    stringstream lineStream(line);
    string token;
    while (lineStream >> token) {
      if (dictionary.find(token) == dictionary.end()){
        cout << token << " is misspelled" << endl;
        int minDistance = 1000000;
        string closestWord;
        for (const string& word : dictionary){
          int distance = levenshteinDistance(token, word);
          if (distance < minDistance){
            minDistance = distance;
            closestWord = word;
          }
        }
        cout << "Did you mean " << closestWord << "?" << endl;
      }
    }
  }
}


int main(){
  // vector<string> tokens = tokenize("t.txt");
  // for (const string& token : tokens) {
  //   cout << token << endl;
  // }
  // int distance = levenshteinDistance("kitten", "sitting");
  // cout << distance << endl;
  unordered_set<string> dictionary;
  readDictionary("dict.txt", dictionary);
  // spellCheckWrong("text.txt", dictionary);
  printDictionary(dictionary);
  // spellCheck("test.txt", dictionary);

  return 0;
}

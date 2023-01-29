# CPPSpellchecker
A Simple spellchecker written in C++ using the Levenshtein Algorithm and implementing ideas learnt during the data structures course.

# Description

This programme reads a text file and uses a dictionary stored in a hash table to check the spelling of the words in the file. If a word is misspelt, the Levenshtein distance algorithm will suggest corrections. The user will be able to choose between the suggested corrections and the original word. After that, the programme will reconstruct the original text with the corrected words and output the result.

# Usage
Compile the source code and run the executable with the text file name.

# Dependencies

 - C++ Standard Library
 - string for string manipulation
 - iostream for input/output
 - algorithm to use the transform function in the tokenize() function
 - sstream for string stream manipulation
 - fstream for file manipulation, including input/output for files
 - vector for dyanmic arrays
 

# Files Used

 - Spellchecker.cpp is the source code for the spell checking program.
 - dict.txt is the file containing all the correctly spelled words.
 
## Side Notes
 - Program converts all the strings/sentecnes in the file to lowercase before checking them against the dict.txt file.
 - dict.txt should be in the same directory as the source code for the program to run. 
 - Program uses the Levenshtein distance algorithm to find the closest words in the dictionary.

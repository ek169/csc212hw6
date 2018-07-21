#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <ctime>
#include "bst.h"
#include <string.h>
//  add any other needed include files..

int loadDictionaryArray(std::string * dictArray, std::string fileName)
{
  std::string line;
  std::string word;
  std::ifstream infile(fileName);
  int total = 0;
  while(std::getline(infile, line))
  {
      std::istringstream iss(line);
      while(iss >> word)
      {
          word.erase(std::remove_if (word.begin(), word.end(), ispunct), word.end());
          std::transform(word.begin(), word.end(), word.begin(), ::tolower);
          dictArray[total] = word;
          total++;
      }
  }
  return total;
}

// added in binary search to make it run faster
bool binSearch(std::string * dict, std::string word, int lo, int hi)
{
  if(lo <= hi)
  {
    int mid = (hi+lo)/2;
    int result = strcmp(word.c_str(), dict[mid].c_str());
    if(result == 0) return true;
    if(result > 0) return binSearch(dict, word, mid+1, hi);
    if(result < 0) return binSearch(dict, word, lo, mid-1);

  }
  return false;
}

// check file is used to drive the whole program
// it checks if the words are in the dictionaries and inserts them into
// instances of BSTree classes if they are not
void checkFile(BSTree * newFile, std::string * dict1, int dict1size, std::string * dict2, \
   int dict2size, std::string response, std::string s1, std::string s2)
{

  int file_size = newFile->get_size();
  BSTree wordsNotInDict1;
  BSTree wordsNotInDict2;

  std::string next_word;
  int n;
  int in_range_query = 0;
  std::string line;
  std::string word;
  std::ifstream infile(response);
  while(std::getline(infile, line))
  {
      std::istringstream iss(line);
      while(iss >> word)
      {
          word.erase(std::remove_if (word.begin(), word.end(), ispunct), word.end());
          std::transform(word.begin(), word.end(), word.begin(), ::tolower);
          if(word != "")
          {
            if((strcmp(word.c_str(), s1.c_str()) >= 0) && \
             (strcmp(word.c_str(), s2.c_str()) <= 0))
            {
              if(!newFile->containsWord(word)) in_range_query++;
            }
            newFile->insert(word);

            if(!binSearch(dict1, word, 0, dict1size))
            {
              wordsNotInDict1.insert(word);
            }
            if(!binSearch(dict2, word, 0, dict2size))
            {
              wordsNotInDict2.insert(word);
            }
          }
      }
  }

  std::cout << response << std::endl;
  std::cout << wordsNotInDict1.get_uniques() << ": ";
  wordsNotInDict1.print_list();
  std::cout << std::endl;
  std::cout << wordsNotInDict2.get_uniques() << ": ";
  wordsNotInDict2.print_list();
  std::cout << std::endl;
  std::cout << newFile->get_size() << " total words" << std::endl;
  std::cout << newFile->get_uniques() << " unique words" << std::endl;
  std::cout << in_range_query << std::endl;

  // for range query
  if((s1.size() > 0) && (s2.size()))
  {
    newFile->print_range(s1, s2);
  }
}

int main(int argc, const char * argv[]) {

    // initialize main tree and range query strings
    BSTree * newFile = new BSTree;
    std::string s1;
    std::string s2;

    // initialize variables for dictionary 1
    int wc1 = 0;
    std::string wrds;
    std::ifstream dc1("dictionary.txt");

    // get count of words in dictionary 1
    for (; dc1 >> wrds; ++wc1);
    std::string * dictionaryArr1 = new std::string[wc1];

    // fill array with strings from dictionary 1
    loadDictionaryArray(dictionaryArr1, "dictionary.txt");
    std::sort(dictionaryArr1, dictionaryArr1+wc1);

    // initialize variables for dictionary 2
    int wc2 = 0;
    std::ifstream dc2("dictionary-brit.txt");

    // get count of words in dictionary 2
    for (; dc2 >> wrds; ++wc2);
    std::string * dictionaryArr2 = new std::string[wc2];

    // fill array with strings from dictionary 2
    loadDictionaryArray(dictionaryArr2, "dictionary-brit.txt");
    std::sort(dictionaryArr2, dictionaryArr2+wc2);
  // enter while loop to get user input
  std::string response;
  while(1)
  {
    std::cout << "Enter a name of a text file, or return to exit" \
     << std::endl;
    std::cin >> response;
    if(response.size())
    {
        std::cout << "Enter two words to perform a range query:" << std::endl;
        std::cin >> s1;
        std::cin >> s2;
        checkFile(newFile, dictionaryArr1, wc1, dictionaryArr2, wc2, response, s1, s2);
        break;
    }
    else
    {
      break;
    }
  }
  delete[] dictionaryArr1;
  delete[] dictionaryArr2;
  delete newFile;
  return 0;
}

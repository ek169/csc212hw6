#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <ctime>
#include "bst.h"
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


void checkFile(BSTree * newFile, std::string * dict1, int dict1size, std::string * dict2, \
   int dict2size, std::string response)
{

  int file_size = newFile->get_size();
  BSTree wordsNotInDict1;
  BSTree wordsNotInDict2;

  std::string next_word;
  int n;
  int w = 0;
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
            newFile->insert(word);
            w = 0;
            bool is_in_dict1 = false;
            bool is_in_dict2 = false;
            while(1)
            {
              if(w < dict1size || w < dict2size)
              {

                if(w < dict1size)
                {
                  //std::cout << "dict1 wrd: " << dict1[w] << std::endl;

                  if(dict1[w].compare(word) == 0)
                  {
                    is_in_dict1 = true;
                  }
                  else if(w == (dict1size - 1) && !is_in_dict1)
                  {
                    std::cout << "word is: " << word << " not in dict1" << std::endl;
                    wordsNotInDict1.insert(word);
                  }
                }
                if(w < dict2size)
                {
                  //std::cout << "dict2 wrd: " << dict2[w] << std::endl;

                  if(dict2[w].compare(word) == 0)
                  {
                    is_in_dict2 = true;
                  }
                  else if(w == (dict2size - 1) && !is_in_dict2)
                  {
                    std::cout << "word is: " << word << " not in dict2" << std::endl;
                    wordsNotInDict2.insert(word);
                  }
                }
              }
              else
              {
                break;
              }
              w++;
            }
      }
  }



  std::cout << "~ Words Not In Dictionary 1 ~" << std::endl;
  wordsNotInDict1.print_tree();
  std::cout << std::endl;
  std::cout << "~ Words Not In Dictionary 2 ~" << std::endl;
  wordsNotInDict2.print_tree();
  std::cout << std::endl;

  //newFile->print_tree();
  delete newFile;
}

int main(int argc, const char * argv[]) {

    // declare your data structures here
    int wordCount1 = 0;
    BSTree * newFile = new BSTree;
    std::string li1;
    std::ifstream dc1("dictionary.txt");
    while (std::getline(dc1, li1))
        ++wordCount1;
    std::string * dictionaryArr1 = new std::string[wordCount1];

    std::cout << "size dic1: " << \
    loadDictionaryArray(dictionaryArr1, "dictionary.txt") \
    << std::endl;

    int wordCount2 = 0;
    std::string li2;
    std::ifstream dc2("dictionary-brit.txt");
    while (std::getline(dc2, li2))
        ++wordCount2;
    std::string * dictionaryArr2 = new std::string[wordCount2];


    std::cout << "size dic2: " << \
    loadDictionaryArray(dictionaryArr2, "dictionary-brit.txt") \
     << std::endl;

  // enter while loop
  std::string response;
  while(1)
  {
    std::cout << "Enter a name of a text file 'xyz.txt', or enter nothing to exit" \
     << std::endl;
    std::cin >> response;
    if(response.size())
    {
        checkFile(newFile, dictionaryArr1, wordCount1, dictionaryArr2, wordCount2, response);
    }
    else
    {
      break;
    }
  }


/*
// for range query
    std::string s1;
    std::string s2;

    if(argv[2] && argv[3])
    {
      s1 = argv[2];
      s2 = argv[3];
    }

    myTree.print_list(1);
    std::cout << "~~~~~~~~~~~~~~~~~~~" << std::endl;
    if((s1.size() > 0) && (s2.size()))
    {
      myTree.print_range(s1, s2);
    }
    myTree.print_tree();*/

    return 0;
}

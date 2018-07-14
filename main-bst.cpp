#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <ctime>
#include "bst.h"
//  add any other needed include files..

int main(int argc, const char * argv[]) {

    // declare your data structures here
    BSTree myTree;


// Here is an idea of how to get started -- You *may* want to use it..
    std::ifstream infile(argv[1]);
    std::string s1;
    std::string s2;

    if(argv[2] && argv[3])
    {
      s1 = argv[2];
      s2 = argv[3];
    }
    std::string line;
    std::string word;

    while(std::getline(infile, line))
    {
        std::istringstream iss(line);
        while(iss >> word)
        {
            word.erase(std::remove_if (word.begin(), word.end(), ispunct), word.end());
            std::transform(word.begin(), word.end(), word.begin(), ::tolower);
            myTree.insert(word);
        }
    }
    myTree.print_list(1);
    std::cout << "~~~~~~~~~~~~~~~~~~~" << std::endl;
    if((s1.size() > 0) && (s2.size()))
    {
      myTree.print_range(s1, s2);
    }
    myTree.print_tree();

    return 0;
}

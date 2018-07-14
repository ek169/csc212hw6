#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <ctime>
//  add any other needed include files..

int main(int argc, const char * argv[]) {

    // declare your data structures here
//    BSTree myTree;


// Here is an idea of how to get started -- You *may* want to use it..
    std::ifstream infile(argv[1]);

    std::string line;
    std::string word;


    while(std::getline(infile, line))
    {
        std::istringstream iss(line);
        while(iss >> word)
        {
            word.erase(std::remove_if (word.begin(), word.end(), ispunct), word.end());
            std::transform(word.begin(), word.end(), word.begin(), ::tolower);



        }
    }

    return 0;
}

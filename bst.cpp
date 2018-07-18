#include "bst.h"
#include <iostream>
#include <string>

// constructor which initializes root to null, size and unique_words to zero
BSTree::BSTree()
{
    root = NULL;
    size = 0;
    unique_words = 0;
}

BSTree::~BSTree()
{
  destroy(root);
}

// destroys each node in the tree recursively
void BSTree::destroy(BSTNode* b)
{
  if(b != 0)
  {
    destroy(b->left);
    destroy(b->right);
    delete b;
  }
}

// compares two words to see if one contains a letter that is greater
// in ascii value than the other, and returns and integer that will
// allow other functions to make decisions
int BSTree::checkWords(std::string s, std::string w)
{
  int i = 0;
  while(1)
  {
    if(s[i] == '\0' && w[i] == '\0')
    {
      return 0;
    }
    if(s[i] < w[i])
    {
      return 1;
    }
    if(s[i] > w[i])
    {
      return -1;
    }
    i++;
  }

}

// finds the closest node to whatever word was inputted to the function
BSTNode * BSTree::find(BSTNode *r, std::string w)
{
  int comparisonResults;
  comparisonResults = checkWords(r->data, w);
  switch(comparisonResults)
  {
    case 0:
      return r;
    case 1:
      if(r->right == 0) return r;
      return find(r->right, w);
    case -1:
      if(r->left == 0) return r;
      return find(r->left, w);
    default:
      return r;
  }

}

// increments the frequency data member of the BSTNode pointer passed in
void BSTree::increment_frequency(BSTNode *ptr)
{
  if(ptr != 0)
  {
    ptr->frequency += 1;
  }
}

// inserts a new node or increments frequency of an existing node
// based on the return value of find()
void BSTree::insert(BSTNode ** currentNode, std::string newStr)
{
  //std::cout << "size in insert is: " << size << " for str: " << newStr << std::endl;
  if(root == 0)
  {
    BSTNode *rootNode = new BSTNode(newStr);
    root = rootNode;
    size = 1;
    unique_words = 1;
    return;
  }

  BSTNode * existingNode = find(*currentNode, newStr);
  // performs one final check with checkWords to see if the last node's
  // data is equal to newStr or if a new node should be added
  int finalComparison = checkWords(existingNode->data, newStr);
  switch(finalComparison)
  {
    BSTNode *addedNode;
    case 0:
      increment_frequency(existingNode);
      size++;
      break;
    case 1:
      addedNode = new BSTNode(newStr);
      existingNode->right = addedNode;
      size++;
      unique_words++;
      break;
    case -1:
      addedNode = new BSTNode(newStr);
      existingNode->left = addedNode;
      size++;
      unique_words++;
      break;
    default:
      break;
  }

}

// prints a certain number of nodes in the tree below the initial node passed in
void BSTree::print_list(BSTNode* currentNode, int n)
{
  if(n > 0)
  {
    if(currentNode)
    {
      std::cout << currentNode->data << " : " << currentNode->frequency << std::endl;
      if(currentNode->left)
      {
        print_list(currentNode->left, --n);
      }
      if(currentNode->right)
      {
        print_list(currentNode->right, --n);
      }
    }
    else
    {
      return;
    }
  }
}

// uses checkWords() to find the words in the already existing binary tree
// which are between the startWord and endWord, and then prints those words
// out and then searches the current nodes branches dependent on the return of
// checkWords
void BSTree::print_range(std::string startWord, std::string endWord, BSTNode* currentNode)
{
  if(currentNode)
  {
    int startVsData = checkWords(startWord, currentNode->data);

    // startVsData && endVsData are assigned a value -1, 0, or 1,
    // which determines if the current node is within the range of start and end words
    int endVsData = checkWords(currentNode->data, endWord);
    if(startVsData >= 0 && endVsData >= 0)
    {
      print_range(startWord, endWord, currentNode->left);
      print_list(currentNode, 1);
      print_range(startWord, endWord, currentNode->right);
    }
    else if(endVsData >= 0)
    {
      print_range(startWord, endWord, currentNode->right);
    }
    else if(startVsData >= 0)
    {
      print_range(startWord, endWord, currentNode->left);
    }
  }
}


// public functions, mostly just call the private member functions which
// modify the private data members

void BSTree::insert(std::string str)
{
  BSTNode ** rootPtr = &root;
  insert(rootPtr, str);
}

void BSTree::print_list(int n)
{
  print_list(root, size);
  return;
}


void BSTree::print_tree()
{
  print_list(size);
}

void BSTree::print_tree_details()
{
  // prints details of tree
  std::cout << size << " total words" << std::endl;
  std::cout << unique_words << " unique words" << std::endl;
  return;
}

void BSTree::print_range(std::string startWord, std::string endWord)
{
  print_range(startWord, endWord, root);
  return;
}


// takes in a string and sees if there is a node with that string as its data
bool BSTree::containsWord(std::string w)
{
  BSTNode * n = find(root, w);
  if(n->data == w)
  {
    return true;
  }
  return false;
}

// takes in an integer and utilizes the private findWordAtNode function

int BSTree::get_size()
{
  return size;
}

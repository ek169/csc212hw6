#include "bst.h"
#include <iostream>
#include <string>
#include <string.h>

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

// finds the closest node to whatever word was inputted to the function
BSTNode * BSTree::find(BSTNode *r, std::string w)
{
  // determines whether to check left or right based off of strcmp
  int result = strcmp(w.c_str(), r->data.c_str());
  if(result == 0) return r;

  if(result > 0)
  {
    if(r->right == 0) return r;
    return find(r->right, w);
  }

  if(result < 0)
  {
    if(r->left == 0) return r;
    return find(r->left, w);
  }
  return r;

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
  if(root == 0)
  {
    BSTNode *rootNode = new BSTNode(newStr);
    root = rootNode;
    size = 1;
    unique_words = 1;
    return;
  }

  BSTNode * existingNode = find(*currentNode, newStr);

  // performs one final check with strcmp to see if the last node's
  // data is equal to newStr or if a new node should be added
  int result = strcmp(newStr.c_str(), existingNode->data.c_str());
  BSTNode *addedNode;
  if(result == 0)
  {
    increment_frequency(existingNode);
    ++size;
  }
  else if(result > 0)
  {
    addedNode = new BSTNode(newStr);
    existingNode->right = addedNode;
    ++size;
    ++unique_words;
  }
  else if(result < 0)
  {
    addedNode = new BSTNode(newStr);
    existingNode->left = addedNode;
    ++size;
    ++unique_words;
  }
  return;
}

// prints a certain number of nodes in the tree below the initial node passed in
void BSTree::print_list(BSTNode* currentNode, int* n, bool full_printout=true)
{
  if(*n > 0)
  {
    if(currentNode)
    {
      if(full_printout)
      std::cout << currentNode->data << " : " << currentNode->frequency << std::endl;
      else
      {
        std::cout << currentNode->data;
        if(*n != 1) std::cout << ",";
      }

      if(currentNode->left)
      {
        (*n)--;
        print_list(currentNode->left, n, full_printout);
      }
      if(currentNode->right)
      {
        (*n)--;
        print_list(currentNode->right, n, full_printout);
      }
    }
    else
    {
      return;
    }
  }
}


// uses strcmp to find the words in the already existing binary tree
// which are between the startWord and endWord, and then prints those words
// out and then searches the current nodes branches dependent on the return of
// strcmp
void BSTree::print_range(std::string startWord, std::string endWord, BSTNode* currentNode)
{
  if(currentNode)
  {
    int one = 1;
    // startVsData && endVsData are assigned a value < 0, > 0, or 0, this helps
    // determine if the current node is within the range of start and end words
    int startVsData = strcmp(currentNode->data.c_str(), startWord.c_str());
    int endVsData = strcmp(currentNode->data.c_str(), endWord.c_str());
    if(startVsData >= 0 && endVsData <= 0)
    {
      print_range(startWord, endWord, currentNode->left);
      print_list(currentNode, &one);
      print_range(startWord, endWord, currentNode->right);
    }
    else if(endVsData <= 0)
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

void BSTree::print_list()
{
  int n = unique_words;
  print_list(root, &n, false);
  return;
}

void BSTree::print_list(int n)
{
  print_list(root, &n, false);
  return;
}


void BSTree::print_tree()
{
  int n = unique_words;
  print_list(root, &n);
}

void BSTree::print_range(std::string startWord, std::string endWord)
{
  print_range(startWord, endWord, root);
  return;
}

// returns the number of inserts that have been called for the tree
int BSTree::get_size()
{
  return size;
}

// returns the number of nodes that are in the tree
int BSTree::get_uniques()
{
  return unique_words;
}

// checks if the word exists in the BSTree
bool BSTree::containsWord(std::string theStr)
{
  BSTNode * node = find(root, theStr);
  if(strcmp(node->data.c_str(), theStr.c_str()) == 0) return true;
  return false;
}

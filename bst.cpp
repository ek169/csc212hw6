#include "bst.h"
#include <iostream>

// constructor which initializes root to null, size and unique_words to zero
BSTree::BSTree()
{
    root = NULL;
    size = 0;
    unique_words = 0;
}

// destroys each node in the tree recursively
void BSTree::destroy(BSTNode* b)
{
  if(b != 0)
  {
    destory(b->left);
    destroy(b->right)
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
    case 2:
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

// inserts a new 
void BSTree::insert(BSTNode *currentNode, std::string newStr)
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
  int finalComparison = checkWords(existingNode->data, newStr);
  switch(finalComparison)
  {
    case 0:
      increment_frequency(existingNode);
      break;
    case 1:
      BSTNode *rightNode = new BSTNode(newStr);
      existingNode->right = rightNode;
      break;
    case 2:
      BSTNode *leftNode = new BSTNode(newStr);
      existingNode->left = leftNode;
      break;
    default:
      break;
  }

}

void print_list(BSTNode* currentNode, int n)
{
  if(n > 0)
  {
    if(startNode)
    {
      cout << currentNode->data << " : " << currentNode->frequency << endl;
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

void print_range(std::string startWord, std::string endWord, BSTNode* currentNode)
{
  if(currentNode)
  {
    int startVsData = checkWords(currentNode->data, startWord);
    int endVsData = checkWords(currentNode->data, endWord);
    if(startVsData <= endVsData)
    {
      print_range(startWord, endWord, currentNode->left);
      print_list(currentNode, 1);
      print_range(startWord, endWord, currentNode->right);
    }
    else if(endVsData == -1)
    {
      print_range(startWord, endWord, currentNode->right);
    }
    else if(startVsData == 1)
    {
      print_range(startWord, endWord, currentNode->left);
    }
  }
}

// public functions

void BSTree::insert(std::string str)
{
  insert(root, str);
}

void print_list(int n)
{
  print_list(root, n);
  return;
}

void print_tree(int n)
{
  print_list(root, size);
  return;
}

void print_range(std::string startWord, std::string endWord)
{
  BSTNode * closestNode = find(root, startWord);
  print_range(startWord, endWord, closestNode);
  return;
}

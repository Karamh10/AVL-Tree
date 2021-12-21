#include <iostream>
#include <string>
#include "AVLTree.h"
#include <iomanip>
#include <queue>
using namespace std;

AVLTree::AVLTree()
{
    root = nullptr;
}

AVLTree::~AVLTree()
{

}

AVLNode* AVLTree::getRoot()
{
    return root;
}


// search value ss in the AVL tree
bool AVLTree::find(string ss)
{
    if (root == nullptr)
    {
        return false;
    }

    AVLNode* node = root;

    while (node != nullptr)
    {
        if (ss.compare(node->ssn) == 0)
        {
            return true;
        }
        if (ss.compare(node->ssn) < 0)
        {
            node = node->left;
        }
        else
        {
            node = node->right;
        }
    }
    return false;
}

// return the height of the subtree rooted at node
// if subtree is empty, height is -1
// if subtree has one node, height is 0
int AVLTree::height(AVLNode* node)
{

    if(node != nullptr)
    {
        return node->height;
    }
    else
    {
        return -1;
    }
}

// return the balance factor of the node
int AVLTree::balanceFactor(AVLNode* node)
{
    return height(node->left) - height(node->right);
}

// update the height of the node
// this should be done whenever the tree is modified
void AVLTree::updateHeight(AVLNode* node)
{
    int hl = height(node->left);
    int hr = height(node->right);
    node->height = (hl>hr ? hl : hr) + 1;
}


// rotate right the subtree rooted at node
// return the new root of the subtree
AVLNode* AVLTree::rotateRight(AVLNode* node)
{
    AVLNode* lp = node->left;      // left child of node
    if (node->parent!=nullptr)
        {
             // node is not root
        if (node->parent->left == node)
        { // node is a left child
            node->parent->left = lp;
        }

        else
        {
            node->parent->right = lp;     // node is a right child
        }
    }

    if (lp->right != nullptr)
    {           // pointer update
        lp->right->parent = node;
    }

    lp->parent = node->parent;
    node->left = lp->right;
    lp->right = node;
    node->parent = lp;
    updateHeight(node);                   // after rotation, update height
    updateHeight(lp);                     // after rotation, update height
    if (node == root)
    {
        root = lp;
    }
    return lp; // lp is the new root of the subtree
}


// rotate left the subtree rooted at node
// return the new root of the subtree
AVLNode* AVLTree::rotateLeft(AVLNode* node)
{
    AVLNode* rp = node->right;
    if (node->parent!=nullptr)
    {

        if (node->parent->left == node)
        {
            node->parent->left = rp;
        }

        else
        {
            node->parent->right = rp;
        }
    }

    if (rp->left != nullptr)
    {
       rp->left->parent = node;
    }

    rp->parent = node->parent;

    node->right = rp->left;
    rp->left = node;
    node->parent = rp;
    node->parent = rp;
    updateHeight(node);
    updateHeight(rp);
    if (node == root)
    {
        root = rp;
    }
    return rp;
}


// rebalance a tree rooted at node
// return the new root of the subtree
AVLNode* AVLTree::balance(AVLNode* node)
{
    updateHeight(node);
    if (balanceFactor(node) == 2)
    {

        if (balanceFactor(node->left) < 0)
        {
            node->left = rotateLeft(node->left); // for left right case
        }

        AVLNode* temp = rotateRight(node);
        updateHeight(temp);
        return temp;
    }

    if (balanceFactor(node) == -2)
    {

        if (balanceFactor(node->right) > 0)
        {
            node->right = rotateRight(node->right);  // for right left case
        }
        AVLNode* temp2 = rotateLeft(node);
        updateHeight(temp2);
        return temp2;
    }
    return node;
}

// insert a new node with (ss, na) to the AVL tree
// if there exists ss value, return false
// otherwise, insert it, balance the tree, return true
bool AVLTree::insert(string ss, string na) { //IMPLEMENT THIS
  
  if(find(ss) == true) //If an ssn is already present in the tree, then false is returned.
      return false;
	  
  AVLNode * node = root; //Created 2 new AVLNode pointers called node and newNode.
  AVLNode * newNode = new AVLNode(ss, na); 
  
  newNode->ssn = ss; //Inputs the proper information into newNode.
  newNode->name = na;
  newNode->left = nullptr;
  newNode->right = nullptr;
  newNode->parent = nullptr;

  if(root == nullptr) {
    root = newNode;
    return true; //If root is null, then set root equal to newNode and return true.
  }

  while(true) { //While loop that runs while the function is true.
    if(ss.compare(node->ssn) < 0) { //If ss is less than the node ssn go to left side and check for ssn's less than the root node.
      if(node->left == nullptr) { //If statement that runs when the left side of the node is empty. 
        node->left = newNode;
        newNode->parent = node; //Insert newNode and change the parent node.
        break;
      }
      node = node->left; //Set node equal to the left of node. 
    }
    else { //Else statment that runs if ss is NOT less than the node ssn
      if(node->right == nullptr) { //If statement that runs when the right side of the node is empty. 
        node->right = newNode;
        newNode->parent = node; //Insert newNode and change the parent node.
        break;
      }
      node = node->right; //Set node equal to the right of node. 
    }
  }
  
  while(newNode != nullptr) { //While statment that goes throught the AVL tree (runs while newNode is not null). 
    balance(newNode); //Balance the tree.
    newNode = newNode->parent; //Set newNode equal to the parent of newNode.
  }
  return true; //Return true.
}

AVLNode* AVLTree::maxOfSubtree(AVLNode* node)
{
    if (node == nullptr)
    {
        return nullptr;
    }
    while (node->right != nullptr)
    {
        node = node->right;
    }
    return node;
}

// delete the node containing value ss
// if there is not such node, return false
// otherwise, delete the node, balance the tree, return true
bool AVLTree::deleteNode(string ss) { //IMPLEMENT THIS
  
  if(root == nullptr)
    return false; //Returns false if the tree is empty. 
  
  AVLNode * tmp = root; //Created a new AVLNode pointer called tmp and set it equal to root.

  while(true) { //While loop that runs while the function is true. Will locate the node that needs to be deleted.
    if(tmp == nullptr)
      return false; //If tmp is null, return false.
    if(ss.compare(tmp->ssn) == 0)
      break; //If ss and the ssn of tmp are equal, break the function.
    if(ss.compare(tmp->ssn) < 0) 
      tmp = tmp->left; //If ss is less than ssn of tmp, set tmp equal to left of tmp.
    else
      tmp = tmp->right; //If ss is greater than ssn of tmp, set tmp equal to right of tmp.
  }

  AVLNode * parentNode = tmp->parent; //Created four new AVLNode pointers which will be used during the deletion process.
  AVLNode * max = nullptr;
  AVLNode * nextNode = nullptr;
  AVLNode * actionPos = nullptr;

    
  if((tmp->left == nullptr) && (tmp->right == nullptr)) { //OPTION 1: The node is a leaf.
    if(root == tmp) { //If statement that runs when root equals tmp. 
      root = nullptr;
      delete tmp; //Deletes tmp.
      return true;
    }
    tmp->parent = nullptr; //Set parent of tmp equal to null.

    if(parentNode->left == tmp)
      parentNode->left = nullptr; //If the left of parentNode is tmp, then set left of parent node equal to null.
    else
        parentNode->right = nullptr; //If else statement is ran, set right of parentNode equal to null.
    delete tmp; //Delete tmp
    actionPos = parentNode; //Set actionPos equal to parentNode.
  }

  else { //Option 2: Node HAS CHILDREN.
    if((tmp->left == nullptr) || (tmp->right == nullptr)) { //Suboption 1: Node has ONE CHILD. 
      if(tmp->left == nullptr)
        nextNode = tmp->right; //If left of null is empty, set nextNode equal to right of tmp.
      else
        nextNode = tmp->left; //If left of null is not empty, set nextNode equal to left of tmp.
      nextNode->parent = parentNode; //Make the child node point to the parent node.
    
      if(parentNode != nullptr) { //If statement that updates the parent node (runs when parentNode is not null.)
        if(parentNode->left == tmp)
          parentNode->left = nextNode; //If left of parentNode equals tmp, set left of parentNode equal to nextNode.
        else
          parentNode->right = nextNode; //If left of parentNode does not equals tmp, set right of parentNode equal to nextNode.
      }
      else
        root = nextNode; //If else statement is ran, set root equal to nextNode.

      actionPos = parentNode; //Set actionPos equal to parentNode.
    }
    else { //Suboption 2: Node has TWO CHILDREN.
      max = maxOfSubtree(tmp->left); //Set max equal to the largest value of the left subtree.
      actionPos = max->parent; //Set actionPos equal to the parent of the largest child node.
	  
      AVLNode * child = max->left; //Made new AVLNode pointer called child and set it equal to the left of max.
      tmp->ssn = max->ssn; //Imput the data into the proper nodes.
      tmp->name = max->name; 

      if(child != nullptr) { //If statement that runs while the child is not null.
        child->parent = max->parent; //Set the parent of child equal to parent of max.
        if(child->parent->left == max) //If statement that runs when the left of the parents child equals max.
          child->parent->left = child; //Set the left of the parents child equal to child.
        else
          child->parent->right = child; //Set the right of the parents child equal to child.
      }
      else { //Else statement that runs when child is null.
        if(actionPos->left == max) //If statment that runs when the left of actionPos is equal to max.
          actionPos->left = nullptr; //Set left of actionPos equal to null.
        else
          actionPos->right = nullptr; //Set the right of actionPost equal to null.
      }
      delete max; //Delete max.
    }
  }

  while(actionPos != nullptr) { //While statement that runs while actionPos is not null.
    balance(actionPos); //Balance the tree.
    actionPos = actionPos->parent; //Set actionPos equal to the parent of actionPos.
  }
  return true; //Return true.
}

// internal function
// do not call it directly
void AVLTree::print(AVLNode* x, int indent)
{
    if(x == nullptr) return;

    if (x->right != nullptr)
    {
        print(x->right, indent+4);
    }

    if (indent != 0)
    {
        cout << std::setw(indent) << ' ';
    }

    if(x->right != nullptr)
    {
        cout << " /\n" << std::setw(indent) << ' ';
    }

    cout << x->ssn << endl;

    if (x->left != nullptr)
    {
        cout << std::setw(indent) << ' ' <<" \\\n";
        print(x->left, indent+4);
    }

}

// print out the structure of the binary tree
// use it for debugging, I love this function
void AVLTree::print()
{
    int count = 0;
    print(root, count);
}


// it does not level order traversal
// it prints out the number of node
// use it mainly for debugging
void AVLTree::levelOrder(){ //IMPLEMENT THIS
  int nodeCount = 0; //Created a new int variable called nodeCount and set it equal to zero.

  if(root != nullptr) { //If statement that runs if the tree is not empty.
    AVLNode * curr = root; //Created two new AVLNode pointers; curr and parent.
    AVLNode * parent = nullptr;
	
    while (curr != nullptr) { //While loop that goes through the whole tree.
	  if(curr->left == nullptr) {
        nodeCount++; //If left of curr is null, incread nodeCount by one.
        curr = curr->right; //Set curr equal to the right side of the tree.
      } 	
	  else { //Else statment that runs if left of curr is not null.
        parent = curr->left; //Set parent equal to left of curr.
        while(parent->right != nullptr) { //While loop that runs as long as there are still parent nodes in the right side of the tree.
          if(parent->right == curr)
            break; //Break the functiong is the right of parent is equal to curr.
          else
            parent = parent->right; //If right of parent is not equal to curr, set parent equal to the right of parent.
        }	
        if(parent->right == nullptr) { 
          parent->right = curr;
          curr = curr->left; //If the right of parent is null, set right of parent equal to  curr and set curr equal to the left of curr.
        }	
        else {
          parent->right = nullptr;
          nodeCount++; //Increase nodeCount by one. 
          curr = curr->right;  //If the right of parent is not null, set right of parent equal to null, and set curr equal to the right of curr.	
	    }
      }
    }
  }
  cout << "Tree Size: " << nodeCount << endl;
}


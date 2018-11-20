
/*  BST312.h
  CS 312 Fall 2018

  a simple implementation of a binary search tree


*/

#ifndef BST_312_H
#define BST_312_H

#include <cstdlib>  // Provides size_t
#include <iostream>
#include <vector>

using namespace std;

template<class ItemType>
class BST_312 {
public:

    BST_312();

    //Copy constructor
    BST_312(const BST_312 & src);

    ~BST_312();

/****************************
makeEmpty

Function: Removes all the items from the BST.
Preconditions: BST has been initialized
Postconditions: All the items have been removed
*****************************/
    void makeEmpty();

/****************************
isEmpty

Function: Checks to see if there are any items in the BST.
Preconditions: BST has been initialized
Postconditions: Returns true if there are no items in the BST, else false.
*****************************/
    bool isEmpty() const;

/****************************
isFull

Function: Determines if you have any more room to add items to the BST
Preconditions: BST has been initialized
Postconditions: Returns true if there is no more room to add items, else false
*****************************/
    bool isFull() const;

/****************************
insertItem

Function: Adds newItem to the BST.
Preconditions: BST has been initialized and is not full.
Postconditions: newItem is in the proper position for a BST.
*****************************/
    void insertItem(const ItemType &);

/****************************
deleteItem

Function: Removes target from BST.
Preconditions: BST has been initialized.
Postconditions: If found, element has been removed from BST.
*****************************/
    void deleteItem(const ItemType& newItem);

/****************************
countNodes

Function: Counts the number of nodes in the BST
Preconditions: BST has been initialized.
Postconditions: returns the number of nodes in the BST
*****************************/
    int countNodes();

/****************************
preOrderTraversal

Function: Returns the preOder (Node, Left, Right) as a vector of ItemTypes
Preconditions: BST has been initialized.
Postconditions: none
*****************************/
    vector<ItemType> preOrderTraversal();

/****************************
inOrderTraversal

Function: Returns the inOder (Left, Node, Right) as a vector of ItemTypes
Preconditions: BST has been initialized.
Postconditions: none
*****************************/
    vector<ItemType> inOrderTraversal();

/****************************
postOrderTraversal

Function: returns the postOder (Left, Right, Node) as a vector of ItemTypes
Preconditions: BST has been initialized.
Postconditions: none
*****************************/
    vector<ItemType> postOrderTraversal();

/********************
 isItemInTree

Function: Determines if a given Item is in tree.
Preconditions: BST has been initialized.
Postconditions: none
*****************************/

    bool isItemInTree(const ItemType& item);


private:
    struct TreeNode {
        ItemType data;
        TreeNode *left;
        TreeNode *right;
    };

    TreeNode * root;


    void insertItem(TreeNode*& t, const ItemType& newItem);
    void inOrderTraversal(TreeNode* t,vector<ItemType>& result) const;
    int  countNodes(TreeNode* t) const;
    void deleteNode(TreeNode*& node);
    void makeEmpty(TreeNode*& t);
    void deleteItem(TreeNode*& t, const ItemType& newItem);
    void getPredecessor(TreeNode* t, ItemType& data);
    void preOrderTraversal(TreeNode* t,vector<ItemType>& result) const;
    void postOrderTraversal(TreeNode* t,vector<ItemType>& result) const;
    void copyTree(TreeNode*& copy, const TreeNode *originalTree);

};

/*******************************
//Function implementations
********************************/

template<class ItemType>
BST_312<ItemType>::BST_312 ()
{
    root = NULL;
}


template<class ItemType>
BST_312<ItemType>::BST_312(const BST_312 & src)
{
    copyTree(root, src.root);
}


template<class ItemType>
BST_312<ItemType>::~BST_312()
{
    makeEmpty();
}


template<class ItemType>
void BST_312<ItemType>::copyTree(TreeNode*& copy, const TreeNode* originalTree)
{
    if (originalTree == NULL)
        copy = NULL;
    else
    {
        copy = new TreeNode;
        copy->data = originalTree->data;

        copyTree(copy->left, originalTree->left);
        copyTree(copy->right, originalTree->right);
    }
}


template<class ItemType>
void BST_312 <ItemType>::deleteNode(TreeNode*& t)
{
    ItemType info;
    TreeNode *tempPtr;

    tempPtr = t;

    if (t->left == NULL)
    {
        t = t->right;
        delete tempPtr;
    }
    else if (t->right == NULL)
    {
        t = t->left;
        delete tempPtr;
    }
    else
    {
        getPredecessor(t->left, info);
        t->data = info;
        deleteItem(t->left, info);
    }
}


//find largest in left subtree
template<class ItemType>
void BST_312 <ItemType>::getPredecessor(TreeNode* t, ItemType& data)
{
    while (t->right != NULL)
        t = t->right;

    data = t->data;
}


template<class ItemType>
void BST_312 <ItemType>::deleteItem(TreeNode*& t, const ItemType& newItem)
{
    if (t == NULL)
        return;
    else if (newItem < t->data)
        deleteItem(t->left, newItem);
    else if (newItem > t->data)
        deleteItem(t->right, newItem);
    else
        deleteNode(t);
}


template<class ItemType>
void BST_312 <ItemType>::deleteItem(const ItemType& newItem)
{
    deleteItem(root, newItem);
}


template<class ItemType>
void BST_312 <ItemType>::makeEmpty(TreeNode*& t)
{
    if(t == NULL) return;
    makeEmpty(t->left);
    makeEmpty(t->right);
    delete t;
}


template<class ItemType>
void BST_312 <ItemType>::makeEmpty()
{
    makeEmpty(root);
    root = NULL;
}


template<class ItemType>
bool BST_312 <ItemType>::isEmpty() const
{
    if(root == NULL) return true;
    else return false;
}


template<class ItemType>
bool BST_312 <ItemType>::isFull() const
{
    try
    {
        TreeNode *temp = new TreeNode;
        delete temp;
        return false;
    }
    catch (std::bad_alloc)
    {
        return true;
    }
}


template<class ItemType>
void BST_312 <ItemType>::insertItem(TreeNode*& t, const ItemType& newItem)
{
    if(!isFull()) {
        TreeNode *temp = new TreeNode;
        temp->data = newItem;
        temp->left = NULL;
        temp->right = NULL;

        TreeNode *ptr = t;

        if (ptr == NULL) {
            t = temp;
            return;
        }

        while (temp->data != ptr->data) {
            if (temp->data < ptr->data) {
                if (ptr->left == NULL)
                    ptr->left = temp;
                ptr = ptr->left;                        //while loop exits when ptr is assigned to newly added node
            }
            else if (temp->data > ptr->data) {
                if (ptr->right == NULL)
                    ptr->right = temp;
                ptr = ptr->right;
            }
        }
    }
}


template<class ItemType>
void BST_312 <ItemType>::insertItem(const ItemType& newItem)
{
    insertItem(root, newItem);
}


template<class ItemType>
int BST_312 <ItemType>::countNodes(TreeNode* t) const
{
    int nodeCount = 1;                              //count the node itself
    if(t->left != NULL) nodeCount += countNodes(t->left);
    if(t->right != NULL) nodeCount += countNodes(t->right);

    return nodeCount;
}


template<class ItemType>
int BST_312 <ItemType>::countNodes()
{
    if (root == NULL) return 0;
    else return countNodes(root);
}


template<class ItemType>
void BST_312 <ItemType>::preOrderTraversal(TreeNode* t,vector<ItemType>& result) const
{
    if(t != NULL){
        result.push_back(t->data);              //N
        preOrderTraversal(t->left, result);    //L
        preOrderTraversal(t->right, result);   //R
    }
}


template<class ItemType>
vector<ItemType> BST_312 <ItemType>::preOrderTraversal()
{
    vector <ItemType> result;
    preOrderTraversal(root, result);
    return result;
}


template<class ItemType>
void BST_312 <ItemType>::inOrderTraversal(TreeNode* t,vector<ItemType>& result) const
{
    if(t != NULL){
        inOrderTraversal(t->left, result);    //L
        result.push_back(t->data);              //N
        inOrderTraversal(t->right, result);   //R
    }
}


template<class ItemType>
vector<ItemType> BST_312 <ItemType>::inOrderTraversal()
{
    vector <ItemType> result;
    inOrderTraversal(root, result);
    return result;
}


template<class ItemType>
void BST_312 <ItemType>::postOrderTraversal(TreeNode* t,vector<ItemType>& result) const
{
    if(t != NULL){
        postOrderTraversal(t->left, result);        //L
        postOrderTraversal(t->right, result);       //R
        result.push_back(t->data);                  //N
    }
}


template<class ItemType>
vector<ItemType> BST_312 <ItemType>::postOrderTraversal()
{
    vector <ItemType> result;
    postOrderTraversal(root, result);
    return result;
}


template<class ItemType>
bool BST_312 <ItemType>::isItemInTree(const ItemType& item) {
    if (root == NULL) return false;
    TreeNode *temp = root;

    while(temp != NULL){
        if(item < temp->data) temp = temp->left;
        else if(item > temp->data) temp = temp->right;
        else if(item == temp->data) return true;
    }
    return false;               //false when search goes to where the Item would be if it was there, and the program finds a NULL
}


#endif


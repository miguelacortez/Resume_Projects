// mymap.h
//
// This program will create a custom map class.
//
// Author: Miguel Cortez
// Date: 10/31/2022
// Course: CS 251, Thurs. 12pm Lab
//
// Contributors: Miguel Cortez (Program 04)
//

#pragma once

#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

template <typename keyType, typename valueType>
class mymap 
{
 private:
    struct NODE 
    {
        keyType key;  // used to build BST
        valueType value;  // stored data for the map
        NODE* left;  // links to left child
        NODE* right;  // links to right child
        int nL;  // number of nodes in left subtree
        int nR;  // number of nodes in right subtree
        bool isThreaded;
    };

    NODE* root;  // pointer to root node of the BST
    int size;  // # of key/value pairs in the mymap

    //
    // iterator:
    // This iterator is used so that mymap will work with a foreach loop.
    //
    struct iterator 
    {
     private:
        NODE* curr;  // points to current in-order node for begin/end

     public:
        iterator(NODE* node) 
        {
            curr = node;
        }

        keyType operator *() 
        {
            return curr -> key;
        }

        bool operator ==(const iterator& rhs) 
        {
            return curr == rhs.curr;
        }

        bool operator !=(const iterator& rhs) 
        {
            return curr != rhs.curr;
        }

        bool isDefault() 
        {
            return !curr;
        }

        //
        // operator++:
        //
        // This function should advance curr to the next in-order node.
        // O(logN)
        //
        iterator operator++() 
        {
            // Condition to check if curr is threaded
            if (curr->isThreaded)
            {
                curr = curr->right;
            }

            // Otherwise, continue to onto right child
            else
            {
                curr = curr->right;

                // Condition to check if there is a left child, if so
                // traverse BST to the left-most node
                if (curr->left != nullptr)
                {
                    while (curr->left != nullptr)
                    {
                        curr = curr->left;
                    }
                }
            }

            return iterator(curr);
        }
    };

    //
    // _moveNodeLeft()
    //
    // This helper function will take in a node and assign it to the 
    // leftmost node in the map. It will take in a NODE pointer
    // and return its new value via the reference parameter
    //
    struct NODE* _moveNodeLeft(NODE *currNode)
    {
        if (currNode == nullptr)
        {
            return nullptr;
        }

        while (currNode->left != nullptr)
        {
            currNode = currNode->left;
        }

        return currNode;
    }

    //
    // _toString()
    //
    // This will be a helper function to the toString() member function.
    // It will convert the current binary search tree into a string,
    // having it displayed in ascending order (in-order traversal).
    //
    void _toString(NODE *curr, ostream &output)
    {
        // Condition to check if we have entered an empty BST/node
        if (curr == nullptr)
        {
            return;
        }

        else
        {
            // Traversing down left side of the BST
            _toString(curr->left, output);
        
            output << "key: " << curr->key << " value: " << curr->value << endl;

            // Condition to check if curr is threaded 
            curr = (curr->isThreaded) ? nullptr : curr->right;

            // Traverse down right side of the BST
            _toString(curr, output);
        }
    }

    //
    // _clear()
    //
    // This will be a helper function to the clear() member function.
    // It will perform a poster order traversal to delete the nodes
    // from the leaves, going up.
    void _clear(NODE *currNode)
    {
        // Recursive base case
        if (currNode == nullptr)
        {
            return;
        }

        // Otherwise, continue traversing BST, deleting leaves/nodes
        else
        {
            _clear(currNode->left);

            // Condition to check if currNode is not threaded before traversing right
            if (!currNode->isThreaded)
            {
                _clear(currNode->right);
            }
            
            delete currNode;
        }
    }

    //
    // _equalOperatorHelper()
    //
    // This function will be a helper function to the = operator overload
    // This function will perform a pre-order traversal to
    // assign the right-hand side values to the class object
    void _equalOperatorHelper(NODE *otherNode)
    {
        // Recursive base case
        if (otherNode == nullptr)
        {
            return;
        }

        // Creating new key-value pair
        put(otherNode->key, otherNode->value);

        // Traversing left side
        _equalOperatorHelper(otherNode->left);

        // Condition to check if otherNode is threaded
        otherNode = (otherNode->isThreaded) ? nullptr : otherNode->right;

        // Traversing right side
        _equalOperatorHelper(otherNode);
    }

    //
    // _copyConst()
    //
    // This function will be a helper function to the copy constructor.
    // It will take in the implicit object and the source object as 
    // parameters. It will then perform a pre-order traversal to copy
    // over all of source values respectively. 
    void _copyConst(mymap &thisMap, NODE *otherMap)
    {
        // Base case for recursive copying of map
        if (otherMap == nullptr)
        {
            return;
        }

        // Inserting key-value pair
        thisMap.put(otherMap->key, otherMap->value);

        // Traversing left side 
        _copyConst(thisMap, otherMap->left);

        // Condition to traverse right side is otherMap node isn't threaded
        if (!otherMap->isThreaded)
        {
            _copyConst(thisMap, otherMap->right);
        }
    }

    //
    // _toVector()
    //
    // This function will be a helper function to the toVector() function.
    // It will perform an in-order traversal and populate the key-value
    // pairs into the given vector. 
    void _toVector(NODE *currentNode, vector<pair<keyType, valueType>> &tempToVector)
    {
        // Recursive base case
        if (currentNode == nullptr)
        {
            return;
        }

        else
        {
            // Traversing left side
            _toVector(currentNode->left, tempToVector);

            // Condition to push back new key-value pair 
            tempToVector.push_back(make_pair(currentNode->key, currentNode->value));

            // Condition to check if currentNode is threaded
            currentNode = (currentNode->isThreaded) ? nullptr : currentNode->right;

            // Traversing right side
            _toVector(currentNode, tempToVector);
        }
    }

    //
    // _checkBalance()
    //
    // This function will be a helper function to the checkBalance()
    // member function. It will preform a pre-order traversal to display
    // the (assumed) balanced tree's nodes, respectively.
    void _checkBalance(NODE *currNode, ostream &output)
    {
        // Base case for recursive call; checking for empty BST/node
        if (currNode == nullptr)
        {
            return;
        }

        // Traversing left side
        _checkBalance(currNode->left, output);

        output << "key: " << currNode->key << ", nL: " << currNode->nL << ", nR: " << currNode->nR << endl;

        // Condition to check that currNode isn't threaded before traversing right side
        if (!currNode->isThreaded)
        {
            _checkBalance(currNode->right, output);
        }
    }

 public:
    //
    // default constructor:
    //
    // Creates an empty mymap.
    // Time complexity: O(1)
    //
    mymap() 
    {
        root = nullptr;
        size = 0;
    }

    //
    // copy constructor:
    //
    // Constructs a new mymap which is a copy of the "other" mymap.
    // Sets all member variables appropriately.
    // Time complexity: O(nlogn), where n is total number of nodes in threaded,
    // self-balancing BST.
    //
    mymap(const mymap& other) 
    {
        root = nullptr;

        // Helper function call
        _copyConst(*this, other.root);

        this->size = other.size;
    }

    //
    // operator=:
    //
    // Clears "this" mymap and then makes a copy of the "other" mymap.
    // Sets all member variables appropriately.
    // Time complexity: O(nlogn), where n is total number of nodes in threaded,
    // self-balancing BST.
    //
    mymap& operator=(const mymap& other) 
    {
        // Base case to check if object is "self-assigning"
        if (this == &other)
        {
            return *this;
        }

        this->clear();

        // Helper function call
        _equalOperatorHelper(other.root);

        this->size = other.size;

        return *this;
    }

    // clear:
    //
    // Frees the memory associated with the mymap; can be used for testing.
    // Time complexity: O(n), where n is total number of nodes in threaded,
    // self-balancing BST.
    //
    void clear() 
    {
        // Helper function call
        _clear(root);

        root = nullptr;
        size = 0;
    }

    //
    // destructor:
    //
    // Frees the memory associated with the mymap.
    // Time complexity: O(n), where n is total number of nodes in threaded,
    // self-balancing BST.
    //
    ~mymap() 
    {
        // Helper function call
        clear();
    }

    //
    // put:
    //
    // Inserts the key/value into the threaded, self-balancing BST based on
    // the key.
    // Time complexity: O(logn + mlogm), where n is total number of nodes in the
    // threaded, self-balancing BST and m is the number of nodes in the
    // sub-tree that needs to be re-balanced.
    // Space complexity: O(1)
    //
    void put(keyType key, valueType value) 
    {
        NODE *prevNode = nullptr;
        NODE *currNode = root;

        // This loop will traverse to the desired node
        while (currNode != nullptr)
        {
            // Duplicate base case
            if (currNode->key == key)
            {
                prevNode = currNode;
                currNode->value = value;
            
                return;
            }

            // Go left, down BST
            if (key < currNode->key)
            {
                prevNode = currNode;
                currNode->nL++;
                currNode = currNode->left;
            }

            // Go right, down BST
            else
            {
                prevNode = currNode;

                // Condition to check if current node is threaded
                if (currNode->isThreaded)
                {
                    currNode = nullptr;
                }

                else
                {
                    currNode->nR++;
                    currNode = currNode->right;
                }
            }
        }

        NODE *newNode = new NODE();
        newNode->key = key;
        newNode->value = value;
        newNode->left = nullptr;
        newNode->right = nullptr;
        newNode->nL = 0;
        newNode->nR = 0;
        newNode->isThreaded = false;

        // Condition to check for empty BST
        if (prevNode == nullptr)
        {
            newNode->isThreaded = true;
            newNode->right = nullptr;
            root = newNode;
        }

        // Otherwise, attempt to add left child
        else if (key < prevNode->key)
        {
            prevNode->left = newNode;
            newNode->right = prevNode;
            newNode->isThreaded = true;
        }

        // Otherwise, attempt to add right child
        else
        {
            newNode->right = prevNode->right;
            newNode->isThreaded = true;

            prevNode->right = newNode;
            prevNode->isThreaded = false;
        }

        size++; 
    }

    //
    // contains:
    // Returns true if the key is in mymap, return false if not.
    // Time complexity: O(logn), where n is total number of nodes in the
    // threaded, self-balancing BST
    //
    bool contains(keyType key) 
    {
        NODE *currNode = root;

        // Search BST for key, return true when if found
        while (currNode != nullptr)
        {
            // Condition to check if key exists, returning true
            if (currNode->key == key)
            {
                return true;
            }

            // Traversing left BST
            if (key < currNode->key)
            {
                currNode = currNode->left;
            }

            // Traversing right BST
            else
            {
                // Condition to check current node is threaded
                currNode = (currNode->isThreaded) ? nullptr : currNode->right;
            }
        }

        // Otherwise, key was not found
        return false;  
    }

    //
    // get:
    //
    // Returns the value for the given key; if the key is not found, the
    // default value, valueType(), is returned (but not added to mymap).
    // Time complexity: O(logn), where n is total number of nodes in the
    // threaded, self-balancing BST
    //
    valueType get(keyType key) 
    {   
        // Condition to check that key exists within map
        if (contains(key))
        {
            NODE *currNode = root;

            // Search BST for key, return value if found
            while (currNode != nullptr)
            {
                // Condition to check if key-value exists
                if (currNode->key == key)
                {
                    return currNode->value;
                }

                // Traversing left side of BST
                if (key < currNode->key)
                {
                    currNode = currNode->left;
                }

                // Traversing right side of BST
                else
                {
                    // Condition to check if current node is threaded
                    currNode = (currNode->isThreaded) ? nullptr : currNode->right;
                }
            }
        }

        // Otherwise, return default value
        return {};
    }

    //
    // operator[]:
    //
    // Returns the value for the given key; if the key is not found,
    // the default value, valueType(), is returned (and the resulting new
    // key/value pair is inserted into the map).
    // Time complexity: O(logn + mlogm), where n is total number of nodes in the
    // threaded, self-balancing BST and m is the number of nodes in the
    // sub-trees that need to be re-balanced.
    // Space complexity: O(1)
    //
    valueType operator[](keyType key) 
    {
        // Condition to check if key exists within map
        if (contains(key))
        {
            valueType returnValue = get(key);
            return returnValue;
        }

        // Otherwise, create key-value pair
        put(key, valueType());

        return valueType();
    }

    //
    // Size:
    //
    // Returns the # of key/value pairs in the mymap, 0 if empty.
    // O(1)
    //
    int Size() 
    {
        return size;
    }

    //
    // begin:
    //
    // returns an iterator to the first in order NODE.
    // Time complexity: O(logn), where n is total number of nodes in the
    // threaded, self-balancing BST
    //
    iterator begin() 
    {
        // Helper function call to assign left-most node
        NODE *nextNode = _moveNodeLeft(root);

        return iterator(nextNode);
    }

    //
    // end:
    //
    // returns an iterator to the last in order NODE.
    // this function is given to you.
    // 
    // Time Complexity: O(1)
    //
    iterator end() 
    {
        return iterator(nullptr);
    }

    //
    // toString:
    //
    // Returns a string of the entire mymap, in order.
    // Format for 8/80, 15/150, 20/200:
    // "key: 8 value: 80\nkey: 15 value: 150\nkey: 20 value: 200\n
    // Time complexity: O(n), where n is total number of nodes in the
    // threaded, self-balancing BST
    //
    string toString() 
    {
        stringstream stringStream;

        // Helper function call
        _toString(root, stringStream);

        string str = stringStream.str();

        return str;
    }

    //
    // toVector:
    //
    // Returns a vector of the entire map, in order.  For 8/80, 15/150, 20/200:
    // {{8, 80}, {15, 150}, {20, 200}}
    // Time complexity: O(n), where n is total number of nodes in the
    // threaded, self-balancing BST
    //
    vector<pair<keyType, valueType> > toVector() 
    {
        vector <pair<keyType, valueType>> tempToVector;

        // Helper function call
        _toVector(root, tempToVector);

        return tempToVector;
    }

    //
    // checkBalance:
    //
    // Returns a string of mymap that verifies that the tree is properly
    // balanced.  For example, if keys: 1, 2, 3 are inserted in that order,
    // function should return a string in this format (in pre-order):
    // "key: 2, nL: 1, nR: 1\nkey: 1, nL: 0, nR: 0\nkey: 3, nL: 0, nR: 0\n";
    // Time complexity: O(n), where n is total number of nodes in the
    // threaded, self-balancing BST
    //
    string checkBalance() 
    {
        stringstream checkStream;

        // Helper function call
        _checkBalance(root, checkStream);

        return checkStream.str();
    }
};

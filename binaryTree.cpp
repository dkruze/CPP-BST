//Filename: binaryTree.cpp
//Author: Daniel Kruze
//Create Date: 10/03/21
//Compile Date: 10/09/21

#include <iostream> // cout, cin
#include <cstdlib> // utility functions, exit()

using namespace std; // standard namespace

int k; // global for holding the user input value
int counter = 0; // global for tracking how many children have been processed by the kthsmallest function
int input[] = {6, 17, 20, 41, 45, 52, 57, 71, 76, 79, 87, 92, 95, 99}; // values to be insert into the tree

/*
* Let there exist nodes that represent members of the binary tree
*/
struct Node { // let a node that holds a value and a series of pointers be a struct
    int value; // a node has an integer value
    Node* leftChild; // a node has a left child (whose value is lower than the node's value)
    Node* rightChild; // a node has a right child (whose value is higher than the node's value)
    Node(): rightChild(NULL), leftChild(NULL) { // this node constructor initializes all new nodes with no children
    }
};

/*
* Let there be a class representing the binary tree itself, made up of node members
*/
class bigTree { // class representing a binary search tree
    Node* root; // there is a specific node that is the root of the tree

    public:
        bigTree(int); // constructor
        ~bigTree(); // destructor
        void destroyTree(struct Node*); // method that the destructor calls to delete the tree
        void newMember(int); // method for calling the method that inserts into the tree
        void insert(struct Node*, int); // method for inserting into the tree
        //void deadMember(int); // method for calling the method that removes from the tree (unused in this implementation)
        //void remove(struct Node*, int); // method for removing from the tree (unused in this implementation)
        void displayTree(); // method for calling the method that prints the members of the tree
        void printTree(struct Node*); // method that prints the members of the tree
        void findk(); // method for calling the method that prints the kth smallest member of the tree
        void kthSmallest(struct Node*); // method that prints the kth smallest member of the tree
};

/*
* The constructor accepts a parameter that allows it to pass a specified value to the root
*/
bigTree::bigTree(int value) {
    cout << "Tree Initialized!" << endl; // notify the user that the tree exists
    this->root = new Node(); // initialize the root
    root->value = value; // the root has the intial value passed as an argument
};

/*
* The destructor calls a method that deletes all members of the tree, then notifies the user that it has been deleted
*/
bigTree::~bigTree() {
    destroyTree(root); // call deletion method
    cout << endl << "Tree Destroyed!" << endl; // notify the user that the tree is deleted entirely
};

/*
* The method will deallocate and delete node in the tree when the program ends or the driver function no longer needs the instance
* This is done by deleting all children of the root, and then the root itself in a postorder traversal
* Expected input: a member of the tree "tree"
* Expected output: deletion of the input member of the tree "tree"
*/
void bigTree::destroyTree(struct Node* dead) {
    if (dead != NULL) { // while the node passed to the method exists
        destroyTree(dead->leftChild); // process that node's left child(ren)
        destroyTree(dead->rightChild); // process that node's right child(ren)
        delete dead; // process the given node by deleting it
    }
};

/*
* This Node accepts an integer as a new value for a member of the tree "tree"
* It calls the insertion method to create this new member and insert it relative to the root
* Expected input: integer value from the input array
* Expected output: call to insert()
*/
void bigTree::newMember(int newNum) {
    insert(root, newNum); // call the insertion method
};

/*
* This method accepts a member of the tree "tree" and a new value, then finds a place for the new value in that tree
* It does this by checking if the given node, starting with the root (passed above,) has a value larger or smaller than the new node to be inserted 
* If it has a larger value, insert a new node with the new value if no right child exists
*   If a right child does exist, process that child
* If it has a smaller value, insert a new node with the new value if no left child exists
*   If a left child does exist, process that child
* In either case, once an empty spot is found (meaning that no smaller/larger node exists than the new node to be inserted,) a new child is
*   added using a temporary pointer node
* In the case that a null pointer is passed to this function or that the root doesn't exist, the program will end promptly 
* Expected input: node members of the tree "tree," starting with the root, and an integer passed to newMember()
* Expected output: a new element in the tree "tree"
*/
void bigTree::insert(struct Node* insertTemp, int newNum) {
    if (insertTemp == NULL){
        cout << "Fatal memory error!" << endl;
        exit(0);
    }
    else if (newNum <= insertTemp->value){
        if (insertTemp->leftChild == NULL) {
            Node* tempL = new Node();
            tempL->value = newNum;
            insertTemp->leftChild = tempL;
            return;
        }
        insert(insertTemp->leftChild, newNum);
    }
    else if (newNum > insertTemp->value) {
        if (insertTemp->rightChild == NULL) {
            Node* tempR = new Node();
            tempR->value = newNum;
            insertTemp->rightChild = tempR;
            return;
        }
        insert (insertTemp->rightChild, newNum);
    }
};


/*void bigTree::deadMember(int searchNum) {
    remove(root, searchNum);
};


void bigTree::remove(struct Node* removeTemp, int searchNum) {

};*/

/*
* This method simply calls the other method to print the tree--this is so the print function can accept a class member as an argument
* Expected input: none
* Expected output: call to the printTree() method
*/
void bigTree::displayTree() {
    printTree(root); // invoke the printing method with the root as an argument
};

/*
* This method recursively prints the elements (nodes) of the binary search tree by being passed the root of the tree as an argument
* It achieves this by letting the root (or any node passed to it, represented by "temp") have all its children printed until no more children 
*   exist on the left, then printing itself, then having all its right children printed (their values, that is)
* Expected input: node representing an element in the tree--starting with the root
* Expected output: a single line of 15 integers
*/
void bigTree::printTree(struct Node* temp) {
    if (temp != NULL) { // while the node passed to the method exists
        printTree(temp->leftChild); // process that node's left child(ren)
        cout << temp->value << " "; // process that node (print its value)
        printTree(temp->rightChild); // process that node's right child(ren)
    }
};

/*
* This method simply calls the other method to find the kth smallest element of the tree--this is so the print function can accept a class 
*   member as an argument
* Expected input: none
* Expected output: call to the kthSmallest() method
*/
void bigTree::findk() {
    kthSmallest(root); // invoke the kthSmallest method with the root as an argument
};

/*
* This method finds the kth smallest element in the tree "tree" by starting at the lowest value relative to the root, meaning its deepest left child
* Every time the lowest value is processed, a counter is incremented and the next value up is processed
* Ideally, this will preorder traverse the tree to find the smallest values incrementing upward, stopping when it has traversed k elements
* Expected input: node representing an element in the tree--starting with the root
* Expected output: an integer value representing the value in the kth-smallest member of the tree "tree"
*/
void bigTree::kthSmallest(struct Node* kth) {
    if (counter == k) { // if the smallest element has already been found
        return; // exit the method
    }
    if (kth != NULL) { // while the node passed to the method exists
        kthSmallest(kth->leftChild); // process the node's left child(ren)
        counter++; // begin to process the current node; start by incrementing the counter global, indicating 1 node has been processed
        if (counter == k) { // if the counter has incremented k times
            if (k == 1) { // if the counter is 1
                cout << "The " << k << "st smallest element is: " << kth->value << endl; // print the node's value
            }
            else if (k == 2) { // if the counter is 2
                cout << "The " << k << "nd smallest element is: " << kth->value << endl; // print the node's value
            }
            else if (k == 3) { // if the counter is 3
                cout << "The " << k << "rd smallest element is: " << kth->value << endl; // print the node's value
            }
            else { // if the counter is [4, 15]
                cout << "The " << k << "th smallest element is: " << kth->value << endl; // print the node's value
            }
            return; // exit the method before processing other elements: the correct value has been found
        }
        kthSmallest(kth->rightChild); // if the counter has not incremented k times, process the node's right child(ren)
    }
};

int main() {
    bigTree tree(65); // instantiate the tree with a root of 65
    bool sentryMain = true; // sentry for the following while loop
    while (sentryMain) { // sentry = true
        cout << "Please enter a positive integer within the bounds [1, 15]:\n>> "; // there are only 15 values in the tree, making a 0th or smaller case/16th or larger case impossible to evaluate
        cin >> k; // int n = user input
        if (cin.fail()){ // if the user enters a non-integer
            cin.clear(); // clear the error flag that cin throws
            cin.ignore(100000, '\n'); // ignore up to 100,000 entered characters (technically, an input of 100,001 characters could break this program)
            cout << "Invalid input!" << endl; // warn the user their input is invalid, let them try again
        }
        else if (!cin.fail()) { // if the user enters an integer
            if (k >= 16 || k <= 0) { // if the user enters any integer lower than 1 or higher than 15
                cout << "Invalid Input!" << endl; // warn the user their input is invalid, let them try again
            }
            else { // if the user enters a valid integer
                for (int i = 0; i < 14; i++) { // iterate 14 times
                    tree.newMember(input[i]); // insert an element from the array into the tree
                }
                tree.displayTree(); // print out all members of the tree
                cout << endl; // spacer line
                tree.findk(); // find the kth smallest member of the tree
                sentryMain = false; // end the loop
            }
        }
    }
    return 0;
}
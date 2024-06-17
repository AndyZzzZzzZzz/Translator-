/*
 * BST.cpp
 * 
 * Description: Binary Search Tree data collection ADT class.
 *              Link-based implementation.
 *              Duplicated elements are not allowed.
 *
 * Class invariant: It is always a BST.
 * 
 * Author: Kunpeng (Andy) Zhang
 * Date of last modification: March 10, 2024
 */
 
#include "BST.h"
#include "WordPair.h"
#include <iostream>

using std::cout;
using std::endl;
using std::nothrow;


// You cannot change the prototype of the public methods of this class.
// Remember, if you add public methods to this class, our test driver 
// - the one with which we will mark this assignment - 
// will not know about them since, in order to create it, we will have 
// used only the public method prototypes below.


/* Constructors and destructor */

   // Default constructor
   BST::BST() { }            

   // Copy constructor
   BST::BST(const BST & aBST) {
     
     //Set the root of BST to nullptr
     root = nullptr;

     //recursively copy all nodes from aBST to this BST. 
     copyBST(aBST.root,root);
     
     //Update element count 
     elementCount = aBST.elementCount;
   }

   // Destructor 
   BST::~BST() {
      //Recursively delete every node using freeTree method
      freeTree(root);
      //Set element Count to 0 and root to nullptr
      elementCount = 0;
      root = nullptr;
   }                
   
   
/* Getters and setters */

   // Description: Returns the number of elements currently stored in the binary search tree.   
   // Postcondition: This method does not change the binary search tree.
   // Time efficiency: O(1)
   unsigned int BST::getElementCount() const {     

     return this->elementCount;
	 
   }
   

/* BST Operations */

   // Description: Inserts an element into the binary search tree.
   //              This is a wrapper method which calls the recursive insertR( ).
   // Precondition: "newElement" does not already exist in the binary search tree.
   // Exception: Throws the exception "UnableToInsertException" when newElement 
   //            cannot be inserted because the "new" operator failed. 
   // Exception: Throws the exception "ElementAlreadyExistsException" 
   //            if "newElement" already exists in the binary search tree.
   // Time efficiency: O(log2 n)   
   void BST::insert(WordPair & newElement) {
      
      //Attempt to create a new node
      try{
         //Create a new BST node using newElement 
         BSTNode* newNode = new BSTNode(newElement);

         //If BST empty, make this new node the root
         if(root == nullptr){
            root = newNode;
            elementCount ++;
            return;
         }

         //If the root is not empty, recursively enter the node into correct position
         if(insertR(newNode, root)){
            //If the insertR method returns true, insertion is successful and increment element count
            elementCount ++;
            return;
         }
         else{
         	//If insertR method returns false, free memory and throw element exist exception
               delete newNode;
               throw ElementAlreadyExistsException();
         }

      } 
      //Catch the error of memory allocation failure and throw exception 
      catch(std::bad_alloc&){
            //Throw cooresponding exception 
            throw UnableToInsertException();
      }
	  
   } 
   
   // Description: Recursive insertion into a binary search tree.
   //              Returns true when "anElement" has been successfully inserted into the 
   //              binary search tree. Otherwise, returns false.
   bool BST::insertR(BSTNode * newBSTNode, BSTNode * current) {  
         //Check if elements in new node is larger than element in current 
         if(newBSTNode-> element > current -> element){
            //If right sub-tree of current is empty, insert new node
            if(!current -> hasRight()){
               current -> right  = newBSTNode;
               return true;
            }
            //If there is a right sub-tree, recursively find correct position 
            else{
               return insertR(newBSTNode, current -> right);
            }
         }
         //Check if elements in new node is smaller than element in current 
         else if(newBSTNode-> element < current -> element){
            //If left sub-tree of current is empty, insert new node
            if(!current -> hasLeft()){
               current -> left  = newBSTNode;
               return true;
            }
            //If there is a left sub-tree, recursively find correct position 
            else{
               return insertR(newBSTNode, current -> left);
            }
         }
         //If the element in new node equals element in current, there's duplication
         //return false because we cannot insert duplicated element
         else{
            return false;
         }
	  
		
   }

   
   // Description: Retrieves "targetElement" from the binary search tree.
   //              This is a wrapper method which calls the recursive retrieveR( ).
   // Precondition: Binary search tree is not empty.
   // Exception: Throws the exception "EmptyDataCollectionException" 
   //            if the binary search tree is empty.
   // Exception: Propagates the exception "ElementDoesNotExistException" 
   //            thrown from the retrieveR(...)
   //            if "targetElement" is not found in the binary search tree.
   // Postcondition: This method does not change the binary search tree.
   // Time efficiency: O(log2 n)
   WordPair& BST::retrieve(WordPair & targetElement) const {
     //If element count is 0, throw empty exception
     if (elementCount == 0)  
     	//throw corresponding exception
        throw EmptyDataCollectionException();

     //Call recursive retrieveR function. If the element does not exist, recursiveR will
     //throw corresponding exception 
     WordPair& translated = retrieveR(targetElement, root);
     //Return result
     return translated;
   }

   // Description: Recursive retrieval from a binary search tree.
   // Exception: Throws the exception "ElementDoesNotExistException" 
   //            if "targetElement" is not found in the binary search tree.
   // Postcondition: This method does not change the binary search tree.
   WordPair& BST::retrieveR(WordPair & targetElement, BSTNode * current) const {
      //Base case, we didn't found any matching element
      if(current == nullptr){
         throw ElementDoesNotExistException();
      }
      //If we found a match, return the element
      if(current -> element == targetElement){
         return current -> element;
      }
      //if current element is larger than target, search the left sub-tree
      else if(current -> element > targetElement){
         return retrieveR(targetElement, current -> left);
      }
      //If current element is less than target, search the right sub-tree
      else{
         return retrieveR(targetElement, current -> right);
      }
	 
   } 
         
   
   // Description: Traverses the binary search tree in order.
   //              This is a wrapper method which calls the recursive traverseInOrderR( ).
   //              The action to be done on each element during the traverse is the function "visit".
   // Precondition: Binary search tree is not empty.
   // Exception: Throws the exception "EmptyDataCollectionException" 
   //            if the binary search tree is empty.
   // Postcondition: This method does not change the binary search tree.
   // Time efficiency: O(n)     
   void BST::traverseInOrder(void visit(WordPair &)) const {
     //If elementCount is 0, throw empty data collection exception 
     if (elementCount == 0)  
       throw EmptyDataCollectionException();
     
     //Call recursive traverse in order function
     traverseInOrderR(visit, root);
     
     return;
   }

   // Description: Recursive in order traversal of a binary search tree.   
   // Postcondition: This method does not change the binary search tree. 
   void BST::traverseInOrderR(void visit(WordPair &), BSTNode* current) const { 
   
     //Base case : node is empty
     if(current == nullptr){
      return;
     }
     else{
      //traverse through left sub-tree
      traverseInOrderR(visit, current -> left);
      //Visit element in the node 
      visit(current -> element);
      //traverse through right sub-tree
      traverseInOrderR(visit, current -> right);
     }
	  
   }

   //Description: Recursive free nodes in a BST tree.
   //Precondition: BST is not empty.
   //Postcondition: Every node stored in BST is deleted properly and element count is being set to zero.
   //               Result BST is empty.
   //Time Efficiency: O(n).
   void BST::freeTree(BSTNode* current){
      //Check that the root is not null
      if(current == nullptr){
         return;
      }
      //If tree is not empty, recursively delete nodes using post-order traverse
      else{
         //Delete node from left sub-tree
         freeTree(current -> left);
         //Delete node from right sub-tree
         freeTree(current -> right);
         //Delete node
         delete current;
         
      }
   }

   //Description: Recursive copy nodes from one BST tree to another BST tree.
   //Precondition: Original BST tree is not empty.
   //Postcondition: Original BST tree is not modified, target BST tree has all the elements in the 
   //               same format as original BST tree.
   //Time efficiency: O(n).
   void BST::copyBST(BSTNode* original, BSTNode* &target){
       //Check that the root is not null
      if(original == nullptr){
         return;
      }
      //If tree is not empty, recursively copy nodes using pre-order traverse
      else{
         //Create a new node for target using element from original node
         target = new BSTNode(original -> element);
         //Copy the left sub-tree
         copyBST(original -> left, target -> left);
         //Copy the right sub-tree
         copyBST(original -> right, target -> right);
      }
   }

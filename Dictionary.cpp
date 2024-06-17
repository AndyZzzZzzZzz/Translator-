/*
 * Dictionary.cpp
 * 
 * Description: Implementation of dictonary data collection ADT class.
 *              BST-based implementation.
 *              Duplicated elements not allowed.
 *              
 * Author: Kunpeng (Andy) Zhang 
 * Date of last modification: March 11, 2024
 */
 
 #include "Dictionary.h"
 #include <iostream>
 
using std::cout;
using std::endl;
using std::nothrow;

 // Constructor and destructor:
   Dictionary::Dictionary(){
   	//Create a BST for dictionary 
   	keyValuePairs = new BST();
   	
   }  
   
                            
   Dictionary::~Dictionary(){
   	//Free dynamically allocated memory 
   	delete keyValuePairs;
   	
   }
   
   // Description: Returns the number of elements currently stored in the Dictionary.
   // Postcondition: This method does not change the Dictionary.
   //Time efficiency: O(1)
   unsigned int Dictionary::getElementCount() const{
   	
   	//Return elementCount in BST
   	return keyValuePairs -> getElementCount();
   	}
   
   // Description: Puts "newElement" (association of key-value) into the Dictionary.
   // Precondition: "newElement" does not already exist in the Dictionary.
   //               This is to say: no duplication allowed.
   // Exception: Throws the exception "UnableToInsertException" 
   //            when newElement cannot be inserted in the Dictionary.  
   // Exception: Throws the exception "ElementAlreadyExistsException" 
   //            if "newElement" already exists in the Dictionary.  
   void Dictionary::put(WordPair & newElement){
   	//Check for duplications
   	try{
   		//Attempt to search element in dictionary 
   		WordPair & duplicate = keyValuePairs -> retrieve(newElement);
   		//If element is found, throw duplicate element error 
   		throw ElementAlreadyExistsException();
   	}
   	//If we didn't found this element
   	catch(ElementDoesNotExistException& error){
   		
   		//Insert element into the dictionary
   		keyValuePairs -> insert(newElement);
   		return;
   	}
   	//If the dictionary is empty, insert element
   	catch(EmptyDataCollectionException& error){
   	
   		//Insert element into the dictionary
   		keyValuePairs -> insert(newElement);
   		return;
   		
   	}
   	
   }
 
   // Description: Gets "newElement" (i.e., the associated value of a given key) 
   //              from the Dictionary.
   // Precondition: Dictionary is not empty.
   // Exception: Throws the exception ElementDoesNotExistException
   //            if the key is not found in the Dictionary.
   // Exception: Throws the exception EmptyDataCollectionException if the Dictionary is empty.
   // Postcondition: This method does not change the Dictionary.
   WordPair & Dictionary::get(WordPair & targetElement) const{
   	
   	//Check if the dictionary is empty 
   	if(keyValuePairs -> getElementCount() == 0){
   		//throw empty dictionary exception
   		throw EmptyDataCollectionException();
   	}
   	//If the data collection is not empty, search for the element
   	else{
   		//If element is not found, retrieve method will throw element not exist exception
   		return keyValuePairs -> retrieve(targetElement);
   	
   	}
   
   }

   // Description: Prints the content of the Dictionary.
   // Precondition: Dictionary is not empty.
   // Exception: Throws the exception EmptyDataCollectionException if the Dictionary is empty.
   // Postcondition: This method does not change the Dictionary.
   void Dictionary::displayContent(void visit(WordPair &)) const{
	//Check if the dictionary is empty
	try {
		//Call travser in order function
		keyValuePairs -> traverseInOrder(visit);
	} catch(EmptyDataCollectionException& error){
		//Catch empty data collection from BST class and rethrow exception 
		throw EmptyDataCollectionException();
	}
   
   }
   
   
   
   
   
   
   
   
   
   
   
   

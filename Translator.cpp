/*
 * Translator.cpp
 * 
 * Description: Translates English words to another language using a dictionary.
 *              The dictionary is implemented as a binary search tree (BST).
 *
 * Author: Kunpeng (Andy) Zhang
 * Last Modification Date: March 10, 2024
 */
#include <iostream>
#include <fstream>
#include <string>
#include "Dictionary.h"
#include "WordPair.h"
#include "ElementAlreadyExistsException.h"
#include "ElementDoesNotExistException.h"
#include "EmptyDataCollectionException.h"
#include "UnableToInsertException.h"

using namespace std;

// Display function for WordPair objects
void display(WordPair& anElement) {
    cout << anElement;
}

int main(int argc, char *argv[]){
	//Create a dictionary 
	Dictionary myDictionary;
	//Create a variable to store file name
	string filename = "";
	//Create a variable to hold a line 
	string aLine = "";
	//Create a variable to hold English word
	string englishW = "";
	//Create a variable to hold translated word
	string translationW = "";
	//Specify the delimiter of data file
	string delimiter = ":";
	//Variable that store the position of delimiter
	size_t pos = 0;
	//Declare a word pair for the dictionary 
	WordPair translated;
	
	//If there's a file name on the command line 
	if(argc > 1){
		//assign the corresponding file name
		filename = argv[1];
		//open file
		ifstream data_file(filename);
		//If the file is not opened successfully, return -1 indicate failure
		 if (!data_file.is_open()) {
			// Indicates failure
			return -1; 
    		}
    		
    		
    		//Read each line from the data file
    		while(getline(data_file, aLine)){
    			//Find the position of delimiter and store into pos 
    			pos = aLine.find(delimiter);
    			//Find the first half of the string and store into English word
			englishW = aLine.substr(0, pos);
			//Find the second half of the string and store as translated word 
			translationW = aLine.substr(pos + delimiter.length());
			//Create a word pair with English word and translated word 
			WordPair aWordPair(englishW, translationW);
			//Attempt to insert the word pair into dictionary 
			try {
			    //put the word into dictionary 
			    myDictionary.put(aWordPair);
			} catch (const ElementAlreadyExistsException& e) {
			    //If we found a duplicated element, catch the corresponding error
			} catch (const UnableToInsertException& e) {
			    //If we are unable to insert due to other reason, catch the corresponding error
        }
    }
    //close the data file
    data_file.close();
  }
    //Read in a english word from user 
    while(cin >> englishW && !cin.eof()){
    	
    	// Check for termination command
        if (englishW == "exit") {
            cout << "Exiting the program." << endl;
            break;
        }
        
    	//If the user enter key word display 
    	//Check whether the user enter display key word
	if(englishW == "display"){
		try{
    			//Print all elements of dictionary in alphabetical order
    			myDictionary.displayContent(display);
    		} catch(EmptyDataCollectionException& error) {
    		//If dictionary is empty, throw exceptions
		}
	}
	else{
	    	//Attempt to search for user's input
	    	try{
	    		//Create a word pair using user's input
	    		WordPair user_word(englishW);
	    		//Search this word pair in dictionary 
	    		const WordPair &result = myDictionary.get(user_word);
	    		//Output the translation
	    		cout << result;
	    	} catch(EmptyDataCollectionException& error) {
    		//If dictionary is empty, throw exceptions
		}
	    	//If user input does not exist in dictionary, throw exception
	    	catch(ElementDoesNotExistException& error){
	    		cout << "***Not Found!***" << endl;
	    	}
    	}
    }
    return 0;
  }
	


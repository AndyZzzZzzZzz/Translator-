# Translator 

## Description

The Translator project is a C++ application that translates English words to another language using a dictionary. The dictionary is implemented as a binary search tree (BST) to efficiently manage and search for word pairs. This project includes various custom exceptions to handle errors gracefully.

## Table of Contents

- [Description](#description)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Files](#files)
- [Classes](#classes)
- [Exceptions](#exceptions)
- [Contributing](#contributing)
- [License](#license)

## Features

- Translate English words to another language.
- Efficiently manages word pairs using a BST.
- Custom exceptions for error handling.
- Command-line interface for interaction.
- Supports loading word pairs from a file.
- Display all word pairs in alphabetical order.

## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/YOUR_USERNAME/Translator.git
   cd Translator
   ```
2. Compile the project using the provided Makefile:
   ```bash
   make
   ```

## Usage
1.  Run the program with a data file:
   ```bash
  ./translate myDataFile.txt
  ```
2.  Interact with the program by entering English words to get their translations. Special commands:
   ```plaintext
  display: Show all word pairs in alphabetical order.
  exit: Terminate the program.
  ```

## Files

-  Translator.cpp: Main program file that handles user interaction and file input.
-  Dictionary.cpp / Dictionary.h: Dictionary class implemented using a BST.
-  BST.cpp / BST.h: Binary Search Tree implementation
-  BSTNode.cpp / BSTNode.h: Node class for BST.
-  WordPair.cpp / WordPair.h: Models an English word and its translation.
-  ElementAlreadyExistsException.h: Exception for duplicate elements.
-  ElementDoesNotExistException.h: Exception for non-existent elements.
-  EmptyDataCollectionException.cpp / EmptyDataCollectionException.h: Exception for empty collections.
-  UnableToInsertException.cpp / UnableToInsertException.h: Exception for insertion failures.
-  Makefile: Makefile for compiling the project.
-  myDataFile.txt: Sample data file with word pairs.




#include <iostream>
#include <fstream>
#include "AVLTree.h"
#include <string>
#include <time.h>
#include <ctime>

using namespace std;

int main(int argc, char* argv[]){

  clock_t start, end; //Started the timer.
  double duration;
  start = clock();
  
  AVLTree tree; //Created an object out of AVLTree so the functions can be called.
  
  char instruct; //Declared proper variables. Instruct will check the first letter in each line to call the proper function.
  int countInsert = 0; //Declared int variables that will keep track of the number of times the functions are needed.
  int countDelete = 0;
  int countRetrieve = 0;
  int counter = 0; //Int variable counter keeps track of the number of items in the doubly linked list. 
  string SSN2; //Defined two new string variables, one for stored SSN and another for first and last name seperate.
  string firstName, lastName, name;
  
  fstream input(argv[1]); //Uses fstream to read in the file found at index 1 of the command line array.
  
  while (!input.eof()) { //Created a while loop that will read all of the data on each line of the external file.
    if (!input) { //Breaks the loop if correct data is not inputed and an error message is displayed.  
      cout << "Error, Invalid File." << endl;
      return 0; 
  	}
	  
    input >> instruct >> SSN2 >> firstName >> lastName; //Inputed the data from external files into proper variables.
    name = firstName + " " + lastName; //Combines first and last name so it is stored together.	  
			
    if(instruct == 'i') { //If branch for insert function. Will run if first char in row is 'i'.
      if(tree.find(SSN2) == false) { //Calls the find function and runs the loop if false.
        counter++; //Changed the counters accordingly.
        countInsert++; 
        tree.insert(SSN2, name); //Called the function insert through tree object.	
      }	  
    }
	
    else if(instruct == 'd') { //Else if branch for remove function. Will run if first char in row is 'd'.
      if(tree.find(SSN2) == true) { //Calls the find function and runs the loop if true.
        counter--; //Changed the counters accordingly.
        countDelete++;
	      tree.deleteNode(SSN2); //Called the function deleteNode through object tree.
      }
	  }
    
    else if(instruct == 'r') { //Else if branch for retrieval action. Will run if first char in row is 'r'.
	    if(tree.find(SSN2) == true) //Calls the find function and runs the loop if true.
	      countRetrieve++; //If the search is true, then countRetrieve is increased by one.
      }
  }	
  AVLNode * root = tree.getRoot(); //Created a new AVLNode pointer called root that stores the root of the tree that is created.
  input.close(); // Closes the external file.
  
  cout << "The Number of Valid Insertation: " << countInsert << endl; //Printed out the proper information onto the screen.
  cout << "The Number of Valid Deletion: " << countDelete << endl;
  cout << "The Number of Valid Retrieval: " << countRetrieve << endl;
  cout << "The Height of the AVL Tree: " << tree.height(root) << endl; //Printed out the height of the tree from the root. 
  
  end = clock();
  duration = ( end - start ) / (double) CLOCKS_PER_SEC; //Ends the timer.
  cout <<"Time Elapsed: " << duration << '\n'; //Prints out the time onto the screen.
  
  tree.levelOrder(); //Called the level order function so the info can be printed out to the screen.
  
}

# AVL-Tree

This was a school project where an AVL Tree is implemented that is used to organize files containing Names and the Social Security numbers associated with them.
AVLNode.h, AVLNode.cpp, and AVLTree.h files were given to us and we were told to implement the AVLTree.cpp file as well as the AVLMain.cpp file. 

AVL tree is a Binary Search Tree that is also known as a BST. The values and data in this data structure are ordered. It is also balanced; meaning that the left subtree and right subtree have similar size. Thus, an insertion 

The complexity of searching, inserting, and deleting a node are O(log n) for an AVL Tree. 

The "Social Security" files contain data that looks like this:
i 355589543    John Doe
d 423594023    Jane Doe
r 240934900    Regina Phalange

The program will first parse in the first letter of a line. If the letter is
  - i : That means the social security number and the name after it need to be inserted into the tree.
  - d : That means the social security number and the name after it need to be deleter from the tree.
  - r : That means the social security number and the name after it need to be retrieved from the tree.

## How to run it:
The repository includes the files that have the Social Security numbers in them. Make sure to clone the repository and make sure all the files are in the same directory.
### To compile the code:
Type ``` g++ AVLNode.cpp AVLTree.cpp AVLMain.cpp -o main ``` in your terminal.
This will compile the code and will name your executable file "main".
### To run the executable:
Type ``` ./main "text file" ``` in your terminal. Replace "text file" with the file name that you want to run the code on. For example ``` ./main 250000-idr ```.
### The results should look like the following:
```
./main 250000-idr
The Number of Valid Insertation: 156536
The Number of Valid Deletion: 28338
The Number of Valid Retrieval: 18613
The Height of the AVL Tree: 19
Time Elapsed: 0.456Tree Size: 128198

./main 500000-idr
The Number of Valid Insertation: 312656
The Number of Valid Deletion: 56010
The Number of Valid Retrieval: 37360
The Height of the AVL Tree: 20
Time Elapsed: 0.974
Tree Size: 256646

./main 750000-idr
The Number of Valid Insertation: 468893
The Number of Valid Deletion: 84297
The Number of Valid Retrieval: 56129
The Height of the AVL Tree: 21
Time Elapsed: 1.559
Tree Size: 38459
```

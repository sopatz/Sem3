Programming assignment 2 for Operating Systems course at Kent State:

Banker's Algorithm Project

Code is in one C++ code file called "banker.cpp".

Input file with data is in a text file called "tableData.txt", but any text file with the right format (see readData function in banker.cpp) can be used to compute its safe sequence.

Compiled using "g++ banker.cpp", then running "./a.out".

Problems faced:

-The hardest part of this project was figuring out how to read data from an input file into a vector of vectors. I definitely did not do this the most efficient way possible, but it works for the example system given, but my program would not work for systems of different size, sadly.

-I used a lot of loops and it made the code hard to read for me while writing it. Remembering the scope of all my variables was tough.

-Figuring out what exactly "allocation", "max", and "available" are took a while to wrap my head around.



# 8puzzle solver (AKA. Taquin in French)

As the name implies, this AI project aims to solve the 8puzzle game! (AKA. taquin in French, hence the name of the program). 

This solver uses the Iterative Deepening A* algorithm, but an A* solution is also included in the main file (although the A* algorithm will run all of memory really fast if you try the more difficult puzzles).

## Quick start 
    
    make 
    ./taquin [input_file_name] ([output_file_name])  


Compile the program with make and pass it the file containing the a puzzle to solve. The first line of the file must contain only the size of the rows and columns, and all other lines must contain the rows of the puzzle, the numbers inside a same row being separated by whitespaces.

Optionally, a second argument with the name of the file to create and write the data into can be provided. If none is given, the solution will be printed to the standard output (the terminal).


## About

This project was originally a programming assignement in Java for a AI class, but the methods we used (asside from the actual A* algorithm) were different, including the implementation of IDA* and specially the way we evaluated if a board is solvable or not. I also wanted to try a different programming style and a different language. 

The 8puzzle folder contains many different puzzles provided by my teacher to test the program with.
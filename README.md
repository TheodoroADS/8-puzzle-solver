# 8puzzle solver (AKA. Taquin in French)

As the name implies, this AI project aims to solve the 8puzzle game! (AKA. taquin in French, hence the name of the program). 

This solver uses the Iterative Deepening A* algorithm, but an A* solution is also included in the main file (although the A* algorithm will run all of memory really fast if you try the more difficult puzzles).

## Quick start 

 ``` sh
    make
    ./taquin [input_file_name] ([output_file_name])  

```

Compile the program with make and pass it the file containing the a puzzle to solve. The first line of the file must contain only the size of the rows and columns, and all other lines must contain the rows of the puzzle, the numbers inside a same row being separated by whitespaces.

Optionally, a second argument with the name of the file to create and write the data into can be provided. If none is given, the solution will be printed to the standard output (the terminal).

By default, a version of the program that runs IDA* is built with the make command, but a target implementing the A* algorithm is also included in the make file. For instance: 


 ``` sh
    make # builds an executable implementing IDA* named taquin 
    make taquin_astar # builds an executable implementing A* named taquin_astar 
    make taquin_idastar # builds an executable implementing IDA* named taquin_idastar

```


## About

This project was originally a programming assignement in Java for a AI class, but the methods we used (asside from the actual A* algorithm) were different, including the implementation of IDA* and specially the way we evaluated if a board is solvable or not. I also wanted to try a different programming style and a different language. 

The 8puzzle folder contains many different puzzles provided by my teacher to test the program with.

This project uses a reusable "generic" priority that I implemented earlier which is available in [this repository](https://github.com/TheodoroADS/generic-priority-queue-in-c).

## References   

[The taquin (8 puzzle) game](https://en.wikipedia.org/wiki/15_puzzle)

[The A* algorithm](https://en.wikipedia.org/wiki/A*_search_algorithm)

[The IDA* algorithm](https://en.wikipedia.org/wiki/Iterative_deepening_A*)
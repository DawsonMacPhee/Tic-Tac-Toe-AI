A program that allows a user to play tic tac toe against a computer.

Files

    ttt1.c & ttt2.c
        Contains all functions required for the ai to make decisions
        
    ttt.h
        Contains function declarations for both ttt.c files
        
    show_node.c
        Displays a list nodes given on the command line - the input should be the index in hashtable
        
    count_nodes.c
        Counts the number of nodes that have been initialized
        
    alphatoe.c
        The main executable for playing a game of tic tac toe against the computer

Usage (make)

    all
        Compiles all executables and object files
        
    ttt1.o
        Compiles the functions in the ttt1 file into an object file
        
    ttt2.o
        Compiles the functions in the ttt2 file into an object file
        
    show_node.o
        Compiles show_node.c into an object file
        
    count_nodes.o
        Compiles count_nodes.c into an object file
        
    alphatoe.o
        Compiles alphatoe.c into an object file
        
    show_node
        Links required object files together into an executable called show_node
        
    count_nodes
        Links required object files together into an executable called count_nodes
        
    alphatoe
        Links required object files together into an executable called alphatoe

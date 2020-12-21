#ifndef __stdio_h_
#include <stdio.h>
#endif

#ifndef __ttt_h_
#include "ttt.h"
#endif

#ifndef __stdlib_h_
#include <stdlib.h>
#endif

// Prints the nodes listed as arguments on the command line
// Given arguments correspond to hash values in htables
int main(int argc, char *argv[]){
    init_boards();
    init_board(START_BOARD);
    join_graph(START_BOARD);
    compute_score();

    for(int i = 1; i < argc; i++){
        print_node(htable[atoi(argv[i])]);
    }
}
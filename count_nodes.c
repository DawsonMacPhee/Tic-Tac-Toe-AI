#ifndef __stdio_h_
#include <stdio.h>
#endif

#ifndef __ttt_h_
#include "ttt.h"
#endif

// Counts all the initialized nodes in htable
int main(int argc, char *argv[]){
    int count = 0;
    init_boards();
    init_board(START_BOARD);
    join_graph(START_BOARD);

    for(int i = 0; i < HSIZE; i++){
        if(htable[i].init == 1){
            count += 1;
        }
    }
    printf("%d\n", count);
}
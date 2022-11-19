#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "priority_queue.h"
#include "linked_list.h"
#include <assert.h>

#define PQ_INITIAL_CAP 100

#define DEBUG(message) printf(message "\n") ; fflush(stdout);


#if !defined STRATEGY_IDASTAR && !defined STRATEGY_ASTAR 

#define STRATEGY_IDASTAR

#endif

enum previous_dir{
    LEFT,
    RIGHT,
    UP,
    DOWN
};

typedef struct game_info_t {
    Board* intial_configuration;
    Board* solution;
    int solved;
    int nb_moves;
} game_info_t;


#ifdef STRATEGY_ASTAR


void add_children_to_priority_queue(Board* b, priority_queue* q){
    
    //left 
    if(b->holej >=1){

        Board* leftChild = Boardfrom(b, b->holei, b->holej, b->holei, b->holej - 1); 

        if(!equals(leftChild, b->parent)){
            priority_queue_add(q,leftChild);
        }else{
            deleteBoard(leftChild);
        }
    }
    //right
    if(b->holej <b->N - 1){

        Board* rightChild = Boardfrom(b, b->holei, b->holej, b->holei, b->holej + 1); 

        if(!equals(rightChild, b->parent)){
            priority_queue_add(q,rightChild);
        }else{
            deleteBoard(rightChild);
        }
    }

    //up
    if(b->holei >=1){

        Board* upperChild = Boardfrom(b, b->holei - 1, b->holej, b->holei, b->holej); 

        if(!equals(upperChild, b->parent)){
            priority_queue_add(q,upperChild);
        }else{
            deleteBoard(upperChild);
        }
    }

    //down
    if(b->holei < b->N - 1){

        Board* lowerChild = Boardfrom(b, b->holei + 1, b->holej, b->holei, b->holej); 

        if(!equals(lowerChild, b->parent)){
            priority_queue_add(q,lowerChild);
        }else{
            deleteBoard(lowerChild);
        }
    }

}


Board* Astar(Board* current, priority_queue* queue){


    if (isGoal(current)){
        printf("Found a solution! \n");
        fflush(stdout);
        return current;
    }

    add_children_to_priority_queue(current, queue);

    return Astar(priority_queue_poll(queue), queue);
}


game_info_t solve_game_astar(Board* initial_configuration){

    game_info_t gameInfo = {
        initial_configuration,
        NULL,
        0,
        0
    };

    printf("Lets start \n");
    fflush(stdout);

    priority_queue* queue = priority_queue_new(PQ_INITIAL_CAP, board_compare);

    gameInfo.solution = Astar(gameInfo.intial_configuration, queue);

    gameInfo.nb_moves = gameInfo.solution->depth;

    priority_queue_delete(queue);

    return gameInfo;
}


#endif


#ifdef STRATEGY_IDASTAR

int idastar(Board* b, int limit , ll* stack, char* solved_ptr){


    if (isGoal(b)){
        *solved_ptr = 1;
        return b->depth;
    }

    int min = limit;

  //left 
    if(b->holej >=1){

        Board* leftChild = Boardfrom(b, b->holei, b->holej, b->holei, b->holej - 1); 

        if(!equals(leftChild, b->parent)){
            
            int cost = manhattan(leftChild) + leftChild->depth;

            if (cost <= limit){

                // printf("cost : %d \n", cost);

                ll_add(stack, leftChild);
                cost = idastar(leftChild, min, stack, solved_ptr);

                if (*solved_ptr){
                    return cost;
                }

                Board* last = ll_pop(stack);
                assert(last);
                deleteBoard(last);

                if (cost < min ) min = cost;

            }else{
                deleteBoard(leftChild);
            }

        }else{
            deleteBoard(leftChild);
        }
    }

    //right
    if(b->holej <b->N - 1){

        Board* rightChild = Boardfrom(b, b->holei, b->holej, b->holei, b->holej + 1); 

        if(!equals(rightChild, b->parent)){

            int cost = manhattan(rightChild) + rightChild->depth; 

            if (cost <= limit){


                ll_add(stack, rightChild);
                cost = idastar(rightChild, limit, stack, solved_ptr);

                if (*solved_ptr){
                    return cost;
                }

                Board* last = ll_pop(stack);
                assert(last);
                deleteBoard(last);

                if (cost < min ) min = cost;
            }else{
                deleteBoard(rightChild);
            }
            
        }else{
            deleteBoard(rightChild);
        }
        
    }

    //up
    if(b->holei >=1){

        Board* upperChild = Boardfrom(b, b->holei - 1, b->holej, b->holei, b->holej); 

        if(!equals(upperChild, b->parent)){
            
            int cost = manhattan(upperChild) + upperChild->depth; 

            if (cost <= limit){

                // printf("cost : %d \n", cost);


                ll_add(stack, upperChild);
                cost = idastar(upperChild, limit, stack, solved_ptr);

                if (*solved_ptr){
                    return cost;
                }

                Board* last = ll_pop(stack);
                assert(last);
                deleteBoard(last);

                if (cost < min ) min = cost;
            }else{
                deleteBoard(upperChild);
            }

        }else{
            deleteBoard(upperChild);
        }
    }

    //down
    if(b->holei < b->N - 1){

        Board* lowerChild = Boardfrom(b, b->holei + 1, b->holej, b->holei, b->holej); 

        if(!equals(lowerChild, b->parent)){

            int cost = manhattan(lowerChild) + lowerChild->depth; 

            if (cost <= limit){

                // printf("cost : %d \n", cost);


                ll_add(stack, lowerChild);
                cost = idastar(lowerChild, limit, stack,solved_ptr);

                if (*solved_ptr){
                    return cost;
                }

                Board* last = ll_pop(stack);
                assert(last);
                deleteBoard(last);

                if (cost < min ) min = cost;
            }else{
                deleteBoard(lowerChild);
            }

        }else{
            deleteBoard(lowerChild);
        }
    }

    return min;


}



game_info_t solve_game_idastar(Board* initial_configuration){


    game_info_t gameInfo = {
        initial_configuration,
        NULL,
        0,
        0
    };

    int limit = manhattan(initial_configuration) + 2;
    Board* solution = NULL;

    ll stack = NULL;
    char solved = 0;

    while(!solved){
        // printf("limit : %d \n", limit);
        ll_add(&stack, initial_configuration);
        limit = idastar(initial_configuration, limit, &stack, &solved);
        printf("solved : %hhd \n", solved);
        fflush(stdout);

    }

    gameInfo.solution = ll_pop(&stack);
    gameInfo.nb_moves = gameInfo.solution->depth;

    return gameInfo;

}

#endif

void reconstruct_path(Board* finished_game_board, FILE* file){

    Board* current = finished_game_board;

    //initializing the linked list
    ll solution;
    solution = NULL;

    while(has_parent(current)){
        ll_add(&solution, current);
        current = current->parent;
    }
    
    fprintf(file, "Solution : \n");

    while(current){
        board_print_to(current,file);
        current = ll_pop(&solution);
    }

    
    fclose(file);
}


Board* readFromFile(char* filename){

    FILE* file;
    unsigned char N;
    unsigned int num;
    unsigned char* board;


    if ((file = fopen(filename, "r")) == (FILE*) NULL){
        fprintf(stderr , "Could not open file \n");
        exit(1);
    }

    if (!fscanf(file, "%hhd \n", &N)){
        fprintf(stderr, "Could not recognize board dimension \n");
        exit(1);
    }

    board = malloc(sizeof(unsigned char) * N*N);

    for (unsigned int i = 0; i < N*N; i++)
    {
        
        if (!fscanf(file, "%d", &num)){
            fprintf(stderr, "Error during scanning \n");
            exit(1);
        }

        board[i] = (unsigned char) num;
    }
    

    fclose(file);

    return newBoard(N, board);
}




int main(int argc, char** argv){

    FILE* file; //file to write the solution

    if (argc > 3 || argc == 1){
        printf("Usage: %s [puzzle file name] (output_file_name)\n", argv[0]);
        printf("The output file name is optionnal. If none is provided, the solution will be printed to the screen. \n");
        exit(1);
    }else if(argc == 3){

        if ((file = fopen(argv[2], "w")) == (FILE*) NULL){
        fprintf(stderr , "Could not open file to write solution \n");
        exit(1);
        }

    }else{
        file = stdout;
    }

    printf("Opening file and scanning input board \n");

    Board* b = readFromFile(argv[1]);


    if (board_is_solvable(b)){

        DEBUG("Beginning to solve board \n");

        #ifdef STRATEGY_ASTAR 

        game_info_t solved = solve_game_astar(b);
        
        #endif
        
        #ifdef STRATEGY_IDASTAR

        game_info_t solved = solve_game_idastar(b);

        #endif


        printf("Game solved in %d moves \n", solved.nb_moves);     

        reconstruct_path(solved.solution, file);

    }else{
        printf("This board is unsolvable! \n");
    }

    return 0;
}
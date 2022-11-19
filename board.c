#include <stdio.h>
#include <malloc.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "board.h"
// #include "priority_queue.h" 

static inline char get(Board* b, unsigned char i, unsigned char j){
    return b->board[i*b->N + j];
}

static inline void set(Board* b, unsigned char i, unsigned char j, unsigned char val){
    b->board[i*b->N + j] = val;
}


Board* newBoard(unsigned char N, unsigned char board[]){
    Board* b = (Board *) malloc(sizeof(Board));
    b->N = N;
    //allocating 2D array dynamically
    b->board = (unsigned char *) malloc(sizeof(unsigned char)*N*N);

    for (unsigned char i = 0; i< N ; i++){
        for (unsigned char j = 0; j<N ; j++){
            set(b, i,j,board[i*N +j]);
        }
    }

    for (unsigned char i = 0; i< N ; i++){
        for (unsigned char j = 0; j<N ; j++){
            if(get(b, i,j) == 0){
                b->holei = i;
                b->holej = j;
            }
        }
    }

    b->depth = 0;
    b->parent = NULL;

    return b;
}


static void resolve_holepos(Board* b){

    for (size_t i = 0; i < b->N; i++)
    {
        for (size_t j = 0; j < b->N; j++)
        {
            if (get(b,i , j) == 0){
                b->holei = i;
                b->holej = j;
                return;
            }
        }
        
    }
    
    //if we get here hten there is no hole!

    fprintf(stderr, "Invalid format in one of the boards: there is no hole. Board in quetion: \n");
    render(b);
    exit(1);

}

Board * Boardfrom(Board * b , unsigned char swapi1,unsigned char swapj1, unsigned char swapi2,unsigned char swapj2 ){
    Board * newb = newBoard(b->N,b->board);
    unsigned char temp = get(newb, swapi1, swapj1);
    set(newb, swapi1,swapj1, get(newb,swapi2,swapj2));
    set(newb, swapi2, swapj2 , temp);
    newb->depth = b->depth + 1;
    newb->parent = b;
    resolve_holepos(newb);
    return newb;
}

void deleteBoard(Board* b){
    
    free(b->board);

    free(b);
}


char has_parent(Board* b){
    return b->parent != NULL;
}

char isGoal(Board * b){

    char seq = 1;
    char N = b-> N;
    for (char i = 0; i< N ; i++){
        for (char j = 0; j<N && seq != N*N; j++){
            if (get(b, i ,j) != seq){
                return 0;
            }
            seq++;
        }
    }

    return 1;
}

char manhattan(Board* b){
    char manhattan = 0;
    char N = b->N;

    for(char i = 0; i < N ; i++){
        for(char j = 0; j < N; j++){

            char num = get(b, i, j) - 1;
            
            if(num >= 0){

                char correctj = num%(N);
                char correcti = (num-correctj)/N;

                manhattan += abs(correcti - i) + abs(correctj - j);
            }else{
                char correct = N-1;

                manhattan += abs(correct - i) + abs(correct - j);
            }
                
        }
    } 
    
    return manhattan;
}

char equals(Board* b1 , Board * b2){

    if( !b1 || !b2) return 0; //b1 or b2 can be null

    if(b1->N != b2->N) return 0;

    for(unsigned char i = 0; i < b1->N; i++){
        for(unsigned char j = 0; j < b1->N; j++){
            if (get(b1, i, j) != get(b2,i,j)){
                return 0;
            }
        }
    } 

    return 1;
}

double board_compare(Board* b1 , Board* b2){
    return manhattan(b1) + b1->depth - manhattan(b2) - b2->depth;
}

static inline char same_hole_pos(Board* b1,Board* b2 ){
    return b1->holei == b2->holei || b1->holej == b2->holej;
}


void board_print_to(Board* b, FILE* stream ){

    fprintf( stream,"N:%d\n", b->N);
    for(unsigned char i = 0; i < b->N ; i++){
        for(unsigned char j = 0; j< b->N -1; j++){
            fprintf(stream ,"%d|", get(b, i,j));
        }
        fprintf(stream ,"%d \n", get(b,i,b->N-1));
        
    }
}

char board_is_solvable(Board* b){

    /*
        This procedure checks if the board is solvable or not. 
        It has been proven that if the total number of permutations needed (without following the rules of the game)
        to arrange the numbers of the board in order is of a different parity then the distance of the hole to its
        place, then the board is unsolvable. The procedure then computes this two numbers to make its decision
    */


    //computing number of permutations needed for arranging the numbers in order
    unsigned char N2 = b->N*b->N;

    unsigned char* values = malloc(sizeof(char) * N2);

    for (unsigned char i = 0; i < N2; i++)
    {   
        values[i] = b->board[i];
    }

    unsigned char absolute_hole_position = b->holei * b->N + b->holej;

    //the hole should be in the last position, so we assign it a value greater than all others in the array
    values[absolute_hole_position] = N2;
    
    // we are going to do a bubble sort and count the total number of permutations
    unsigned char nb_permutations = 0;
    unsigned char finished = 0;

    for(unsigned char i = N2 ; i>= 0 && !finished; i-- ){
    finished = 1;
    for(unsigned char j = 0 ; j < i -1 ; j++){
        
        if(values[j+1] < values[j]){
            finished = 0;
            unsigned char temp = values[j];
            values[j] = values[j+1];
            values[j+1] = temp;
            nb_permutations++;
            }
        }
    }   
      

    free(values);
    
    //distance of the hole from its right position
    unsigned char dist_hole = 2*(b->N -1) - b->holei - b->holej;

    printf("Total number of permutations: %d \n", nb_permutations);
    printf("Hole distance to goal: %d \n", dist_hole);

    if(dist_hole % 2 == 0){
        if(nb_permutations %2 == 0){
            return 1;
        }else{
            return 0;
        }
    }else{
        if (nb_permutations %2 != 0){
            return 1;
        }else{
            return 0;
        }
    }


}

void render(Board* b){
    board_print_to(b, stdout);
}

/* This main helped test the board funcions
int main(){

    int bob[9] = {
        3,4,1,
        5,7,0,
        9,2,8
    };

    int nice[9] = {
        1,2,3,
        4,5,6,
        7,8,0
    };

    Board * goal = newBoard(3,nice);
    render(goal);
    printf("%d\n", isGoal(goal));
    

    Board* board = newBoard(3, bob);
    render(board);
    printf("%d\n", isGoal(board));

    Board * brother = Boardfrom(board, 0,0,1,1);
    render(brother);
    printf("manhattan: %d\n", manhattan(brother));
    printf("manhattan goal: %d\n", manhattan(goal));

    deleteBoard(goal);
    deleteBoard(board);
    deleteBoard(brother);
    return 0;
}*/
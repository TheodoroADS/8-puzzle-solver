#pragma once
#include "board.h"

//lifo structure to reverse the order of the solution
typedef struct node{
    Board * b;
   struct node* next;
} node;


typedef node* ll;


void ll_add(ll* ll,Board* b);

Board* ll_pop(ll* ll);


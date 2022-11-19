#include "linked_list.h"
#include <stdlib.h>
#include "board.h"
#include <assert.h>


void ll_add(ll* li,Board* b){

    assert(li); // this procedure must not be called with a null pointer!!

    node* new = malloc(sizeof(node));

    new->b = b;

    if(*li){ 

        new->next = *li;
        *li = new;

    }else{
        new->next = NULL;
        *li = new;
    }

}



Board* ll_pop(ll* li){

    assert(li); //idem 

    if (!(*li)){
        return NULL;
    }

    node* front = *li;

    *li = front->next;

    Board* val = front->b;

    free(front);

    return val;
}

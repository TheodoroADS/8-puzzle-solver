CC=gcc
CFLAGS=-Wall -Wextra

ifeq ($(OS),Windows_NT) 
RM = del
else
RM= rm
endif

# TODO use makefile features to make better compile rules

taquin: taquin.o board.o priority_queue.o linked_list.o
	$(CC) taquin.o board.o priority_queue.o linked_list.o -o taquin

taquin_astar : taquin_astar.o board.o priority_queue.o linked_list.o
	$(CC) taquin_astar.o board.o priority_queue.o linked_list.o -o taquin_astar

taquin_idastar : taquin_idastar.o board.o priority_queue.o linked_list.o
	$(CC) taquin_idastar.o board.o priority_queue.o linked_list.o -o taquin_idastar


taquin.o: taquin.c board.h priority_queue.h linked_list.h
	$(CC) $(CFLAGS) -c taquin.c -DT=Board*

taquin_astar.o: taquin.c board.h priority_queue.h linked_list.h
	$(CC) $(CFLAGS) -c taquin.c -DT=Board* -DSTRATEGY_ASTAR -o taquin_astar.o

taquin_idastar.o: taquin.c board.h priority_queue.h linked_list.h
	$(CC) $(CFLAGS) -c taquin.c -DT=Board* -DSTRATEGY_IDASTAR -o taquin_idastar.o


board.o: board.c board.h 
	$(CC) $(CFLAGS) -c board.c 

priority_queue.o : priority_queue.c priority_queue.h board.h
	$(CC) $(CFLAGS) -c priority_queue.c -DT=Board*

linked_list.o: linked_list.c linked_list.h board.h
	$(CC) $(CFLAGS) -c linked_list.c


clean: 
	$(RM) *.o
	$(RM) *.exe
	$(RM) *.gch
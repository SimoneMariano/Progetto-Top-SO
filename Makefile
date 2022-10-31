all: MyTop clean

MyTop: main.o stat_manager.o process_list.o utils.o mergesort.o linked_list.o src/utils.h src/stat_manager.h src/mergesort.h src/process_list.h src/linked_list.h subsystem
	gcc -g -o MyTop main.o stat_manager.o process_list.o utils.o linked_list.o mergesort.o

main.o: main.c src/utils.h src/stat_manager.h src/process_list.h src/linked_list.h
	gcc -c main.c

utils.o: src/utils.c src/utils.h src/linked_list.h
	gcc -c src/utils.c

stat_manager.o: src/stat_manager.c src/utils.h src/process_list.h
	gcc -c src/stat_manager.c

process_list.o: src/process_list.c src/utils.h src/process_list.h src/linked_list.h src/mergesort.h
	gcc -c src/process_list.c

linked_list.o: src/linked_list.c src/utils.h src/linked_list.h src/mergesort.h
	gcc -c src/linked_list.c

mergesort.o: src/mergesort.c src/linked_list.h src/mergesort.h
	gcc -c src/mergesort.c

subsystem:
	@cd function && $(MAKE)

clean:
	rm *.o

cleanall: 
	rm *.o MyTop
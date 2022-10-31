all: processLauncher clean

processLauncher: main_process.o process_list.o linked_list.o utils.o mergesort.o ../src/linked_list.h ../src/mergesort.h ../src/utils.h ../src/process_list.h
	gcc -g -o processLauncher main_process.o process_list.o utils.o linked_list.o mergesort.o

main_process.o: main_process.c ../src/process_list.h ../src/linked_list.h ../src/mergesort.h
	gcc -c main_process.c

utils.o: ../src/utils.c ../src/utils.h  ../src/linked_list.h
	gcc -c ../src/utils.c

process_list.o: ../src/process_list.c ../src/utils.h ../src/process_list.h ../src/linked_list.h ../src/mergesort.h
	gcc -c ../src/process_list.c

linked_list.o: ../src/linked_list.c ../src/linked_list.h ../src/utils.h
	gcc -c ../src/linked_list.c

mergesort.o: ../src/mergesort.c ../src/linked_list.h ../src/mergesort.h
	gcc -c ../src/mergesort.c

clean:
	rm *.o

cleanall: 
	rm *.o processLauncher
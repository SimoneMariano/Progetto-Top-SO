all: processLauncher clean

processLauncher: main_process.o process_list.o linked_list.o utils.o fifo_utils.o ../src/linked_list.h ../src/fifo_utils.h ../src/utils.h ../src/process_list.h
	gcc -g -o processLauncher main_process.o process_list.o utils.o fifo_utils.o linked_list.o

main_process.o: main_process.c ../src/process_list.h ../src/linked_list.h
	gcc -c main_process.c

fifo_utils.o: ../src/fifo_utils.c ../src/fifo_utils.h ../src/utils.h
	gcc -c ../src/fifo_utils.c

utils.o: ../src/utils.c ../src/utils.h  ../src/linked_list.h
	gcc -c ../src/utils.c

process_list.o: ../src/process_list.c ../src/fifo_utils.h ../src/utils.h ../src/process_list.h ../src/linked_list.h
	gcc -c ../src/process_list.c

linked_list.o: ../src/linked_list.c ../src/linked_list.h ../src/utils.h
	gcc -c ../src/linked_list.c

clean:
	rm *.o

cleanall: 
	rm *.o processLauncher
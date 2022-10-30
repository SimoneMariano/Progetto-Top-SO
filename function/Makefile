all: processLauncher clean

processLauncher: main_process.o stat_manager.o process_list.o utils.o fifo_utils.o ../src/fifo_utils.h ../src/utils.h ../src/stat_manager.h ../src/process_list.h
	gcc -o processLauncher main_process.o stat_manager.o process_list.o utils.o fifo_utils.o

main_process.o: main_process.c ../src/process_list.h
	gcc -c main_process.c

fifo_utils.o: ../src/fifo_utils.c ../src/fifo_utils.h ../src/utils.h
	gcc -c ../src/fifo_utils.c

utils.o: ../src/utils.c ../src/utils.h
	gcc -c ../src/utils.c

stat_manager.o: ../src/stat_manager.c ../src/fifo_utils.h ../src/utils.h ../src/process_list.h
	gcc -c ../src/stat_manager.c

process_list.o: ../src/process_list.c ../src/fifo_utils.h ../src/utils.h ../src/process_list.h
	gcc -c ../src/process_list.c

clean:
	rm *.o

cleanall: 
	rm *.o processLauncher
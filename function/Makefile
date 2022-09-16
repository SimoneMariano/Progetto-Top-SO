
processLauncher: main_process.o ../src/process_list.h ../src/stat_manager.h
	gcc -o processLauncher main_process.o ../src/process_list.h ../src/stat_manager.h -lrt

main_process.o: ../src/stat_manager.c ../src/process_list.c ../src/utils.c ../src/fifo_utils.c ../src/process_list.h ../src/stat_manager.h ../src/process_list.h ../src/utils.h ../src/fifo_utils.h
	gcc -c main_process.c ../src/process_list.c ../src/stat_manager.c ../src/process_list.c ../src/utils.c ../src/fifo_utils.c -lrt

clean: 
	rm *.o processLauncher
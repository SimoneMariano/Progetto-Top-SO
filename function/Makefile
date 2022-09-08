
processLauncher: main_process.o processHandler.h statHandler.h
	gcc -o processLauncher main_process.o processHandler.h statHandler.h

main_process.o: main_process.c processHandler.h statHandler.h
	gcc -c main_process.c

clean: 
	rm *.o processLauncher
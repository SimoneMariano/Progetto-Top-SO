MyTop: main.o subsystem
	gcc -o MyTop main.o

main.o: main.c
	gcc -c main.c

subsystem:
	@cd function && $(MAKE)

clean: 
	rm *.o MyTop

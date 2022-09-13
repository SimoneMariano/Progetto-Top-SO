MyTop: main.o subsystem
	gcc -o MyTop main.o -lrt

main.o: main.c
	gcc -c main.c -lrt

subsystem:
	@cd function && $(MAKE)

clean: 
	rm *.o MyTop

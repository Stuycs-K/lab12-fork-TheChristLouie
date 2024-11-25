.PHONY: clean compile run
notDefault:
	@echo "No arguments runs the first recipe no matter what you call it."
compile: forkbomb.o main.o
	@gcc -w -o target forkbomb.o main.o -lm
main.o: main.c forkbomb.h
	@gcc -w -c main.c
forkbomb.o: forkbomb.c forkbomb.h
	@gcc -w -c forkbomb.c -lm
run: target
	@./target
clean:
	@rm -f *.o
	@rm -f target
	@rm -f output.txt
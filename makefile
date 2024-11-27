.PHONY: clean compile run
notDefault:
	@echo "No arguments runs the first recipe no matter what you call it."
compile: forkbomb.o main.o
	@gcc -w -o a.out forkbomb.o main.o -lm
main.o: main.c forkbomb.h
	@gcc -w -c main.c
forkbomb.o: forkbomb.c forkbomb.h
	@gcc -w -c forkbomb.c -lm
run: a.out
	@./a.out
clean:
	@rm -f *.o
	@rm -f a.out
	@rm -f output.txt
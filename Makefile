CC=gcc
FLAGS= -g

measure-speed: measure-speed.c cat-stdlib cat-syscall
	$(CC) $(FLAGS) -o measure-speed measure-speed.c

cat-stdlib: cat-stdlib.c
	$(CC) $(FLAGS) -o cat-stdlib cat-stdlib.c

cat-syscall: cat-syscall.c
	$(CC) $(FLAGS) -o cat-syscall cat-syscall.c

.PHONY: clean
clean:
	rm cat-stdlib cat-syscall measure-speed

all: turing.c
	make clean
	make turing

clean:
	if [ -a turing ]; then rm turing; fi;

turing: turing.c
	gcc -o turing turing.c
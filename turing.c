#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <signal.h>

struct state {
	signed char move0; //-1 or 1 upon seeing a 0
	unsigned char write0; //write 0 or 1 upon seeing a 0
	unsigned char next0; //next state index upon seeing a 0

	signed char move1;
	unsigned char write1;
	unsigned char next1;
};

int writeFile(unsigned char * tape, unsigned long steps, 
			unsigned int tapepos, char tapeind, unsigned char state, 
			unsigned int minTape, unsigned char minInd,
			unsigned int maxTape, unsigned char maxInd,
			unsigned long * tapestep, unsigned long * tapelength, unsigned int savei) {
	char filename[25];
	sprintf(filename, "%lu.txt", steps);
	FILE * fp = fopen(filename,"w+");
	fprintf(fp, "Iterations: %lu\n\nCurrent Position: Char %u Index %hd\nCurrent State: %hu\n\nLeft Tape End: Char %u Index %hu\nRight Tape End: Char %u Index %hu\n\n\n",
		steps, tapepos, tapeind, state, minTape, minInd, maxTape, maxInd);
	int i;
	for(i=minTape; i<=maxTape; i++) {
		fprintf(fp, "%x ", tape[i] & 0xff);
	}
	fclose(fp);

	fp = fopen("lengths.txt","w+");
	for(i=0; i<savei; i++) {
		fprintf(fp, "%lu\t%lu\n", tapestep[i], tapelength[i]);
	}
	fclose(fp);
	return 0;
}

int sigintBreak;
void handle_sigint(int sig) {
	sigintBreak = 1;
	return;
}

int main() {
	/* BB(3)
	const unsigned char MACHINESIZE = 3; //HALT = 3
	struct state machine[MACHINESIZE];

	machine[0].move0 = 1;
	machine[0].write0 = 1;
	machine[0].next0 = 1;
	machine[0].move1 = 0; //not used
	machine[0].write1 = 0; //not used
	machine[0].next1 = 3; //halt

	machine[1].move0 = -1;
	machine[1].write0 = 1;
	machine[1].next0 = 1;
	machine[1].move1 = 1;
	machine[1].write1 = 0;
	machine[1].next1 = 2;

	machine[2].move0 = -1;
	machine[2].write0 = 1;
	machine[2].next0 = 2;
	machine[2].move1 = -1;
	machine[2].write1 = 1;
	machine[2].next1 = 0;
	*/

	/* BB(4)
	const unsigned char MACHINESIZE = 4; //HALT = 4
	struct state machine[MACHINESIZE];

	machine[0].move0 = 1;
	machine[0].write0 = 1;
	machine[0].next0 = 1;
	machine[0].move1 = -1;
	machine[0].write1 = 1;
	machine[0].next1 = 1;

	machine[1].move0 = -1;
	machine[1].write0 = 1;
	machine[1].next0 = 0;
	machine[1].move1 = -1;
	machine[1].write1 = 0;
	machine[1].next1 = 2;

	machine[2].move0 = 0; //not used
	machine[2].write0 = 0; //not used
	machine[2].next0 = 4; //halt
	machine[2].move1 = -1;
	machine[2].write1 = 1;
	machine[2].next1 = 3;

	machine[3].move0 = 1;
	machine[3].write0 = 1;
	machine[3].next0 = 3;
	machine[3].move1 = 1;
	machine[3].write1 = 0;
	machine[3].next1 = 0;
	*/


	const unsigned char MACHINESIZE = 5; //HALT = 5
	struct state machine[MACHINESIZE];

	//BB5?
	/*
	machine[0].move0 = 1;
	machine[0].write0 = 1;
	machine[0].next0 = 1;
	machine[0].move1 = -1;
	machine[0].write1 = 1;
	machine[0].next1 = 2;

	machine[1].move0 = 1;
	machine[1].write0 = 1;
	machine[1].next0 = 2;
	machine[1].move1 = 1;
	machine[1].write1 = 1;
	machine[1].next1 = 1;

	machine[2].move0 = 1;
	machine[2].write0 = 1; 
	machine[2].next0 = 3;
	machine[2].move1 = -1;
	machine[2].write1 = 0;
	machine[2].next1 = 4;

	machine[3].move0 = -1;
	machine[3].write0 = 1;
	machine[3].next0 = 0;
	machine[3].move1 = -1;
	machine[3].write1 = 1;
	machine[3].next1 = 3;

	machine[4].move0 = 0; //not used
	machine[4].write0 = 0; //not used
	machine[4].next0 = 5; //halt
	machine[4].move1 = -1;
	machine[4].write1 = 0;
	machine[4].next1 = 0;
	//*/

	//HNR#1:
	// A: 1,<,C/1,<,E
	// B: 1,<,@/1,<,D
	// C: 1,>,D/0,<,D
	// D: 1,<,A/1,>,E
	// E: 0,<,B/0,>,C
	///*
	machine[0].move0 = -1;
	machine[0].write0 = 1;
	machine[0].next0 = 2;
	machine[0].move1 = -1;
	machine[0].write1 = 1;
	machine[0].next1 = 4;

	machine[1].move0 = -1;
	machine[1].write0 = 1;
	machine[1].next0 = 5;
	machine[1].move1 = -1;
	machine[1].write1 = 1;
	machine[1].next1 = 3;

	machine[2].move0 = 1;
	machine[2].write0 = 1; 
	machine[2].next0 = 3;
	machine[2].move1 = -1;
	machine[2].write1 = 0;
	machine[2].next1 = 3;

	machine[3].move0 = -1;
	machine[3].write0 = 1;
	machine[3].next0 = 0;
	machine[3].move1 = 1;
	machine[3].write1 = 1;
	machine[3].next1 = 4;

	machine[4].move0 = -1;
	machine[4].write0 = 0;
	machine[4].next0 = 1;
	machine[4].move1 = 1;
	machine[4].write1 = 0;
	machine[4].next1 = 2;
	//*/

	//HNR#16:
	// A: 1,<,B/1,<,@
	// B: 0,>,C/1,<,D
	// C: 1,>,D/1,>,C
	// D: 1,<,E/0,<,E
	// E: 0,<,A/0,>,B
	/*
	machine[0].move0 = -1;
	machine[0].write0 = 1;
	machine[0].next0 = 1;
	machine[0].move1 = -1;
	machine[0].write1 = 1;
	machine[0].next1 = 5;

	machine[1].move0 = 1;
	machine[1].write0 = 0;
	machine[1].next0 = 2;
	machine[1].move1 = -1;
	machine[1].write1 = 1;
	machine[1].next1 = 3;

	machine[2].move0 = 1;
	machine[2].write0 = 1; 
	machine[2].next0 = 3;
	machine[2].move1 = 1;
	machine[2].write1 = 1;
	machine[2].next1 = 2;

	machine[3].move0 = -1;
	machine[3].write0 = 1;
	machine[3].next0 = 4;
	machine[3].move1 = -1;
	machine[3].write1 = 0;
	machine[3].next1 = 4;

	machine[4].move0 = -1;
	machine[4].write0 = 0;
	machine[4].next0 = 0;
	machine[4].move1 = 1;
	machine[4].write1 = 0;
	machine[4].next1 = 1;
	//*/

	//HNR#19:
	// A: 1,<,B/1,<,@
	// B: 0,<,C/0,<,B
	// C: 1,>,C/0,>,D
	// D: 1,<,A/0,>,E
	// E: 0,>,A/0,>,E
	/*
	machine[0].move0 = -1;
	machine[0].write0 = 1;
	machine[0].next0 = 1;
	machine[0].move1 = -1;
	machine[0].write1 = 1;
	machine[0].next1 = 5;

	machine[1].move0 = -1;
	machine[1].write0 = 0;
	machine[1].next0 = 2;
	machine[1].move1 = -1;
	machine[1].write1 = 0;
	machine[1].next1 = 1;

	machine[2].move0 = 1;
	machine[2].write0 = 1; 
	machine[2].next0 = 2;
	machine[2].move1 = 1;
	machine[2].write1 = 0;
	machine[2].next1 = 3;

	machine[3].move0 = -1;
	machine[3].write0 = 1;
	machine[3].next0 = 0;
	machine[3].move1 = 1;
	machine[3].write1 = 0;
	machine[3].next1 = 4;

	machine[4].move0 = 1;
	machine[4].write0 = 0;
	machine[4].next0 = 0;
	machine[4].move1 = 1;
	machine[4].write1 = 0;
	machine[4].next1 = 4;
	//*/

	//HNR#20:
	// A: 1,<,B/1,<,@
	// B: 0,<,C/1,<,D
	// C: 0,>,D/1,<,C
	// D: 1,>,E/0,<,A
	// E: 1,<,A/0,>,E
	/*	
	machine[0].move0 = -1;
	machine[0].write0 = 1;
	machine[0].next0 = 1;
	machine[0].move1 = -1;
	machine[0].write1 = 1;
	machine[0].next1 = 5;


	machine[1].move0 = -1;
	machine[1].write0 = 0;
	machine[1].next0 = 2;
	machine[1].move1 = -1;
	machine[1].write1 = 1;
	machine[1].next1 = 3;


	machine[2].move0 = 1;
	machine[2].write0 = 0;
	machine[2].next0 = 3;
	machine[2].move1 = -1;
	machine[2].write1 = 1;
	machine[2].next1 = 2;


	machine[3].move0 = 1;
	machine[3].write0 = 1;
	machine[3].next0 = 4;
	machine[3].move1 = -1;
	machine[3].write1 = 0;
	machine[3].next1 = 0;


	machine[4].move0 = -1;
	machine[4].write0 = 1;
	machine[4].next0 = 0;
	machine[4].move1 = 1;
	machine[4].write1 = 0;
	machine[4].next1 = 4;
	//*/

	//37?
	// A: 1,<,C/0,>,B
	// B: 1,>,C/1,<,@
	// C: 0,<,D/0,>,D
	// D: 1,>,A/0,<,E
	// E: 1,<,D/1,<,E
	/*
	machine[0].move0 = -1;
	machine[0].write0 = 1;
	machine[0].next0 = 2;
	machine[0].move1 = 1;
	machine[0].write1 = 0;
	machine[0].next1 = 1;


	machine[1].move0 = 1;
	machine[1].write0 = 1;
	machine[1].next0 = 2;
	machine[1].move1 = -1;
	machine[1].write1 = 1;
	machine[1].next1 = 5;


	machine[2].move0 = -1;
	machine[2].write0 = 0;
	machine[2].next0 = 3;
	machine[2].move1 = 1;
	machine[2].write1 = 0;
	machine[2].next1 = 3;


	machine[3].move0 = 1;
	machine[3].write0 = 1;
	machine[3].next0 = 0;
	machine[3].move1 = -1;
	machine[3].write1 = 0;
	machine[3].next1 = 4;

	machine[4].move0 = -1;
	machine[4].write0 = 1;
	machine[4].next0 = 3;
	machine[4].move1 = -1;
	machine[4].write1 = 1;
	machine[4].next1 = 4;
	//*/

	const unsigned int TAPESIZE = 8000000;
	unsigned int tapepos = TAPESIZE/2;
	unsigned int minTape = tapepos; //left bound (char) on tape used
	unsigned int maxTape = tapepos; //right
	char tapeind = 7;
	unsigned char minInd = tapeind; //left bound (index in char) on tape used
	unsigned char maxInd = tapeind; //right
	unsigned long leftEnd, rightEnd; //used in computation

	unsigned long steps = 0;
	unsigned char state = 0;
	const unsigned long SAVESTEPS = 1000000000; //1bil
	const unsigned long PRINTSTEPS = 5000000000; //5bil
	const unsigned long SAVEHERE = 1000000000000; //1tril
	const unsigned long MAXSTEPS = 2000000000000; //2tril

	unsigned char * tape;
	tape = malloc(TAPESIZE * sizeof(*tape));//each char is 8 tape boxes 76543210, will be saved in hex so two hex per char
	memset(tape, 0, TAPESIZE * sizeof(*tape));

	unsigned int numSteps = MAXSTEPS/SAVESTEPS + 1;
	unsigned long tapestep[numSteps];
	unsigned long tapelength[numSteps];
	unsigned int savei = 0;

	sigintBreak = 0;
	signal(SIGINT, handle_sigint);
	while (1) {
		//compute, write, maybe exit
		if (state == MACHINESIZE) {
			printf("Halted after %lu steps. %d\n", steps);
			writeFile(tape, steps, tapepos, tapeind, state, minTape, minInd, maxTape, maxInd, tapestep, tapelength, savei);
			return 0;
		}
		if (steps % SAVESTEPS == 0) {
			//leftEnd = 8*(minTape+1)-1-minInd;
			//rightEnd = 8*(maxTape+1)-1-maxInd;
			//difference+1 is length of tape
			tapestep[savei] = steps;
			tapelength[savei] = 8*(maxTape-minTape)-maxInd+minInd+1;
			savei++;
		}
		if (steps % PRINTSTEPS == 0) {
			printf("Chugging along at step %lu\n", steps);
		}

		if (steps == MAXSTEPS || sigintBreak) {
			printf("Gave up after %lu steps...\n", steps);
			writeFile(tape, steps, tapepos, tapeind, state, minTape, minInd, maxTape, maxInd, tapestep, tapelength, savei);
			return 0;
		}
		if (steps == SAVEHERE) {
			printf("Saving at %lu steps...\n", steps);
			writeFile(tape, steps, tapepos, tapeind, state, minTape, minInd, maxTape, maxInd, tapestep, tapelength, savei);
		}


		//do the next step
		unsigned char taperead = (tape[tapepos]>>tapeind)%2;
		if (taperead) { //1
			tape[tapepos] = ((((tape[tapepos]>>(tapeind+1))<<1) + machine[state].write1)<<tapeind) + (tape[tapepos] % (1<<tapeind)); //write
			tapeind -= machine[state].move1; //move
			state = machine[state].next1; //transition
		}
		else { //0
			tape[tapepos] = ((((tape[tapepos]>>(tapeind+1))<<1) + machine[state].write0)<<tapeind) + (tape[tapepos] % (1<<tapeind)); //write
			tapeind -= machine[state].move0; //move
			state = machine[state].next0; //transition
		}


		//possibly move over, also record edge positions
		if (tapepos == maxTape && tapeind < maxInd) { maxInd = tapeind; }
		if (tapepos == minTape && tapeind > minInd) { minInd = tapeind; }
		if (tapeind == -1) { //move to the char to the right
			tapeind = 7;
			if (tapepos == maxTape) {
				maxTape++;
				maxInd = 7;
			}
			tapepos++;
		}
		else if (tapeind == 8) {
			tapeind = 0;
			if (tapepos == minTape) {
				minTape--;
				minInd = 0;
			}
			tapepos--;
		} //char to the left


		steps++;
	}
}
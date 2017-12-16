#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NR_OF_PROGRAMS 16

int main(void){
	// initialize the programs (a, b, c ...)
	char programs[NR_OF_PROGRAMS], temp[NR_OF_PROGRAMS];

	for(int i = 0; i < NR_OF_PROGRAMS; i++){
		programs[i] = i + 97;
	}


	// read the data
	FILE *fp;
	char * data_read = NULL;
	size_t len; ssize_t read;

	if(!(fp = fopen("data", "r"))){
		fprintf(stderr, "Error opening file\n");
		return EXIT_FAILURE;
	}

	getline(&data_read, &len, fp);
	data_read[strcspn(data_read, "\r\n")] = 0;	// remove line breaks


	// parse through the data and generate instruction list
	char * operation, * pch;
	int instructions[10000][3];
	int curr_instruction = 0, repeat_len;
	int X, A, B;

	operation = strtok(data_read, ",");
	while(operation != NULL){
		switch(operation[0]){
			case 's' :
				X = atoi(&operation[1]);
				instructions[curr_instruction][0] = 's';
				instructions[curr_instruction][1] = X;
				break;

			case 'x' :
				A = atoi(&operation[1]);
				pch = strchr(operation, '/');
				B = atoi(&operation[pch - operation + 1]);

				instructions[curr_instruction][0] = 'x';
				instructions[curr_instruction][1] = A;
				instructions[curr_instruction][2] = B;
				break;

			case 'p' :
				A = operation[1];
				pch = strchr(operation, '/');
				B = operation[pch - operation + 1];

				instructions[curr_instruction][0] = 'p';
				instructions[curr_instruction][1] = A;
				instructions[curr_instruction][2] = B;
				break;

			default :
				exit(EXIT_FAILURE);
		}

		curr_instruction++;
		operation = strtok(NULL, ",");
	}


	// find repeat cycle length
	for(int repeat = 0; repeat < 1000000000; repeat++){
		for(curr_instruction = 0; curr_instruction < 10000; curr_instruction++){
			switch(instructions[curr_instruction][0]){
				case 's' :
					X = instructions[curr_instruction][1];

					for(int i = 0; i < X; i++){
						temp[i] = programs[NR_OF_PROGRAMS - X + i];
					}
					for(int i = 0; i < NR_OF_PROGRAMS - X; i++){
						temp[i + X] = programs[i];
					}
					for(int i = 0; i < NR_OF_PROGRAMS; i++){
						programs[i] = temp[i];
					}

					break;

				case 'x' :
					A = instructions[curr_instruction][1];
					B = instructions[curr_instruction][2];

					programs[A] ^= programs[B];
					programs[B] ^= programs[A];
					programs[A] ^= programs[B];
					break;

				case 'p' :
					A = instructions[curr_instruction][1];
					B = instructions[curr_instruction][2];

					for(int i = 0; i < NR_OF_PROGRAMS; i++){
						if(A == programs[i]){
							A = i;
							break;
						}
					}

					for(int i = 0; i < NR_OF_PROGRAMS; i++){
						if(B == programs[i]){
							B = i;
							break;
						}
					}

					programs[A] ^= programs[B];
					programs[B] ^= programs[A];
					programs[A] ^= programs[B];
					break;

				default :
					exit(EXIT_FAILURE);
			}
		}

		if(strncmp(programs, "abcdefghijklmnop", 16) == 0){
			//printf("ok (%d)\n", repeat);
			repeat_len = repeat;
			break;
		}
	}

	// repeat remainder of cycle time times
	for(int repeat = 0; repeat < (1000000000 % (repeat_len + 1)); repeat++){
		for(curr_instruction = 0; curr_instruction < 10000; curr_instruction++){
			switch(instructions[curr_instruction][0]){
				case 's' :
					X = instructions[curr_instruction][1];

					for(int i = 0; i < X; i++){
						temp[i] = programs[NR_OF_PROGRAMS - X + i];
					}
					for(int i = 0; i < NR_OF_PROGRAMS - X; i++){
						temp[i + X] = programs[i];
					}
					for(int i = 0; i < NR_OF_PROGRAMS; i++){
						programs[i] = temp[i];
					}

					break;

				case 'x' :
					A = instructions[curr_instruction][1];
					B = instructions[curr_instruction][2];

					programs[A] ^= programs[B];
					programs[B] ^= programs[A];
					programs[A] ^= programs[B];
					break;

				case 'p' :
					A = instructions[curr_instruction][1];
					B = instructions[curr_instruction][2];

					for(int i = 0; i < NR_OF_PROGRAMS; i++){
						if(A == programs[i]){
							A = i;
							break;
						}
					}

					for(int i = 0; i < NR_OF_PROGRAMS; i++){
						if(B == programs[i]){
							B = i;
							break;
						}
					}

					programs[A] ^= programs[B];
					programs[B] ^= programs[A];
					programs[A] ^= programs[B];
					break;

				default :
					exit(EXIT_FAILURE);
			}
		}
	}


	// print the answer
	for(int i = 0; i < NR_OF_PROGRAMS; i++){
		printf("%c", programs[i]);
	}
	printf("\n");


	// clean up
	fclose(fp);
	free(data_read);
	return EXIT_SUCCESS;
}

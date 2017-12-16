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


	// parse through the data
	int X, A, B;
	char * operation, * pch;
	operation = strtok(data_read, ",");
	while(operation != NULL){
		switch(operation[0]){
			case 's' :
				X = atoi(&operation[1]);
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
				A = atoi(&operation[1]);
				pch = strchr(operation, '/');
				B = atoi(&operation[pch - operation + 1]);

				programs[A] ^= programs[B];
				programs[B] ^= programs[A];
				programs[A] ^= programs[B];
				break;

			case 'p' :
				for(int i = 0; i < NR_OF_PROGRAMS; i++){
					if(operation[1] == programs[i]){
						A = i;
						break;
					}
				}

				pch = strchr(operation, '/');
				for(int i = 0; i < NR_OF_PROGRAMS; i++){
					if(operation[pch - operation + 1] == programs[i]){
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
		operation = strtok(NULL, ",");
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

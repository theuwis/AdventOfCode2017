#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){
	FILE *fp = fopen("data", "r");	// contains input data
	char current_char, next_char;		// stores each number from the input data
	long answer = 0;						// stores the final answer

	// iterate through all the numbers, until the last number is reached
	while((next_char = fgetc(fp)) != EOF) {
		if(current_char == next_char){
			answer += (current_char - '0');	// - '0' is used to convert char to int value
		}

		current_char = next_char;
	}

	// get the first and last number in the file and compare them,
	// because the input is circular
	fseek(fp, 0, SEEK_SET);
	current_char = fgetc(fp);
	fseek(fp, -1, SEEK_END);
	next_char = fgetc(fp);

	if(current_char == next_char){
		answer += (current_char - '0');
	}

	printf("answer=%ld\n", answer);
	return EXIT_SUCCESS;
}
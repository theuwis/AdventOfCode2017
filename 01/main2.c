#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){
	FILE *fp;
	if(!(fp = fopen("data", "r"))){
		fprintf(stderr, "Error opening file\n");
		return EXIT_FAILURE;
	}

	char current_char, compare_char;	// stores each number from the input data
	long answer = 0;						// stores the final answer
	int current_char_index = 0;		

	// get the amount of numbers
	fseek(fp, 0, SEEK_END);
	long file_size = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	// iterate through all the numbers, until the last number is reached
	while((current_char = fgetc(fp)) != EOF){
		// number in first half of total
		if(current_char_index < file_size / 2){
			fseek(fp, file_size/2 - 1, SEEK_CUR);
			compare_char = fgetc(fp);
		}
		// number in second half of total
		else{
			int diff = file_size - current_char_index;

			fseek(fp, file_size / 2 - diff, SEEK_SET);
			compare_char = fgetc(fp);
		}

		if(current_char == compare_char){
			answer += (current_char - '0');
		}

		current_char_index++;
		fseek(fp, current_char_index, SEEK_SET);
	}

	printf("answer=%ld\n", answer);

	fclose(fp);
	return EXIT_SUCCESS;
}
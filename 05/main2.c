#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long answer = 0;
int input[1001];
char * data_read = NULL;
size_t len; ssize_t read;
FILE *fp;

int main(void){
	// open the input file
	if(!(fp = fopen("data", "r"))){
		fprintf(stderr, "Error opening file\n");
		return EXIT_FAILURE;
	}

	// parse the input 1 line at a time
	// and store it in the input array
	int current_line = 0;
	while((read = getline(&data_read, &len, fp)) != -1){
		data_read[strcspn(data_read, "\r\n")] = 0;	// remove line breaks
		input[current_line] = atoi(data_read);
		current_line++;
	}

	int next_pos = 0;
	int input_len = current_line;
	int current_pos = 0;

	while(next_pos < input_len){
		next_pos += input[current_pos];
		input[current_pos] < 3 ? input[current_pos]++ : input[current_pos]--;
		answer++;
		current_pos = next_pos;
	}

	printf("answer=%ld\n", answer);

	free(data_read);
	fclose(fp);
	return EXIT_SUCCESS;
}
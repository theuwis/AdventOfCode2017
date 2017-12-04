#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long answer = 0;
char * data_read = NULL;
size_t len; ssize_t read;
FILE *fp;

char *pass[50];

int is_anagram(char *first_string, char *second_string){
	int first_char_counter[256] = {0}, second_char_counter[256] = {0};
	int counter;

	// two strings cannot be anagram if their length is not equal
	if(strlen(first_string) != strlen(second_string)){
		return 0;
	}

	// count frequency of characters of first_string
	for(counter = 0; first_string[counter] != '\0'; counter++){
	  first_char_counter[first_string[counter]]++;
	}

	// count frequency of characters of second_string
	for(counter = 0; second_string[counter] != '\0'; counter++){
	  second_char_counter[second_string[counter]]++;
	}

	// compare character counts of both strings
	for(counter = 0; counter < 256; counter++){
		if(first_char_counter[counter] != second_char_counter[counter])
			return 0;
	}
	return 1;
}

int main(void){
	int i = 0, j = 0;
	int not_valid_flag = 0;

	// open the input file
	if(!(fp = fopen("data", "r"))){
		fprintf(stderr, "Error opening file\n");
		return EXIT_FAILURE;
	}

	// parse the input 1 line at a time
	while((read = getline(&data_read, &len, fp)) != -1){
		data_read[strcspn(data_read, "\r\n")] = 0;	// remove line breaks

		pass[i] = strtok(data_read, " ");
		while(data_read != NULL){
			data_read = strtok(NULL, " ");
			i++;
			pass[i] = data_read;
		}

		i = 0;
		while(pass[i] != NULL){
			j = i + 1;

			while(pass[j] != NULL){				
				if(is_anagram(pass[i], pass[j]) == 1){
					not_valid_flag = 1;
				}
				j++;
			}
			i++;
		}

		if(not_valid_flag == 0){
			answer++;
		}

		not_valid_flag = 0;
		i = 0;
	}

	printf("answer=%ld\n", answer);

	free(data_read);
	fclose(fp);
	return EXIT_SUCCESS;
}
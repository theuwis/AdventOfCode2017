#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NR_OF_INPUT 1000

char * data_read = NULL;
size_t len; ssize_t read;
FILE *fp;

struct data{
	char name[100];
	int value;
	int highest_value;
};

struct data registers[NR_OF_INPUT];
int nr_of_reg = 0;

void parse_data(void);

int main(void){
	parse_data();

	rewind(fp);
	while((read = getline(&data_read, &len, fp)) != -1){
		data_read[strcspn(data_read, "\r\n")] = 0;	// remove line breaks

		char * pch, reg_to_manipulate[100], reg_with_condition[100];
		int inc_or_dec; // inc = 0, dec = 1
		int inc_dec_nr;
		int condition; // == 0; != 1; < 2; <= 3; > 4; >= 5
		int condition_nr;

		// read the register to manipulate
		pch = strtok(data_read, " ");
		strcpy(reg_to_manipulate, pch);

		// check if the registers needs to be incremented or decremented
		pch = strtok(NULL, " ");
		(strncmp(pch, "inc", 3) == 0) ? (inc_or_dec = 0) : (inc_or_dec = 1);

		// check with how much the register needs to be inc/dec
		pch = strtok(NULL, " ");
		inc_dec_nr = atoi(pch);

		// throw away the 'if'
		pch = strtok(NULL, " ");

		// see which register needs to be checked before manipulation
		pch = strtok(NULL, " ");
		strcpy(reg_with_condition, pch);

		// check the condition operator
		pch = strtok(NULL, " ");
		if(strcmp(pch, "==") == 0)      condition = 0;
		else if(strcmp(pch, "!=") == 0) condition = 1;
		else if(strcmp(pch, "<")  == 0) condition = 2;
		else if(strcmp(pch, "<=") == 0) condition = 3;
		else if(strcmp(pch, ">")  == 0) condition = 4;
		else if(strcmp(pch, ">=") == 0) condition = 5;

		// check the condition number
		pch = strtok(NULL, " ");
		condition_nr = atoi(pch);

		// find the value of the reg to manipulate
		int reg_with_condition_index;
		for(int i = 0; i < nr_of_reg; i++){
			if(strcmp(registers[i].name, reg_with_condition) == 0){
				reg_with_condition_index = i;
				break;
			}
		}

		// check if the condition was met
		int condition_met_flag = 0;
		switch(condition){
			case 0 :
				if(registers[reg_with_condition_index].value == condition_nr) condition_met_flag = 1;
				break;
			case 1 :
				if(registers[reg_with_condition_index].value != condition_nr) condition_met_flag = 1;
				break;
			case 2 :
				if(registers[reg_with_condition_index].value < condition_nr) condition_met_flag = 1;
				break;
			case 3 :
				if(registers[reg_with_condition_index].value <= condition_nr) condition_met_flag = 1;
				break;
			case 4 :
				if(registers[reg_with_condition_index].value > condition_nr) condition_met_flag = 1;
				break;
			case 5 :
				if(registers[reg_with_condition_index].value >= condition_nr) condition_met_flag = 1;
				break;
			default :
				condition_met_flag = 0;
				break;
		}

		// find and change the value of the register is the condition was condition met
		if(condition_met_flag == 1){
			int reg_to_manipulate_index;
			for(int i = 0; i < nr_of_reg; i++){
				if(strcmp(registers[i].name, reg_to_manipulate) == 0){
					reg_to_manipulate_index = i;
					break;
				}
			}

			if(inc_or_dec == 0){ // increment
				registers[reg_to_manipulate_index].value += (inc_dec_nr);
			}
			else{ // decrement
				registers[reg_to_manipulate_index].value -= (inc_dec_nr);
			}

			if(registers[reg_to_manipulate_index].value > registers[reg_to_manipulate_index].highest_value){
				registers[reg_to_manipulate_index].highest_value = registers[reg_to_manipulate_index].value;
			}
		}
	}

	// find answers
	int answer1 = 0, answer2 = 0;
	for(int i = 0; i < nr_of_reg; i++){
		if(registers[i].value > answer1) answer1 = registers[i].value;
		if(registers[i].highest_value > answer2) answer2 = registers[i].highest_value;
	}

	printf("answer1=%d, answer2=%d\n", answer1, answer2);

	free(data_read);
	fclose(fp);
	return EXIT_SUCCESS;
}


void parse_data(void){
	// open the input file
	if(!(fp = fopen("data", "r"))){
		fprintf(stderr, "Error opening file\n");
		exit(EXIT_FAILURE);
	}

	// parse the input 1 line at a time
	// and store it in the input array
	int curr_line = 0;
	while((read = getline(&data_read, &len, fp)) != -1){
		data_read[strcspn(data_read, "\r\n")] = 0;	// remove line breaks

		// save the string in a dummy value
		char * pch = NULL;
		pch = strchr(data_read, ' ');

		char dummy[100];
		strncpy(dummy, data_read, pch - data_read);
		dummy[pch - data_read] = '\0';

		int duplicate_flag = 0;
		for(int i = 0; i < nr_of_reg; i++){
			if(strcmp(registers[i].name, dummy) == 0){
				duplicate_flag = 1;
			}
		}
		if(duplicate_flag != 1){
			strcpy(registers[nr_of_reg].name, dummy);
			nr_of_reg++;
		}

		curr_line++;
	}
}

#include <stdio.h>
#include <stdlib.h>

#define STEP_SIZE 301
#define TOTAL_LEN 50000000

int main(void){
	int curr_nr = 0, curr_pos = 0;
	int answer;

	while(curr_nr < TOTAL_LEN - 1){
		for(int i = 0; i < STEP_SIZE; i++){
			if(curr_pos < curr_nr){
				curr_pos++;
			}
			else{
				curr_pos = 0;
			}
		}
		curr_pos++;

		curr_nr++;
		if(curr_pos == 1) answer = curr_nr;
	}

	printf("answer=%d\n", answer);
	return EXIT_SUCCESS;
}

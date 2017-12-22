#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GRID_SIZE 1000

int grid[GRID_SIZE][GRID_SIZE]; // 0 = .; 1 = #

int parse_data(void); // returns nr of lines


void print_square(void){
	for(int i = 0; i < GRID_SIZE; i++){
		for(int j = 0; j < GRID_SIZE; j++){
			(grid[i][j] == 0) ? printf(". ") : printf("# ");
		}
		printf("\n");
	}
	printf("\n");
}

int main(void){
	int true_grid_size = parse_data();

	int row = GRID_SIZE/2 - 1 + true_grid_size/2, col = GRID_SIZE/2 - 1 + true_grid_size/2;
	int direction = 0; // 0 = up, right = 1, down = 2, left = 3
	int nr_infected = 0;

	for(int steps = 0; steps < 10000; steps++){
		if(grid[row][col] == 0){ // not infected
			// turn left
			(direction > 0) ? (direction--) : (direction = 3);

			// infect the cell
			nr_infected++;
			grid[row][col] = 1;
		}
		else{ // infected
			// turn right
			(direction < 3) ? (direction++) : (direction = 0);

			// clean the cell
			grid[row][col] = 0;
		}

		// move
		switch(direction){
			case 0 : // up
				row--;
				break;
			case 1 : // right
				col++;
				break;
			case 2 : // down
				row++;
				break;
			case 3 : // left
				col--;
				break;
		}
	}

	printf("answer=%d\n", nr_infected);
	return EXIT_SUCCESS;
}

int parse_data(void){
	FILE *fp;

	if(!(fp = fopen("data", "r"))){
		fprintf(stderr, "Error opening file\n");
		exit(EXIT_FAILURE);
	}

	int curr_x = GRID_SIZE/2 - 1, curr_y = GRID_SIZE/2 - 1;
	char c;
	while( (c = fgetc(fp)) != EOF ){
		switch(c){
			case '.' :
				grid[curr_y][curr_x] = 0;
				curr_x++;
				break;
			case '#' :
				grid[curr_y][curr_x] = 1;
				curr_x++;
				break;
			case '\n' :
				curr_y++;
				curr_x = GRID_SIZE/2 - 1;
				break;
		}
	}

	// clean up
	fclose(fp);

	return (curr_y - GRID_SIZE/2 + 1);
}

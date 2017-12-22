#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GRID_SIZE 1000
#define NR_OF_BURSTS 10000000

int grid[GRID_SIZE][GRID_SIZE]; // 0 = .; 1 = W; 2 = #; 3 = F

int parse_data(void); // returns nr of lines
void print_square(void);

int main(void){
	int true_grid_size = parse_data();

	int row = GRID_SIZE/2 - 1 + true_grid_size/2, col = GRID_SIZE/2 - 1 + true_grid_size/2;
	int direction = 0; // 0 = up, right = 1, down = 2, left = 3
	int nr_infected = 0;

	for(int steps = 0; steps < NR_OF_BURSTS; steps++){
		// check state and change direction
		switch(grid[row][col]){
			case 0 : // clean node => turn left
				(direction > 0) ? (direction--) : (direction = 3);
				break;
			case 1 : // weakend node => don't turn
				break;
			case 2 : // infected node => turn right
				(direction < 3) ? (direction++) : (direction = 0);
				break;
			case 3 : // flagged node => reverse
				switch(direction){
					case 0 :
						direction = 2;
						break;
					case 1 :
						direction = 3;
						break;
					case 2 :
						direction = 0;
						break;
					case 3 :
						direction = 1;
						break;
				}
				break;
		}

		// update state state
		switch(grid[row][col]){
			case 0 : // clean node
				grid[row][col]++;
				break;
			case 1 : // weakend node
				grid[row][col]++;
				nr_infected++;
				break;
			case 2 : // infected node
				grid[row][col]++;
				break;
			case 3 : // flagged node
				grid[row][col] = 0;
				break;
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

void print_square(void){
	for(int i = 0; i < GRID_SIZE; i++){
		for(int j = 0; j < GRID_SIZE; j++){
			switch(grid[i][j]){
				case 0 : // clean node
					printf(". ");
					break;
				case 1 : // weakend node
					printf("W ");
					break;
				case 2 : // infected node
					printf("# ");
					break;
				case 3 : // flagged node
					printf("F ");
					break;
			}
		}
		printf("\n");
	}
	printf("\n");
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
				grid[curr_y][curr_x] = 2;
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

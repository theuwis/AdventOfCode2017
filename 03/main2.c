#include <stdio.h>
#include <stdlib.h>
#define SIZE 1001

int input = 347991;
int grid[SIZE][SIZE];


int get_value(int * row, int * col){
	int value = 0;

	// calculate the value of the new square by using the adjacent ones
	for(int i = *row - 1; i <= *row + 1; i++){
		for(int j = *col - 1; j <= *col + 1; j++){
			value += grid[i][j];
		}
	}

	// check if the new value exceeds the puzzle input
	if(value > input){
		printf("answer=%d\n", value);
		exit(EXIT_SUCCESS);
	}

	return value;
}


int main(void){
	// initialize the grid
	for(int i = 0; i < SIZE; i++){
		for(int j = 0; j < SIZE; j++){
			grid[i][j] = 0;
		}
	}

	int col = (SIZE - 1) / 2, row = (SIZE - 1) / 2;
	int current_ring_multiplier = 1;
	grid[row][col] = 1;

	while(1){
		// go 1 right
		col++;
		grid[row][col] = get_value(&row, &col);

		// go up
		for(int j = 0; j < current_ring_multiplier; j++){
			row--;
			grid[row][col] = get_value(&row, &col);
		}

		// go left
		for(int j = 0; j < current_ring_multiplier + 1; j++){
			col--;
			grid[row][col] = get_value(&row, &col);
		}

		// go down
		for(int j = 0; j < current_ring_multiplier + 1; j++){
			row++;
			grid[row][col] = get_value(&row, &col);
		}

		// go right
		for(int j = 0; j < current_ring_multiplier + 1; j++){
			col++;
			grid[row][col] = get_value(&row, &col);
		}

		// next ring
		current_ring_multiplier += 2;
	}

	return EXIT_SUCCESS;
}
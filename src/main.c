#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "lib/utils.h"
#include "lib/algorithm.h"
#include "consts.h"

int* solution(int** U, int** A, int* x_best, int, int);

// main function
int main() {

	int *x_best, v_best, *P, *B;

	// Incompantibility between users
	/*User users[N_USERS] = {
		{1, (int[]){2, 3},			2},
		{2, (int[]){1, 8, 4}, 		3},
		{3, (int[]){2, 1}, 			2},
		{4, (int[]){2, 8}, 			2},
		{5, (int[]){2, 4, 6}, 		3},
		{6, (int[]){2}, 			1},
		{7, (int[]){2, 1, 4, 6}, 	4},
		{8, (int[]){2}, 			1}
	};
*/
	int U_tmp[N_USERS][N_USERS] = { 
		{1, 0, 0, 1, 1, 1, 0, 1}, 
		{0, 1, 0, 0, 0, 0, 0, 0}, 
		{0, 0, 1, 1, 1, 1, 1, 1}, 
		{1, 0, 1, 1, 0, 1, 0, 0}, 
		{1, 0, 1, 0, 1, 0, 1, 1}, 
		{1, 0, 1, 1, 1, 1, 0, 1}, 
		{0, 0, 1, 0, 1, 0, 1, 1}, 
		{1, 0, 1, 1, 1, 1, 1, 1}
	};

	int** U = (int**)malloc(N_USERS*sizeof(int*));
	int i, j;

	for(i = 0; i < N_USERS; i++){
		U[i] = (int*)malloc(N_USERS*sizeof(int));

		memcpy(U[i], U_tmp[i], N_USERS*sizeof(int));
	}

	//users_to_matrix(users, U, N_USERS);
	print_matrix(U, N_USERS, N_USERS);

	// Available seats and aisles
	int S_tmp[N_SITS][N_SITS] = {
		{-1, 0, -1, -1},
		{ 0, 0, -1, -1},
		{ 0, 0, -1, -1},
		{ 0, 0,  0, -1}
	};

	int** S = (int**)malloc(N_SITS*sizeof(int*));
	for(i = 0; i < N_SITS; i++){
		S[i] = (int*)malloc(N_SITS*sizeof(int));

		memcpy(S[i], S_tmp[i], N_SITS*sizeof(int));
	}

	x_best = (int *)malloc((N_USERS + 1) * sizeof(int));

	solution(U, S, x_best, N_USERS, N_SITS);
	
	free(x_best);
	for(i = 0; i < N_USERS; i++){
		free(U[i]);
	}
	free(U);
	for(i = 0; i < N_SITS; i++){
		free(S[i]);
	}
	free(S);

	return 0;
}

int* solution(int** U, int** S, int* x_best, int n_users, int n_seats){
	// optimal solution
	int v_best = 0;
	int* x = (int *)malloc((N_USERS + 1) * sizeof(int));
	sit_users(U, S, 1, x, x_best, &v_best, n_users, n_seats);

	process(S, x_best, n_users, n_seats);
	printf("\t\t Maximum number of occupied seats: %d\n\n\n\n", v_best);

	// Release memory
	printf("End of program\n");

	free(x);

	return x_best;
}
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// @brief Converts an array of users to an adjacency matrix
/// @param users Array of users
/// @param n_users Size of the array of users
void users_to_matrix(User *users, int** matrix, int n_users) {
	int i, j, other, p_id;

	for (i = 0; i < n_users; i++) {
		for (j = 0; j < n_users; j++) {
			matrix[i][j] = 1;
		}

		p_id = users[i].id - 1;

		for (j = 0; j < users[i].n_cant_sit_with; j++) {
			other = users[i].cant_sit_with[j] - 1;

			matrix[p_id][other] = 0;
			matrix[other][p_id] = 0;
		}
	}
}


/// @brief Print the sequence of decisions
/// @param S Matrix of seats
/// @param x Array of decisions
/// @param n_usuarios Number of users in the decision array
/// @param n_asientos Number of seats in the Seats matrix
/// @return void
void process(int** S, int *x, int n_usuarios, int n_asientos) {
	int i;
	printf("\n\t< ");
	for (i = 0; i < n_usuarios; i++) {
		printf("%d ", x[i]);
	}
	printf(">\n\n");

	int j, k;
	for (i = 0; i < n_asientos; i++) {
		for (j = 0; j < n_asientos; j++) {
			if(S[i][j] == -1) {
				printf(" - ");
			} else {
				for(k = 1; k <= n_usuarios; k++) {
					if(x[k] == i*n_asientos + j) {
						printf(" %d ", k);
					}
				}
			}
		}
		printf("\n");
	}
}

/// @brief Prints a matrix
/// @param matrix Matrix to print
/// @param n Number of rows
/// @param m Number of columns
void print_matrix(int** matrix, int n, int m) {
	int i, j;

	printf("{");
	for (i = 0; i < n; i++) {
		printf("{");
		for (j = 0; j < m-1; j++) {
			printf("%d, ", matrix[i][j]);
		}
		printf("%d},\n", matrix[i][m-1]);
	}
	printf("\n");
}
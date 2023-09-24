#include "algorithm.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// @brief Function to calculate if User k can sit in seat x[k].
/// @param U User adjacency matrix.
/// @param A Seat matrix.
/// @param x Decision array.
/// @param k User number.
/// @param n_users Number of users.
/// @param n_seats Number of seats.
/// @return True if User k can sit in seat x[k], False otherwise.
bool can_sit(int** U, int** S, int *x, int k, int n_users, int n_seats) {
	int i, pos, n_row, n_col;

	// print_matrix(S, n_seats, n_seats);

	// Calculate the matrix coordinates
	pos = x[k];
	n_row = pos / n_seats;
	n_col = pos - n_row * n_seats;
	// printf("Seat: %d, coord[%d][%d]\n", pos, n_row, n_col);

	// Check if the sit can be used by a user 
	if (S[n_row][n_col] == -1) {
		// printf("S[%d][%d] == -1\n", n_row, n_col);
		return false;
	}

	// Check if the sit has not been ocupied by another user
  	// printf("k: %d\n", k);
	for (int i = 1; i < k; i++)
		if (x[i] == pos) {
			// printf("(x[%d] == %d)\n", i, pos);
			return false;
		}

	// Check if the sit x[k] of the usesr is compatible 
	//  with the n_seats asigned to the previous users 
	for (int i = 1; i < k; i++) {
		// printf("abs(x[%d] - %d) == 1 && (U[%d][%d] == 1)\n", i, pos, i, k);
		if (abs(x[i] - pos) == 1 && U[i-1][k-1] == 0) {
			return false;
		}
	}

	return true;
}

/// @brief Function to calculate the number of users who have been seated.
/// @param x Decision array.
/// @param k User number.
int value(int *x, int k) {
	int i, total = 0;
	for (i = 1; i <= k; i++) {
		if (x[i] != 0)
			total = total + 1;
	}
	return total;
}

/// @brief Function to calculate the optimal solution.
/// @param U Adjacency matrix.
/// @param S Seat matrix.
/// @param k User number.
/// @param x Decision array.
/// @param x_best Decision array of the optimal solution.
/// @param v_best Number of users in the optimal solution.
/// @param n_users Number of users.
/// @param n_seats Number of seats.
void sit_users(int** U, int** S, int k, int *x, int *x_best, int *v_best, int n_users, int n_seats) {
	int i, aux;
	x[k] = -1;
	while (x[k] < n_seats * n_seats - 1) {
		x[k] = x[k] + 1;
        
        // printf("x[%d]=%d\tcan_sit: %d\n\n\n", k, x[k], can_sit);
        
        if (can_sit(U, S, x, k, n_users, n_seats)) {
            if (k == n_users) {
                aux = value(x, k);
                if (aux > *v_best) {
                    *v_best = aux;
                    memcpy(x_best, x, (n_users + 1) * sizeof(int));
                }
            }
            if (k < n_users)
                sit_users(U, S, k + 1, x, x_best, v_best, n_users, n_seats);
        }
	}
}
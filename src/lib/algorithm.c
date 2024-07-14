#include "algorithm.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// @brief Function to calculate if User k can sit in seat x[k].
/// @param U User adjacency matrix.
/// @param S Seat matrix.
/// @param x Decision array.
/// @param k User number.
/// @param n_users Number of users.
/// @param n_seats Number of seats.
/// @return True if User k can sit in seat x[k], False otherwise.
bool can_sit(int** U, int** S, int *x, int k, int n_users, int n_seats) {
    int pos = x[k];
    int n_row = pos / n_seats;
    int n_col = pos % n_seats;

    // Check if the seat can be used by a user 
    if (S[n_row][n_col] == -1) {
        return false;
    }

    // Check if the seat has not been occupied by another user
    for (int i = 0; i < k; i++) {
        if (x[i] == pos) {
            return false;
        }
    }

    // Check if the seat x[k] of the user is compatible 
    // with the seats assigned to the previous users 
    for (int i = 0; i < k; i++) {
        if (abs(x[i] - pos) == 1 && U[i][k] == 0) {
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
    for (i = 0; i < k; i++) {
        if (x[i] != -1) // Adjusted to check for -1 which indicates no seat assigned
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
    int aux;
    x[k] = -1;

    // Base cases for 1, 2, 3, and 4 users
    if (n_users <= 4) {
        for (int row = 0; row < n_users; row++) {
            bool seat_found = false;
            for (int col = 0; col < n_seats && !seat_found; col++) {
                int pos = row * n_seats + col;
                if (S[row][col] == 0) { // check if the seat is available
                    x[row] = pos; // 0-based indexing
                    seat_found = true;
                } else {
                    x[row] = -1; // invalid seat
                }
            }
        }
        // Validate the seating arrangement
        bool valid = true;
        for (int i = 0; i < n_users && valid; i++) {
            if (!can_sit(U, S, x, i, n_users, n_seats)) {
                valid = false;
            }
        }
        if (valid) {
            aux = value(x, n_users);
            if (aux > *v_best) {
                *v_best = aux;
                memcpy(x_best, x, n_users * sizeof(int));
            }
        }
        return;
    }

    // General case for more than 4 users
    while (x[k] < n_seats * n_seats - 1) {
        x[k] = x[k] + 1;
        if (can_sit(U, S, x, k, n_users, n_seats)) {
            if (k == n_users - 1) { // Adjusted for 0-based indexing
                aux = value(x, k + 1);
                if (aux > *v_best) {
                    *v_best = aux;
                    memcpy(x_best, x, n_users * sizeof(int));
                }
            }
            if (k < n_users - 1) // Adjusted for 0-based indexing
                sit_users(U, S, k + 1, x, x_best, v_best, n_users, n_seats);
        }
    }
}


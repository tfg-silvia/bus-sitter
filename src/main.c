#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "lib/utils.h"
#include "lib/algorithm.h"
#include "consts.h"

int* solution(int** U, int** A, int, int);

int main() {

    int *x_best, v_best, *P, *B;

    int U_tmp[3][3] = { 
        {1, 1, 0}, 
        {1, 1, 0}, 
        {0, 0, 1},
    };

    int** U = (int**)malloc(3 * sizeof(int*));
    int i, j;

    for (i = 0; i < 3; i++) {
        U[i] = (int*)malloc(3 * sizeof(int));
        memcpy(U[i], U_tmp[i], 3 * sizeof(int));
    }

    int S_tmp[N_SEATS][N_SEATS] = {
        {-1, 0, -1, -1},
        { 0, 0, -1, -1},
        { 0, 0, -1, -1},
        { 0, 0,  0, -1}
    };

    int** S = (int**)malloc(N_SEATS * sizeof(int*));
    for (i = 0; i < N_SEATS; i++) {
        S[i] = (int*)malloc(N_SEATS * sizeof(int));
        memcpy(S[i], S_tmp[i], N_SEATS * sizeof(int));
    }

    x_best = solution(U, S, 3, N_SEATS);

    free(x_best);
    for (i = 0; i < 3; i++) {
        free(U[i]);
    }
    free(U);
    for (i = 0; i < N_SEATS; i++) {
        free(S[i]);
    }
    free(S);

    return 0;
}


int* solution(int** U, int** S, int n_users, int n_seats) {
    int* x_best = (int *)malloc(n_users * sizeof(int));

    // Optimal solution
    int v_best = 0;
    int* x = (int *)malloc(n_users * sizeof(int));
    sit_users(U, S, 0, x, x_best, &v_best, n_users, n_seats);

	process(S, x_best, n_users, n_seats);
	printf("\t\t Maximum number of occupied seats: %d\n\n\n\n", v_best);

    free(x);

    return x_best;
}

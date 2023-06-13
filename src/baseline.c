#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

#define USERS 8
#define SITS 4

// functions prototypes
bool can_sit(int[][USERS], int[][SITS], int *, int);
int value(int *, int);
void process(int *, int);

void OPTIMAL_SITS(int[][USERS], int[][SITS], int, int *, int *, int *);

void printU(int matrix[][USERS]) {
	int i, j;

	printf("{");
	for (i = 0; i < USERS; i++) {
		printf("{");
		for (j = 0; j < USERS-1; j++) {
			printf("%d, ", matrix[i][j]);
		}
		printf("%d},\n", matrix[i][USERS-1]);
	}
	printf("\n");
}

void printA(int matrix[][SITS]) {
	int i, j;

	printf("{");
	for (i = 0; i < SITS; i++) {
		printf("{");
		for (j = 0; j < SITS-1; j++) {
			printf("%d, ", matrix[i][j]);
		}
		printf("%d},\n", matrix[i][SITS-1]);
	}
	printf("\n");
}

// main function
int main() {

	int *x, *x_best, v_best, *P, *B;

	// Incompatibilidad entre USERS
	int U[USERS][USERS] = { {1, 0, 0, 1, 1, 1, 0, 1}, {0, 1, 0, 0, 0, 0, 0, 0}, {0, 0, 1, 1, 1, 1, 1, 1}, {1, 0, 1, 1, 0, 1, 0, 0}, {1, 0, 1, 0, 1, 0, 1, 1}, {1, 0, 1, 1, 1, 1, 0, 1}, {0, 0, 1, 0, 1, 0, 1, 1}, {1, 0, 1, 1, 1, 1, 1, 1}};

	// SITS disponibles/no disponibles
	int S[SITS][SITS] = { {-1, 0, -1, -1}, {0, 0, -1, -1}, {0, 0, -1, -1}, {0, 0, 0, -1}};

	printU(U);

	//
	// Vectores x y x_best tienen una dimension mas [0 .. n]
	// pero solo se usara la seccion [1..n], la posicion 0 se ignora.

	// La entrada 0 no se tiene en cuenta
	x = (int *)malloc((USERS + 1) * sizeof(int));
	x_best = (int *)malloc((USERS + 1) * sizeof(int));

	// Solucion OPTIMA
	v_best = 0;
	OPTIMAL_SITS(U, S, 1, x, x_best, &v_best);

	// Presenta los SITS que ocuparan los USERS
	process(x_best, USERS);
	printf("\t\t Maximum number of occupied sits: %d\n\n\n\n", v_best);

	// Release memory
	free(x);
	free(x_best);

	return 0;
}

// function to work out the weight linked to the sequence of decisions x
bool can_sit(int U[][USERS], int S[][SITS], int *x, int k) {
	int i, pos, n_row, n_col;

	// Calcula coordenadas de la matrix
	pos = x[k];
	n_row = pos / SITS;
	n_col = pos - n_row * SITS;
	// // printf("Asiento: %d, coordenadS[%d][%d]\n", pos, n_row, n_col);

	// Chequear si el asiento puede ser usado por un usuario
	if (S[n_row][n_col] == -1) {
		// printf("S[%d][%d] == -1\n", n_row, n_col);
		return false;
	}

	// Chequear que el asiento no ha sido ocupado por otro usuario
  	// printf("k: %d\n", k);
	for (int i = 1; i < k; i++)
		if (x[i] == pos) {
			// printf("(x[%d] == %d)\n", i, pos);
			return false;
		}

	// Chequear si el asiento x[k] del pasajero k es compatible
	//  con los SITS asignados a los pasajeros anteriores
	// printU(U);
	for (int i = 1; i < k; i++) {
		// printf("abs(x[%d] (%d) - %d) == 1 && (U[%d][%d] (%d) == 1)\n", i, x[i], pos, i, k, U[i][k]);
		if (abs(x[i] - pos) == 1 && U[i][k] == 1) {
			return false;
		}
	}

	return true;
}

// Calcular el numero de pasajeros que han sido ubicados
int value(int *x, int k) {
	int i, total = 0;
	for (i = 1; i <= k; i++) {
		if (x[i] != 0)
			total = total + 1;
	}
	return total;
}

// Presenta la secuencia de decisiones
void process(int *x, int n) {
	int i;
	printf("\n\t< ");
	for (i = 1; i <= n; i++) {
		printf("%d ", x[i]);
	}
	printf(">");
}

// backtracking function que proporciona la SOLUCION OPTIMA
void OPTIMAL_SITS(int U[][USERS], int S[][SITS], int k, int *x, int *x_best, int *v_best) {
	int i, aux;
	x[k] = -1;
	while (x[k] < SITS * SITS - 1) {
		x[k] = x[k] + 1;
		bool can_sit = can_sit(U, S, x, k);

		// printU(U);
		// printA(A);
		// printf("x[%d]=%d\tcan_sit: %d\n\n", k, x[k], can_sit);

		if (can_sit) {
			if (k == USERS) {
				aux = value(x, k);
				if (aux > *v_best) {
					*v_best = aux;
					memcpy(x_best, x, (USERS + 1) * sizeof(int));
				}
			}
			if (k < USERS)
				OPTIMAL_SITS(U, S, k + 1, x, x_best, v_best);
		}
	}
}

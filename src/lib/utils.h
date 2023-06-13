#pragma once

#define m2d(i, j, size) (i + size * j)

typedef struct user_t {
    int id;
    int* cant_sit_with;
    int n_cant_sit_with;
}User;

void users_to_matrix(User[], int**, int);
void print_sequence(int*, int);
void print_matrix(int**, int, int);

void process(int**, int*, int, int);

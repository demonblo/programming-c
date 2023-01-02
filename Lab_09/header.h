#ifndef HEADER_H
#define HEADER_H

#endif // HEADER_H

void allocate_matrix(int**matrix, int rows, int columns);
void increase_memory(int**mass, int first_rows, int second_rows, int columns);
void decrease_memory(int**mass, int rows, int columns);
int input_matrix(int**matrix, int rows, int columns);
void output_matrix(int**matrix, int rows, int columns);
void free_matrix(int**matrix, int rows);
int find_max_row(int**matrix, int rows, int columns);
int find_max_column(int**matrix, int rows, int columns);
void delete_row(int**matrix, int rows, int columns, int deleted_row);
void delete_column(int**matrix, int rows, int columns, int deleted_column);
int lower_s_a(int**matrix, int rows, int column);
int max_in_row(int**mass, int row, int columns);
void add_row(int**matrix, int rows, int columns);
void add_column(int**mass, int rows, int columns);
void make_coppy_matrix(int**mass, int**second_mass, int rows, int columns);
void make_ed_matrix(int**mass, int rows, int columns);
void matrix_multiplication(int **result_matrix, int **first_mass, int size);

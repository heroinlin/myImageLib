#ifndef MATRIX_H
#define MATRIX_H
#include "elem_type.h"
#include "my_error.h"
#ifdef __cplusplus
extern "C" {
#endif
	//row * col matrix
	typedef struct matrix
	{
		//the row of matrix
		int row;
		//the col of matrix
		int col;
		//the data of matrix
		f32_t* data;
	}matrix_st,*matrix_pst;

	/**
	* get_matrix_row - get the row of the matrix
	*
	* Parameters:
	* @mat - the matrix itself
	*
	* Return:
	* The row of matrix.
	*/
	static __inline int get_matrix_row(matrix_pst mat)
	{
		return mat->row;
	}

	/**
	* get_matrix_col - get the column of the matrix
	*
	* Parameters:
	* @mat - the matrix itself
	*
	* Return:
	* The column of matrix.
	*/
	static __inline int get_matrix_col(matrix_pst mat)
	{
		return mat->col;
	}

	/**
	* set_matrix - set the row and column of the matrix
	*
	* Parameters:
	* @mat - the matrix itself
	* @new_row - new row of matrix
	* @new_col _ new column of matrix
	*
	* Return:
	* None.
	*/
	static __inline void set_matrix(matrix_pst mat, int new_row ,int new_col)
	{
		mat->row = new_row;
		mat->col = new_col;
	}

	/**
	* get_matrix_data - get the data of the matrix at [row,col]
	*
	* Parameters:
	* @mat - the matrix itself
	* @row - the row of matrix to get data
	* @col - the column of matrix to get data
	*
	* Return:
	* The data of matrix at [row,col].
	*/
	static __inline f32_t get_matrix_data(matrix_pst mat, int row, int col)
	{
		return mat->data[row * mat->col + col];
	}

	/**
	* set_matrix_data - set the data of the matrix at [row,col]
	*
	* Parameters:
	* @mat - the matrix itself
	* @row - the row of matrix to set data
	* @col - the column of matrix to set data
	* @value - The data of matrix at [row,col]
	*
	* Return:
	* None
	*/
	static __inline void set_matrix_data(matrix_pst mat, int row, int col, f32_t value)
	{
		mat->data[row * mat->col + col] = value;
	}

	/**
	* make_matrix - create the image structure
	*
	* Parameters:
	* @row ----- the row of matrix
	* @col ---- the column of matrix
	*
	* Return:
	* The pointer to the matrix
	*/
	extern matrix_pst make_matrix(int row, int col);

	/**
	*free_matrix - free the memory of matrix struct
	*
	* Parameters:
	* @mat - the matrix itself
	*
	* Return:
	* None
	*/
	extern void free_matrix(matrix_pst mat);

	/**
	* get_matrix_n_row - get the data of n-th row 
	*
	* Parameters:
	* @mat - the matrix itself
	* @n - the n-th row  
	*
	* Return:
	* 1 * col matrix. where col is the column of matrix
	*/
	extern matrix_pst get_matrix_n_row(matrix_pst mat, int n);

	/**
	* get_matrix_n_col - get the data of n-th column
	*
	* Parameters:
	* @mat - the matrix itself
	* @n - the n-th column
	*
	* Return:
	* row * 1 matrix. where row is the row of matrix
	*/
	extern matrix_pst get_matrix_n_col(matrix_pst mat, int n);

	/**
	*print_matrix - print the data of matrix one by one
	*
	* Parameters:
	* @mat - the matrix itself
	*
	* Return:
	* None
	*/
	extern void print_matrix(matrix_pst mat);

	/**
	*copy_matrix - copy the matrix 
	*
	* Parameters:
	* @mat - the matrix itself
	*
	* Return:
	* the copy of matrix 
	*/
	extern matrix_pst copy_matrix(matrix_pst mat);

	/**
	*make_matrix_diag - make a identity matrix 
	*
	* Parameters:
	* @dim - the dim of matrix
	*
	* Return:
	* the identity matrix
	*/
	extern matrix_pst make_matrix_diag(int dim);

	/**
	*matrix_transpose - matrix transposition 
	*
	* Parameters:
	* @mat - the matrix itself
	*
	* Return:
	* the transposed matrix
	*/
	extern matrix_pst matrix_transpose(matrix_pst mat);

	/**
	*matrix_add - matrix addition
	*
	* Parameters:
	* @mat_A - the first matrix 
	* @mat_B - the second matrix
	* Return:
	* the result of  matrix addition
	*/
	extern matrix_pst matrix_add(matrix_pst mat_A, matrix_pst mat_B);

	/**
	*matrix_subtract - matrix subtraction
	*
	* Parameters:
	* @mat_A - the first matrix 
	* @mat_B - the second matrix
	* Return:
	* the matrix after subtraction
	*/
	extern matrix_pst matrix_subtract(matrix_pst mat_A, matrix_pst mat_B);

	/**
	*matrix_multiply - matrix multiplied by  matrix
	*
	* Parameters:
	* @mat_A - the first matrix 
	* @mat_B - the second matrix
	* Return:
	* the matrix after multiplication
	*/
	extern matrix_pst matrix_multiply(matrix_pst mat_A, matrix_pst mat_B);

	/**
	*matrix_num_multiply - number multiplied by  matrix 
	*
	* Parameters:
	* @mat - the matrix itself
	* @number - the number 
	* Return:
	* the matrix after multiplication 
	*/
	extern matrix_pst matrix_num_multiply(matrix_pst mat, f32_t number);

	/**
	*matrix_row_bind - bind two matrix that expand by row
	*
	* Parameters:
	* @mat_A - the first matrix
	* @mat_B - the second matrix
	* Return:
	* the matrix after binding
	*/
	extern matrix_pst matrix_row_bind(matrix_pst mat_A, matrix_pst mat_B);

	/**
	*matrix_col_bind - bind two matrix that expand by column
	*
	* Parameters:
	* @mat_A - the first matrix
	* @mat_B - the second matrix
	* Return:
	* the matrix after binding
	*/
	extern matrix_pst matrix_col_bind(matrix_pst mat_A, matrix_pst mat_B);

#ifdef __cplusplus
}
#endif
#endif

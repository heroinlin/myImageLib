#include "matrix.h"
#include <assert.h>
matrix_pst make_matrix(int row, int col)
{
	matrix_pst mat = 0;
	mat = (matrix_pst)malloc(sizeof(matrix_st));
	mat->row = row;
	mat->col = col;
	mat->data = (f32_t*)malloc(row*col*sizeof(f32_t));
	return mat;
}

void free_matrix(matrix_pst mat)
{
	free(mat->data);
	free(mat);
}

matrix_pst get_matrix_n_col(matrix_pst mat, int n)
{
	assert(n >=0 &&n < get_matrix_col(mat));
	int dim = get_matrix_row(mat);
	matrix_pst col = make_matrix(dim, 1);
	float data = 0;
	for (int i = 0; i < dim; i++)
	{
		data = get_matrix_data(mat, i, n);
		set_matrix_data(col, i, 0, data);
	}
	return col;
}

matrix_pst get_matrix_n_row(matrix_pst mat, int n)
{
	assert(n >= 0 && n < get_matrix_row(mat));
	int dim = get_matrix_col(mat);
	matrix_pst row = make_matrix(1, dim);
	float data = 0;
	for (int i = 0; i < dim; i++)
	{
		data = get_matrix_data(mat, n, i);
		set_matrix_data(row, 0, i, data);
	}
	return row;
}

void print_matrix(matrix_pst mat)
{
	int row = get_matrix_row(mat);
	int col = get_matrix_col(mat);
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
		{
			printf("matrix[%d][%d] = %f\n", i, j, get_matrix_data(mat, i, j));
		}
}

matrix_pst copy_matrix(matrix_pst mat)
{
	matrix_pst mat_copy = make_matrix(mat->row, mat->col);
	mat_copy->data = mat->data;
	return mat_copy;
}

matrix_pst make_matrix_diag(int dim)
{
	// create identity matrix
	matrix_pst I = make_matrix(dim, dim);
	for (int i = 0; i < dim; i++)
		for (int j = 0; j < dim; j++)
		{
			if (i==j)
				set_matrix_data(I, i, j, 1);
			else
				set_matrix_data(I, i, j, 0);
		}
	return I;
}

matrix_pst matrix_transpose(matrix_pst mat)
{
	matrix_pst mat_t = make_matrix(mat->col, mat->row);
	int row = get_matrix_row(mat);
	int col = get_matrix_col(mat);
	f32_t data;
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
		{
			data = get_matrix_data(mat, i, j);
			set_matrix_data(mat_t, j, i, data);
		}
	return mat_t;
}

matrix_pst matrix_add(matrix_pst mat_A, matrix_pst mat_B)
{
	assert(get_matrix_row(mat_A) == get_matrix_row(mat_B) && get_matrix_col(mat_A) == get_matrix_col(mat_B));
	int c_row = get_matrix_row(mat_A);
	int c_col = get_matrix_col(mat_A);
	f32_t data;
	matrix_pst mat_C = make_matrix(c_row, c_col);
	for (int i = 0; i < c_row; i++) 
		for (int j = 0; j < c_col; j++) 
		{
			data = get_matrix_data(mat_A, i, j) + get_matrix_data(mat_B, i, j);
			set_matrix_data(mat_C, i, j, data);
		}
	return mat_C;
}

matrix_pst matrix_subtract(matrix_pst mat_A, matrix_pst mat_B)
{
	assert(get_matrix_row(mat_A) == get_matrix_row(mat_B) && get_matrix_col(mat_A) == get_matrix_col(mat_B));
	int c_row = get_matrix_row(mat_A);
	int c_col = get_matrix_col(mat_A);
	f32_t data;
	matrix_pst mat_C = make_matrix(c_row, c_col);
	for (int i = 0; i < c_row; i++)
		for (int j = 0; j < c_col; j++)
		{
			data = get_matrix_data(mat_A, i, j) - get_matrix_data(mat_B, i, j);
			set_matrix_data(mat_C, i, j, data);
		}
	return mat_C;
}

matrix_pst matrix_multiply(matrix_pst mat_A, matrix_pst mat_B)
{
	assert(get_matrix_col(mat_A) == get_matrix_row(mat_B));
	int c_row = get_matrix_row(mat_A);
	int c_col = get_matrix_col(mat_B);
	int a_col = get_matrix_col(mat_A);
	matrix_pst mat_C = make_matrix(c_row, c_col);
	for (int i = 0; i < c_row; i++)
		for (int j = 0; j < c_col; j++)
		{
			f32_t data = 0;
			for (int k = 0; k < a_col; k++)
			{
				data += get_matrix_data(mat_A, i, k) * get_matrix_data(mat_B, k, j);
			}
			set_matrix_data(mat_C, i, j, data);
		}
	return mat_C;
}

matrix_pst matrix_num_multiply(matrix_pst mat, f32_t number)
{
	matrix_pst mat_t = make_matrix(mat->row, mat->col);
	int row = get_matrix_row(mat);
	int col = get_matrix_col(mat);
	f32_t data;
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
		{
			data = number * get_matrix_data(mat, i, j);
			set_matrix_data(mat_t, i, j, data);
		}
	return mat_t;
}

matrix_pst matrix_row_bind(matrix_pst mat_A, matrix_pst mat_B)
{
	assert(get_matrix_col(mat_A) == get_matrix_col(mat_B));
	int a_row = get_matrix_row(mat_A);
	int b_row = get_matrix_row(mat_B);
	int c_row = a_row + b_row;
	int c_col = get_matrix_col(mat_A);
	matrix_pst mat_C = make_matrix(c_row, c_col);
	f32_t data = 0;
	for (int i = 0; i < c_row; i++) 
		for (int j = 0; j < c_col; j++) 
			if (i < a_row) 
			{
				data = get_matrix_data(mat_A, i, j);
				set_matrix_data(mat_C, i, j, data);
			}
			else 
			{ // i >= A.nrows();
				data = get_matrix_data(mat_B, i - a_row, j);
				set_matrix_data(mat_C, i, j, data);
			}
	return mat_C;
}

matrix_pst matrix_col_bind(matrix_pst mat_A, matrix_pst mat_B)
{
	assert(get_matrix_row(mat_A) == get_matrix_row(mat_B));
	int a_col = get_matrix_col(mat_A);
	int b_col = get_matrix_col(mat_B);
	int c_row = get_matrix_row(mat_A);
	int c_col = a_col + b_col;
	matrix_pst mat_C = make_matrix(c_row, c_col);
	f32_t data = 0;
	for (int i = 0; i < c_row; i++)
		for (int j = 0; j < c_col; j++)
			if (j < a_col)
			{
				data = get_matrix_data(mat_A, i, j);
				set_matrix_data(mat_C, i, j, data);
			}
			else
			{ // i >= A.nrows();
				data = get_matrix_data(mat_B, i, j - a_col);
				set_matrix_data(mat_C, i, j, data);
			}
	return mat_C;
}

matrix_pst matrix_inverse(matrix_pst mat)
{
	assert(get_matrix_row(mat) == get_matrix_col(mat));
	int dim = get_matrix_row(mat);
	matrix_pst mat_I = make_matrix_diag(dim, dim);
	matrix_pst temp = copy_matrix(mat);
	int i, j, k;
	float max;
	float data;
	float data1, data2;
	for (i = 0; i < dim; i++)
	{
		//寻找主元  
		max = get_matrix_data(temp, i, i);
		k = i;
		for (j = i + 1; j < dim; j++)
		{
			data = get_matrix_data(temp, j, i);
			if (fabs(data) > fabs(max))
			{
				max = data;
				k = j;
			}
		}
		if (k != i)
		{
			for (j = 0; j < dim; j++)
			{
				data1 = get_matrix_data(temp, i, j);
				data2 = get_matrix_data(temp, k, j);
				set_matrix_data(temp, i, j, data2);
				set_matrix_data(temp, k, j, data1);
				//mat_I伴随交换  
				data1 = get_matrix_data(mat_I, i, j);
				data2 = get_matrix_data(mat_I, k, j);
				set_matrix_data(mat_I, i, j, data2);
				set_matrix_data(mat_I, k, j, data1);
			}
		}
		if (get_matrix_data(temp, i, i) == 0)
		{
			error("There is no inverse matrix!\n");
		}
		//消去A的第i列除去i行以外的各行元素  
		data1 = get_matrix_data(temp, i, i);
		for (j = 0; j < dim; j++)
		{
			data2 = get_matrix_data(temp, i, j) / data1;  
			set_matrix_data(temp, i, j, data2);//主对角线上的元素变为1
			data2 = get_matrix_data(mat_I, i, j) / data1; 
			set_matrix_data(mat_I, i, j, data2);//伴随计算
		}
		for (j = 0; j < dim; j++)        //第0行->第n行  
		{
			if (j != i)                //不是第i行  
			{
				data1 = get_matrix_data(temp, j, i);
				for (k = 0; k < dim; k++)        //第j行元素 - i行元素*j列i行元素  
				{
					data2 = get_matrix_data(temp, j, k) - get_matrix_data(temp, i, k)*data1;
					set_matrix_data(temp, j, k, data2);
					data2 = get_matrix_data(mat_I, j, k) - get_matrix_data(mat_I, i, k)*data1;
					set_matrix_data(mat_I, j, k, data2);
				}
			}
		}
	}
	return mat_I;
}
int main()
{
	matrix_pst mat = make_matrix(3, 3);
	float a[9] = { 0, 0, 1, -1, 2, 0, 1, 1, 1 };
// 	for (int i = 0; i < 32; i++)
// 	{
// 		mat->data[i] = i;
// 	}
	for (int i = 0; i < mat->row; i++)
		for (int j = 0; j < mat->col; j++)
			set_matrix_data(mat, i, j, a[i *mat->col+ j]);
	//mat->data = a;
	matrix_pst mat1 = matrix_inverse(mat);
	//matrix_pst mat2 = matrix_subtract(mat, mat1);
	//print_matrix(mat);
	//matrix_pst mat1 = get_matrix_n_row(mat,2);
	print_matrix(mat1);
	return 0;
}
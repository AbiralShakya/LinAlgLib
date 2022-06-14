//used https://www.andreinc.net/2021/01/20/writing-your-own-linear-algebra-matrix-library-in-c#the-library
// as well as https://github.com/markkraay/mnist-from-scratch/blob/master/matrix/matrix.c 
// for help with the code 

#include <iostream> 
#include <vector>
#include <string>
#include <map>

using namespace std;

struct Matrix{
    double **data;
    int num_rows;
    int num_cols;
};

Matrix* matrix_new(int row, int col);

Matrix* matrix_new(int row, int col){
    Matrix *matrix = new Matrix;
    matrix -> num_rows = row;
    matrix -> num_cols = col;
    matrix -> data = NULL;
    for(int i  =0; i < row; i ++){
        matrix -> data[i] = matrix -> num_cols, sizeof(**matrix -> data);
    }
    return matrix;
}

void matrix_fill(Matrix *m, int n);

void matrix_fill(Matrix *m, int n){
    for (int i =0; i < m -> num_rows; i++){
        for (int j = 0; j < m -> num_cols; j++){
            m -> data[i][j] =n; 
        }
    }
}

void matrix_delete(Matrix *m);

void matrix_delete(Matrix *m){
    for(int i = 0; i < m -> num_rows; i++){
        delete(m-> data[i]);
    }
    delete(m);
    m = NULL;
}

void matrix_print(Matrix *m);

void matrix_print(Matrix *m){
    std::cout << "Rows: " << m -> num_rows << " Columns: " << m-> num_cols << endl;
    for (int i = 0; i < m->num_rows; i++){
        for (int j = 0; j < m->num_cols; j++){
            std::cout<< m-> data[i][j];
        }
    }
    std::cout << "\n";
}

Matrix* matrix_copy(Matrix *m);

Matrix* matrix_copy(Matrix *m){
    Matrix* matrix = matrix_new(m -> num_rows, m-> num_cols);
    for(int i = 0; i < m -> num_rows; i++){
        for (int j = 0; j < m -> num_cols; j++){
            matrix -> data[i][j]  = m -> data[i][j];
        }
    }
    return matrix;
}

Matrix* matrix_square(Matrix *m, int size){
    return matrix_new(size, size);
}

double matrix_random_interval(double min, double max){
    double output;
    output = min + (rand() % static_cast<int>(max - min + 1));
    return output;
}

Matrix *matrix_random(int row, int col, double min, double max){
    Matrix *mat = matrix_new(row,col);
    for (int i = 0; i < row; i ++){
        for (int j = 0; j< col; j++){
            mat -> data[i][j] = matrix_random_interval(min,max);
        }
    }
    return mat;
}

Matrix* matrix_square_random(Matrix *m, int size, double min, double max){
    return matrix_random(size, size, min, max);
}

Matrix* matrix_load(char* file_string){
    FILE* file = fopen(file_string, "r");
    int rows, cols;
    fscanf(file, "%d", &rows);
    fscanf(file, "%d", &cols);
    Matrix *mat = matrix_new(rows, cols);
    for (int i = 0; i < mat -> num_rows; i ++){
        for( int j = 0; j < mat -> num_cols; j++){
            fscanf(file, "%lf\t", &mat -> data[i][j]);
        }
    }
    return mat;
}

// Matrix manipulation methods 

//equal distance, 1. check for same dimensions, 2. check if each element is same 

int matrix_same_dimensions(Matrix *mat1, Matrix *mat2){
    if ((mat1 -> num_cols == mat2 -> num_cols) && (mat1 -> num_rows == mat2 -> num_rows)){
        return true;
    }
    else{
        return false;
    }
}

int matrix_equal(Matrix *mat1, Matrix *mat2, double tolerance){
    if (!matrix_same_dimensions(mat1, mat2)){
        return 0;
    }
    for(int i = 0; i < mat1 -> num_rows;i++){
        for (int j = 0; j < mat2 -> num_rows; j++){
            if (abs(mat1 -> data[i][j] - mat2-> data[i][j]) > tolerance){
                return 0;
            }
        }
    }
    return 1;
}

//multiply matrix row with a scalar quantity 

int matrix_row_multiply(Matrix *mat, int row, double num){
    if (row >= mat -> num_rows){
        std::cout<< "error: row " << row << " out of bounds";
        return 0;
    }
    for (int i = 0; i < mat-> num_rows; i++){
        mat-> data[row][i] *= num;
    }
    return 1;
}

//multiply matrix column with a scalar quantity 

int matrx_col_quantity(Matrix *mat, int col, double num){
    if (col >= mat -> num_cols){
        std::cout<< "error: column " << col << " out of bounds";
        return 0;
    }
    for (int i = 0; i < mat -> num_cols; i++){
        mat -> data[i][col] *= num;
    }
    return 1;
}

//add two rows 

//multiply entire matrix with scalar 

//add two matrices 

Matrix *matrix_add(Matrix *mat1, Matrix *mat2){
    if (matrix_same_dimensions(mat1, mat2)){
        for (int i = 0; i < mat1->num_rows; i++){
            for (int j = 0; j < mat2-> num_cols; j++){
                mat1 -> data[i][j] += mat2 -> data[i][j];
            }
        }
    }
    else{
        std::cout << "error: cannot add two matrices, need to be same length";
    }  
}

//subtract two matrices 

Matrix *matrix_subtract(Matrix* mat1, Matrix *mat2){
    if (matrix_same_dimensions(mat1, mat2)){
        for(int i = 0; i < mat1 -> num_cols; i++){
            for (int j = 0; j <mat2 -> num_cols; j++){
                mat1 -> data[i][j] -= mat2 -> data[i][j];
            }
        }
    }
}

//multiply two matrices 

//c(ikj) = a(i1) * b(j1) + a(i2) * b(j2) .. = a(iz) + b(zj) where z is number of columns in first matrix 

Matrix *matrix_multiply_sequential(Matrix *mat1, Matrix *mat2){
    if (mat1 -> num_cols == mat2 -> num_rows){
        Matrix *matrix = matrix_new(mat1 -> num_rows, mat2 -> num_cols);
        for (int i = 0; i < matrix -> num_rows;i ++){
            for (int j = 0; j < matrix -> num_cols; j++){
                for (int z = 0; z < mat1 -> num_cols; z++){
                    matrix -> data[i][j] += mat1 -> data[i][z] * mat2 -> data[z][j];
                }
            }
        }
        return matrix;
    }
    else{
        std::cout << "error: cannot multiply two matrices" << endl; 
    }
}

Matrix sum(Matrix *A, Matrix *B){
    Matrix *C = matrix_new(A -> num_cols, B -> num_rows);

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            C -> data[i][j] = A -> data[i][j] + B -> data[i][j];
        }
    }
    return *C;
}

Matrix subtract(Matrix *A, Matrix *B){
    Matrix *C = matrix_new(A -> num_rows, B-> num_cols);

    for (int i = 0; i < A-> num_cols; i++){
        for (int j = 0; j < B-> num_rows; j++){
            C -> data[i][j] = A -> data[i][j] - B -> data[i][j];        }
    }
    return *C;
}

//more efficient for larger matrices
// divide and conquer algorithm, divides input matrices of N = 2^n, into four n/2 submatrices, simpler multiplications, combines resulst into result matrix
/*
Matrix *matrix_multiply_strassen(Matrix *mat1, Matrix *mat2, int size){
    if  (mat1 -> num_cols == mat2 -> num_rows){
        Matrix *matrix = matrix_new(mat1-> num_rows, mat2 -> num_cols);

        int k = size /2; 

        Matrix *A11 = matrix_new(k,k);
        Matrix *A12 = matrix_new(k,k);
        Matrix *A21 = matrix_new(k,k);
        Matrix *A22 = matrix_new(k,k);
        Matrix *B11 = matrix_new(k,k);
        Matrix *B12 = matrix_new(k,k);
        Matrix *B21 = matrix_new(k,k);
        Matrix *B22 = matrix_new(k,k);

        for (int i = 0; i < k; i++){
            for ( int j = 0; j < k; j++){
                A11[i][j] = mat1 -> data[i][j];
                A12[i][j] = mat1 -> data[i][k + j];
                A21[i][j] = mat1 -> data[i + k][j];
                A22[i][j] = mat1 -> data[i +k][j+k];
                B11[i][j] = mat2 -> data[i][j];
                B12[i][j] = mat2 -> data[i][k +j];
                B21[i][j] = mat2 -> data[i +k][j];
                B22[i][j]= mat2 -> data[i+k][j+k];
            }
        }

        Matrix *S1 = sum(A11, A12); 


    }
    
}*/

Matrix *matrix_multiply_fox(Matrix *mat1, Matrix *mat2){
    
}



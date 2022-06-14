#include <iostream>
#include <vector> 
#include <memory> 
#include <string>
#include <map>

using namespace std;

#define twoDimVec std::vector<std::vector<string>> 
#define uint unsigned int 

struct st_matrix_dim{
    int rows;
    int cols;
    twoDimVec data;
};

class Matrix{
    public:
        ~Matrix();
        Matrix();
        void matrixNew (int row, int col);
        void matrixDelte(st_matrix_dim *matrix);
        void matrixPrint(st_matrix_dim *matrix);
        st_matrix_dim matrixCopy(st_matrix_dim *matrix);
        st_matrix_dim matrixSquare(st_matrix_dim *matrix);
    private:
        map<string, st_matrix_dim> matrix_dim;
};

void Matrix::matrixNew(int row, int col){
    twoDimVec matrixVec; 

    matrixVec.resize
}







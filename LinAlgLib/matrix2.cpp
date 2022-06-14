//followed tutorial https://www.youtube.com/watch?v=XvEGi43tKYs&ab_channel=TommyNgo for all the code
//put this in here to help build my custom code 


#include <vector>
#include <string>
#include <iostream> 
#include <map>
#include <memory> 

using namespace std;

#define twoDimVec vector<vector<string>>
#define uint unsigned int

struct st_matrix_dim{
    int rows, cols;
};

class Matrix{
    public:
        ~Matrix(); //destructor
        Matrix(); //constructor
        void init(string var, uint rowSize, uint colSize, string strVal);
        void setVal(string var, uint rowNum, uint colNum, string strVal);
        string getVal(string var, uint rowNum, uint colNum);
        uint getRows(string var);
        uint getCols(string var);
        void print_matrix(string var);

    private:
        map<string, twoDimVec> store;
        map<string, bool> lookup;
        map<string, st_matrix_dim> matrix_dim;
};

Matrix::Matrix() {}
Matrix::~Matrix(){}

void Matrix::init(string var, uint rowSize, uint colSize, string strVal){
    twoDimVec vec_matrix;

    vec_matrix.resize(rowSize +1);
    for(uint i =0; i < vec_matrix.size(); i++){
        vec_matrix[i].resize(colSize +1, strVal);
    }
    st_matrix_dim s;
    s.cols = colSize;
    s.rows = rowSize; 

    this-> store[var] = vec_matrix;
    this -> matrix_dim[var] =s;
    lookup[var] = true;
}


uint Matrix::getRows(string var){
    return this -> matrix_dim[var].rows;
}

uint Matrix::getCols(string var){
    return this -> matrix_dim[var].cols;
}

void Matrix::setVal(string var, uint rowNum, uint colNum, string strVal){
    if (rowNum > getRows(var) || colNum > getCols(var)){
        cout << "cannot set data, outside of array boundary";
        return;
    }
    this -> store[var][rowNum][colNum] = strVal;
}

string Matrix::getVal(string var, uint rowNum, uint colNum){
    if (rowNum > getRows(var) || colNum > getCols(var)){
        cout <<"cannot get data, outside of array boundary";
        return;
    }
    return this-> store[var][rowNum][colNum];
}

void Matrix::print_matrix(string var){
    if(lookup[var]){
        uint rows = this -> getRows(var);
        uint cols = this -> getCols(var);
        cout << "Matrix:" << var<< endl;
        cout << "rows:" << rows << "cols:" << cols << endl;
        for(uint i= 0; i <= rows; i++){
            for(uint j = 0; j<= cols; j++){
                cout << "[" << this -> getVal(var,i,j) << "]";
            }
            cout << endl;
        }
    }
}

int main(void){
    unique_ptr<Matrix> x (new Matrix());
}




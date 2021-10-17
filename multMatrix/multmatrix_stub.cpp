#include "utils.h"
#include "mulmatrix_stub.h"

multMatrix_stub::multMatrix_stub(){

}
matrix_t* multMatrix_stub::readMatrix(const char* fileName);
matrix_t multMatrix_stub::*multMatrices(matrix_t* m1, matrix_t *m2);
void multMatrix_stub::writeMatrix(matrix_t* m, const char *fileName);
multMatrix_stub::~multMatrix_stub();
matrix_t multMatrix_stub::*createIdentity(int rows, int cols);
matrix_t multMatrix_stub::*createRandMatrix(int rows, int cols);

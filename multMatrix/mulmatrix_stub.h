#include "multmatrix.h"

#ifndef MULTMATRIX_STUB_H
#define MULTMATRIX_STUB_H

#define OP_SALIR                        0

#define OP_SUMA                         10
#define OP_MULTVECTOR  			11
#define OP_LEEFICHERO  			12
#define OP_INCREMENTACOUNT              13
#define OP_GETCOUNT  			14

class multMatrix_stub
{
private:
    int serverId=0;
public:
    multMatrix_stub();
    matrix_t* readMatrix(const char* fileName);
    matrix_t *multMatrices(matrix_t* m1, matrix_t *m2);
    void writeMatrix(matrix_t* m, const char *fileName);
    ~multMatrix_stub();
    matrix_t *createIdentity(int rows, int cols);
    matrix_t *createRandMatrix(int rows, int cols);
};

#endif // MULTMATRIX_STUB_H

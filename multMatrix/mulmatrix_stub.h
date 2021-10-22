#include "multmatrix.h"

#ifndef MULTMATRIX_STUB_H
#define MULTMATRIX_STUB_H

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8080

#define OP_SALIR			0

#define OP_READMATRIX		10
#define OP_MULTMATRIX		11
#define OP_WRITEMATRIX		12
#define OP_CREATEIDENTITY	13
#define OP_CREATERANDOM		14

class multMatrix_stub
{
private:
	int serverID=-1;
public:
	multMatrix_stub();
	matrix_t* readMatrix(const char* fileName);
	matrix_t* localReadMatrix(const char* fileName);
	matrix_t *multMatrices(matrix_t* m1, matrix_t *m2);
	void writeMatrix(matrix_t* m, const char *fileName);
	void localWriteMatrix(matrix_t* m, const char *fileName);
	~multMatrix_stub();
	matrix_t *createIdentity(int rows, int cols);
	matrix_t *createRandMatrix(int rows, int cols);
};

#endif // MULTMATRIX_STUB_H

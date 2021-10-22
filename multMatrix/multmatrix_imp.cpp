#include "mulmatrix_imp.h"


#define OP_SALIR			0

#define OP_READMATRIX		10
#define OP_MULTMATRIX		11
#define OP_WRITEMATRIX		12
#define OP_CREATEIDENTITY	13
#define OP_CREATERANDOM		14


multmatrix_imp::multmatrix_imp(int clientID)
{
	this->clientID=clientID;
	this->salir=false;

	ops=new multMatrix();
}


void multmatrix_imp::atenderOperacion()
{
	while(!salir)
	{
		//recibir el tipo de operación
		int operacion=-1;
		char* datos=nullptr;
		int dataLen=0;
		recvMSG(clientID,(void**)&datos,&dataLen);
		memcpy(&operacion,datos, sizeof(int));
		delete datos;

		switch(operacion)
		{
			case OP_SALIR:
			{
				salir=true;
			}break;

			case OP_READMATRIX:
			{
				char* nombre = nullptr;
				// Recibir nombre archivo
				recvMSG(clientID,(void**)&datos,&dataLen);
				nombre = new char[dataLen];
				memcpy(nombre,datos,dataLen);
				delete datos;

				matrix_t* resultado = ops->readMatrix(nombre);
				// Enviar matriz resultado
				sendMSG(clientID, (void*)&resultado->rows, sizeof(int));
				sendMSG(clientID, (void*)&resultado->cols, sizeof(int));
				sendMSG(clientID, (void*)&resultado->data, sizeof(int)*resultado->rows*resultado->cols);
				delete resultado, nombre;
			}break;

			case OP_MULTMATRIX:
			{
				matrix_t *m1 = new matrix_t;
				matrix_t *m2 = new matrix_t;
				matrix_t *resultado = new matrix_t;

				// Recibir matriz 1
				recvMSG(clientID,(void**)&datos,&dataLen);
				memcpy(&m1->rows,datos,dataLen);
				delete datos;
				recvMSG(clientID,(void**)&datos,&dataLen);
				memcpy(&m1->cols,datos,dataLen);
				delete datos;
				recvMSG(clientID,(void**)&datos,&dataLen);
				m1->data=new int[m1->rows*m1->cols];
				memcpy(m1->data,(int*)datos,dataLen);
				delete datos;

				// Recibir matriz 2
				recvMSG(clientID,(void**)&datos,&dataLen);
				memcpy(&m2->rows,datos,dataLen);
				delete datos;
				recvMSG(clientID,(void**)&datos,&dataLen);
				memcpy(&m2->cols,datos,dataLen);
				delete datos;
				recvMSG(clientID,(void**)&datos,&dataLen);
				m2->data=new int[m2->rows*m2->cols];
				memcpy(m2->data,(int*)datos,dataLen);
				delete datos;
				resultado = ops->multMatrices(m1,m2);
				// Enviar matriz resultado
				sendMSG(clientID, (void*)&resultado->data, sizeof(int)*resultado->rows*resultado->cols);
				delete resultado, m1, m2 ;
			}break;

			case OP_CREATERANDOM:
			{
				int rows=0, cols=0;
				// filas
				recvMSG(clientID,(void**)&datos,&dataLen);
				memcpy(&rows,datos,dataLen);
				delete datos;
				// Columnas
				recvMSG(clientID,(void**)&datos,&dataLen);
				memcpy(&cols,datos,dataLen);
				delete datos;

				matrix_t* mRandom = ops->createRandMatrix(rows,cols);
				sendMSG(clientID, (void*)mRandom->data, sizeof(int)*rows*cols);
				delete mRandom;
			}break;

			case OP_CREATEIDENTITY:
			{
				int rows=0, cols=0;
				// filas
				recvMSG(clientID,(void**)&datos,&dataLen);
				memcpy(&rows,datos,dataLen);
				delete datos;
				// Columnas
				recvMSG(clientID,(void**)&datos,&dataLen);
				memcpy(&cols,datos,dataLen);
				delete datos;
				matrix_t* mIdentidad = ops->createIdentity(rows,cols);
				sendMSG(clientID, (void*)mIdentidad->data, sizeof(int)*rows*cols);
				delete mIdentidad;
			}break;

			case OP_WRITEMATRIX:
			{
				matrix_t *resultado = new matrix_t;
				char* nombre = nullptr;
				// Recibir Datos Matriz
				recvMSG(clientID,(void**)&datos,&dataLen);
				memcpy(&resultado->rows,datos,dataLen);
				delete datos;
				recvMSG(clientID,(void**)&datos,&dataLen);
				memcpy(&resultado->cols,datos,dataLen);
				delete datos;
				recvMSG(clientID,(void**)&datos,&dataLen);
				resultado->data=new int[resultado->rows*resultado->cols];
				memcpy(resultado->data,(int*)datos,dataLen);
				delete datos;
				// Recibir nombre archivo
				recvMSG(clientID,(void**)&datos,&dataLen);
				nombre = new char[dataLen];
				memcpy(nombre,datos,dataLen);
				delete datos;
				ops->writeMatrix(resultado,nombre);
				delete resultado, nombre;
			}break;

			default:
			{
				std::cout<<"ERROR: Operacion no valida\n";
			}break;
		}
	}
}

multmatrix_imp::~multmatrix_imp()
{
	closeConnection(clientID);
}

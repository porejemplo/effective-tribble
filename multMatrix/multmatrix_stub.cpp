#include "utils.h"
#include "mulmatrix_stub.h"
#include "multmatrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <cstring>
#include <sys/types.h>
#include <unistd.h>

multMatrix_stub::multMatrix_stub(){
	char* ip=new char[strlen(SERVER_IP)+1];
	memcpy(ip,SERVER_IP,strlen(SERVER_IP)+1);
	
	serverID=initClient(ip,SERVER_PORT);
	
	delete ip;
}

matrix_t* multMatrix_stub::readMatrix(const char* fileName){
	int operacion = OP_READMATRIX;
	matrix_t *resultado = new matrix_t;
	char* datos = nullptr;
	int datosLen=0;

	// Enviar Operacion
	sendMSG(serverID, (void*)&operacion, sizeof(int));
	// Enviar Datos Archivo
	sendMSG(serverID, (void*)fileName, strlen(fileName)+1);
	// Recibir matriz resultado
	recvMSG(serverID,(void**)&datos,&datosLen);
	memcpy(&resultado->rows,datos,datosLen);
	delete datos;
	recvMSG(serverID,(void**)&datos,&datosLen);
	memcpy(&resultado->cols,datos,datosLen);
	delete datos;
	recvMSG(serverID,(void**)&datos,&datosLen);
	resultado->data=new int[resultado->rows*resultado->cols];
	memcpy(resultado->data,(int*)datos,datosLen);
	delete datos;

	return resultado;
}

matrix_t* multMatrix_stub::localReadMatrix(const char* fileName){
	FILE* f=fopen(fileName,"r");
	if(f==0)
	{
		std::cout<< "ERROR: Fichero " << std::string(fileName) <<" no existe\n";
		return NULL;
	}
	matrix_t* matrix=new matrix_t[1];

	fscanf(f,"%d %d",&matrix->rows,&matrix->cols);
	std::cout<<"Leidos fila y columna: "<<matrix->rows<<" "<<matrix->cols<<"\n";
	matrix->data=new int[matrix->rows*matrix->cols];
	for(int i=0;i<matrix->rows*matrix->cols;i++)
	{
		fscanf(f,"%d",&matrix->data[i]);
	}

	fclose(f);
	return matrix;
}

matrix_t *multMatrix_stub::multMatrices(matrix_t* m1, matrix_t *m2){
	int operacion = OP_MULTMATRIX;
	matrix_t *resultado = new matrix_t;
	resultado->cols=m2->cols;
	resultado->rows=m1->rows;
	resultado->data=new int[resultado->rows*resultado->cols];
	char* datos = nullptr;
	int datosLen=0;

	// Enviar Operacion
	sendMSG(serverID, (void*)&operacion, sizeof(int));
	// Enviar Datos Matriz 1
	sendMSG(serverID, (void*)&m1->rows, sizeof(int));
	sendMSG(serverID, (void*)&m1->cols, sizeof(int));
	sendMSG(serverID, (void*)&m1->data, sizeof(int)*m1->rows*m1->cols);
	// Enviar Datos Matriz 2
	sendMSG(serverID, (void*)&m2->rows, sizeof(int));
	sendMSG(serverID, (void*)&m2->cols, sizeof(int));
	sendMSG(serverID, (void*)&m2->data, sizeof(int)*m2->rows*m2->cols);

	// Recibir
	recvMSG(serverID, (void**)&datos, &datosLen);
	memcpy(resultado->data,(int*)datos,datosLen);
	delete datos;

	return resultado;
}

void multMatrix_stub::writeMatrix(matrix_t* m, const char *fileName){
	int operacion = OP_WRITEMATRIX;
	char* datos = nullptr;
	int datosLen=0;

	// Enviar Operacion
	sendMSG(serverID, (void*)&operacion, sizeof(int));
	// Enviar Datos Matriz
	sendMSG(serverID, (void*)&m->rows, sizeof(int));
	sendMSG(serverID, (void*)&m->cols, sizeof(int));
	sendMSG(serverID, (void*)&m->data, sizeof(int)*m->rows*m->cols);
	// Enviar Datos Archivo
	sendMSG(serverID, (void*)fileName, strlen(fileName)+1);
}

void multMatrix_stub::localWriteMatrix(matrix_t* m, const char *fileName) {
	FILE* f=fopen(fileName,"w");
	fprintf(f,"%d %d\n",m->rows,m->cols);
	
	for(int i=0;i<m->rows*m->cols;i++)
	{
		fprintf(f,"%d\n",m->data[i]);
	}
	fclose(f);
}

multMatrix_stub::~multMatrix_stub(){
	int operacion = OP_SALIR;
}

matrix_t* multMatrix_stub::createIdentity(int rows, int cols) {
	int operacion = OP_CREATEIDENTITY;
	matrix_t *resultado = new matrix_t;
	resultado->cols=cols;
	resultado->rows=rows;
	resultado->data=new int[rows*cols];
	char* datos = nullptr;
	int datosLen=0;

	// Enviar Operacion
	sendMSG(serverID, (void*)&operacion, sizeof(int));
	// Enviar datos
	sendMSG(serverID, (void*)&rows, sizeof(int));
	sendMSG(serverID, (void*)&cols, sizeof(int));
	// Recibir Datos
	recvMSG(serverID, (void**)&datos, &datosLen);
	memcpy(resultado->data,(int*)datos,datosLen);
	delete datos;

	return resultado;
}

matrix_t *multMatrix_stub::createRandMatrix(int rows, int cols){
	int operacion = OP_CREATERANDOM;
	matrix_t *resultado = new matrix_t;
	resultado->cols=cols;
	resultado->rows=rows;
	resultado->data=new int[rows*cols];
	char* datos = nullptr;
	int datosLen=0;

	// Enviar
	sendMSG(serverID, (void*)&operacion, sizeof(int));
	sendMSG(serverID, (void*)&rows, sizeof(int));
	sendMSG(serverID, (void*)&cols, sizeof(int));

	// Recibir
	recvMSG(serverID, (void**)&datos, &datosLen);
	memcpy(resultado->data,(int*)datos,datosLen);
	delete datos;

	return resultado;
}
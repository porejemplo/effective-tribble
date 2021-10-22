#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "utils.h"
#include "mulmatrix_stub.h"

using namespace std;

#define SERVER_ADDR "127.0.0.1"
#define SERVER_PORT 8080

void freeMatrix(matrix_t* m){
	delete[] m->data;
	delete[] m;

}

int main(int argc,char** argv)
{
	multMatrix_stub* mmatrix=new multMatrix_stub();
	// En este bloque comentado funcionan las funciones
	// matrix_t* m1= mmatrix->createRandMatrix(4,4);
	// matrix_t* m2= mmatrix->createIdentity(4,4);
	// matrix_t* mres=mmatrix->multMatrices(m1,m2);
	// mmatrix->localWriteMatrix(mres, "resultado.txt");
	// matrix_t* m3=mmatrix->localReadMatrix("resultado.txt");
	// matrix_t* mres2=mmatrix->multMatrices(m1,m3);
	// mmatrix->writeMatrix(mres2,"resultado2.txt");

	int n_filas;
	int n_columnas;
	int contMatrices=0;
	matrix_t* finalListaMatrices = new matrix_t();
	matrix_t* m1= nullptr;
	matrix_t* m2= nullptr;

	char operacion;
	do
	{
		cout<<"Elige operacion:"<<endl;
		cin>>operacion;
		switch(operacion)
		{
			case 'N':
				cout<<"Creando nueva matriz"<<endl;
				cout<<"Introduzca numero filas y columnas ";
				cin>>n_filas;
				cin>>n_columnas;
				m1=new matrix_t();
				m1->cols = n_columnas;
				m1->rows = n_filas;
				m1->matrizAnterior = finalListaMatrices;
				m1->data=new int[m1->rows*m1->cols];
				contMatrices++;
				int elemento;
				for (int i = 0; i < n_filas; i++)
				{
					cout << "Fila " << i << endl;
					for (int j = 0; j < n_columnas; j++)
					{
						cout << "Elemento " << j  << endl;
						cin >> elemento;
						m1->data[i*n_columnas+j] = elemento;
					}
					cout << endl;
				}
				finalListaMatrices = m1;
				break;
			case 'R':
				cout<<"Creando nueva matriz aleatoria"<<endl;
				cout<<"Introduzca numero filas y columnas ";
				cin>>n_filas;
				cin>>n_columnas;
				m1=new matrix_t();
				m1->cols = n_columnas;
				m1->rows = n_filas;
				m1->matrizAnterior = finalListaMatrices;
				m1->data=new int[m1->rows*m1->cols];
				contMatrices++;
				m1= mmatrix->createRandMatrix(n_filas,n_columnas);
				finalListaMatrices = m1;
				break;
			case 'I':
				cout<<"Creando nueva matriz identidad"<<endl;
				cout<<"Introduzca numero filas y columnas ";
				cin>>n_filas;
				cin>>n_columnas;
				m1=new matrix_t();
				m1->cols = n_columnas;
				m1->rows = n_filas;
				m1->matrizAnterior = finalListaMatrices;
				m1->data=new int[m1->rows*m1->cols];
				contMatrices++;
				m1= mmatrix->createIdentity(n_filas,n_columnas);
				finalListaMatrices = m1;
				cout<<m1->data[0]<<endl;
				cout<<finalListaMatrices->data[0]<<endl;
				break;
			case 'E':
			// Guarda los datos mal
				cout<<"Escribiendo la matriz"<<endl;
				cout<<finalListaMatrices->data[0]<<endl;
				mmatrix->localWriteMatrix(finalListaMatrices,"resultado.txt");
				break;
			case 'L':
			// no funcona
				cout<<"Leer una matriz de un archivo."<<endl;
				cout<<"Dime el nombre del arvhico del que leer: ";
				char* nombreArchivo;
				cin>> nombreArchivo;
				m1=mmatrix->localReadMatrix(nombreArchivo);
				cout<<m1->data[0]<<endl;
				m1->matrizAnterior = finalListaMatrices;
				finalListaMatrices = m1;
				cout<<finalListaMatrices->data[0]<<endl;
				free(nombreArchivo);
				break;
			case 'M':
				cout<<"Mostrar matriz."<<endl;
				printf("Hay %d matrices cualquieres ver: \n",contMatrices);
				int nMatriz;
				cin>> nMatriz;
				break;
			case 'F':
				cout<<"FIN"<<endl;
				break;
		}
	}while(operacion!='F');
	
	freeMatrix(m1);
	freeMatrix(m2);
	// freeMatrix(mres);
	// freeMatrix(m3);
	// freeMatrix(mres2);
	delete mmatrix;
	return 0;
}

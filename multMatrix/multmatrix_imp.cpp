#include "mulmatrix_imp.h"


#define OP_SALIR                	0

#define OP_SUMA                 	10
#define OP_MULTVECTOR           11
#define OP_LEEFICHERO           12
#define OP_INCREMENTACOUNT  	13
#define OP_GETCOUNT             14


operaciones_imp::operaciones_imp(int clientID)
{
        this->clientID=clientID;
        this->salir=false;

        ops=new operaciones();
}


void operaciones_imp::atenderOperacion()
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

                        case OP_SUMA:
                        {
                                //recibir argumentos
                                int a=0,b=0,resultado=0;
                                recvMSG(clientID,(void**)&datos,&dataLen);
                                memcpy(&a,datos, sizeof(int));
                                delete datos;

                                recvMSG(clientID,(void**)&datos,&dataLen);
                                memcpy(&b,datos, sizeof(int));
                                delete datos;

                                //sumar
                                resultado=ops->suma(a,b);
                                //devolver resultado
                                sendMSG(clientID,(void*)&resultado,sizeof(int));

                        }break;


                        case OP_MULTVECTOR:{
                                float* a=nullptr;
                                float* b=nullptr;
                                int tam=0;
                                float resultado=0;
                                //recibir paquete variables
                                recvMSG(clientID,
                                        (void**)&datos,&dataLen);
                                //desempaqueto
                                tam=dataLen/(sizeof(float)*2);
                                a=(float*)datos;
                                b=(float*)&datos[sizeof(float)*tam];

                                resultado=ops->multVector(a,b,tam);
                                delete datos;

                                //enviar resultado
                                sendMSG(clientID,(void*)&resultado,sizeof(float));

                        }break;

                        case OP_LEEFICHERO:
                        {
                                //recibir nombre
                                char* nombre=nullptr;
                                int fileLen=0;
                                char* fileData=nullptr;

                                recvMSG(clientID,(void**)&nombre,&dataLen);

                                //leer fichero
                                fileData=ops->leeFichero(nombre,&fileLen);

                                //devolver datos fichero
                                sendMSG(clientID,(void*)fileData,fileLen);
                                delete nombre;
                                delete fileData;

                        }

                        break;
                        case OP_INCREMENTACOUNT:
                        {
                                ops->incrementaCount();
                        }

                        break;

                        case OP_GETCOUNT:
                        {
                                int resultado=0;
                                resultado=ops->getCount();

                                sendMSG(clientID, &resultado,sizeof(int));
                        }

                        break;
                        default:
                        {
                                std::cout<<"ERROR: Operacion no valida\n";
                        }break;
                }
        }

}

operaciones_imp::~operaciones_imp()
{
        closeConnection(clientID);
}

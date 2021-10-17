#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "mulmatrix_imp.h"

#define SERVER_PORT 8080

using namespace std;

void threadClient(int clientID)
{
        operaciones_imp* op=new operaciones_imp(clientID);

        while(!op->getSalir())
        {
                op->atenderOperacion();
        }

        delete op;
}


int main(int argc,char** argv)
{
        //iniciar servidor
        int socketID=initServer(SERVER_PORT);

        while(true)
        {	//bucle conexiones clientes
                if(checkNewConnections()) //si hay nueva conexion
                {
                //atenderlas
                 int clientID=getNewConnection();
                 std::thread* th=new std::thread(threadClient,clientID);
                 th->detach();
                }
                //sleep(1);
        }

        return 0;
}

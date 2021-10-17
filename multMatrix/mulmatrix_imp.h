#pragma once

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "multmatrix.h"


class multmatrix_imp
{
private:
        int clientID=-1;
        bool salir=false;
        multMatrix* ops=nullptr;

public:
        multmatrix_imp(int clientID);
        ~multmatrix_imp();
        bool getSalir(){return salir;};
        void atenderOperacion();

};

#pragma once
#include <string>
using namespace std;

class Compra {
public:
    int id_compra = 0;
    string fecha;
    int id_proveedor = 0;

    Compra() {}
    Compra(string fecha, int id_proveedor) {
        this->fecha = fecha;
        this->id_proveedor = id_proveedor;
    }
};
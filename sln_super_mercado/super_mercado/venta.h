#pragma once
#include <string>
using namespace std;

class Venta {
public:
    int id_venta = 0;
    string nit, nombre_cliente, direccion, fecha;
    int no_factura = 0;
    string serie;

    Venta() {}
    Venta(string nit, string nombre_cliente, string direccion, string fecha, int no_factura, string serie) {
        this->nit = nit;
        this->nombre_cliente = nombre_cliente;
        this->direccion = direccion;
        this->fecha = fecha;
        this->no_factura = no_factura;
        this->serie = serie;
    }
};
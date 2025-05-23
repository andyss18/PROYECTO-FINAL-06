#pragma once
#include <string>
using namespace std;

class CompraDetalle {
protected:
    int id_compra_detalle;
    int id_compra;
    int id_producto;
    string cantidad;
    double precio_costo_unitario;

public:
    CompraDetalle() {}
    CompraDetalle(int c, int p, string cant, double precio) {
        id_compra = c;
        id_producto = p;
        cantidad = cant;
        precio_costo_unitario = precio;
    }
};

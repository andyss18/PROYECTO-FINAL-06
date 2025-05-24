#pragma once
#include <string>
using namespace std;

class CompraDetalle {
public:
    int id_compra = 0, id_producto = 0, cantidad = 0;
    float precio_costo = 0.0;

    CompraDetalle() {}
    CompraDetalle(int id_compra, int id_producto, int cantidad, float precio_costo) {
        this->id_compra = id_compra;
        this->id_producto = id_producto;
        this->cantidad = cantidad;
        this->precio_costo = precio_costo;
    }
};

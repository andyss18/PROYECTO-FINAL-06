#pragma once
#include <string>
using namespace std;

class VentaDetalle {
public:
    int id_venta = 0, id_producto = 0, cantidad = 0;
    float precio_unitario = 0.0;
    string nombre_producto, marca;

    VentaDetalle() {}
    VentaDetalle(int id_venta, int id_producto, int cantidad, float precio_unitario, string nombre_producto, string marca) {
        this->id_venta = id_venta;
        this->id_producto = id_producto;
        this->cantidad = cantidad;
        this->precio_unitario = precio_unitario;
        this->nombre_producto = nombre_producto;
        this->marca = marca;
    }
};
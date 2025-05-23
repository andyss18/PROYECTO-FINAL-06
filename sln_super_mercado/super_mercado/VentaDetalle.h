#pragma once
#include <string>
using namespace std;

class VentaDetalle {
protected:
    int id_venta_detalle;
    int id_venta;
    int id_producto;
    string cantidad;
    double precio_unitario;

public:
    VentaDetalle() {}
    VentaDetalle(int v, int p, string c, double pu) {
        id_venta = v;
        id_producto = p;
        cantidad = c;
        precio_unitario = pu;
    }
};

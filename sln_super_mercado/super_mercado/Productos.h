#pragma once
#include "ConexionBD.h"
#include <iostream>
#include <mysql.h>
#include <string>

using namespace std;

class Producto {
private:
    int id_producto, id_marca, existencia;
    string producto, descripcion, imagen, fecha_ingreso;
    double precio_costo, precio_venta;

public:
    Producto() {}

    Producto(int id_p, string prod, int id_m, string desc, string img, double costo, double venta, int exist, string fecha) {
        id_producto = id_p;
        producto = prod;
        id_marca = id_m;
        descripcion = desc;
        imagen = img;
        precio_costo = costo;
        precio_venta = venta;
        existencia = exist;
        fecha_ingreso = fecha;
    }

    void crear() {
        ConexionBD cn;
        int q_estado = 0;
        cn.abrir_conexion();
        if (cn.getConector()) {
            string insert = "INSERT INTO productos (producto, id_marca, descripcion, imagen, precio_costo, precio_venta, existencia, fecha_ingreso) VALUES ('" +
                producto + "', " + to_string(id_marca) + ", '" + descripcion + "', '" + imagen + "', " +
                to_string(precio_costo) + ", " + to_string(precio_venta) + ", " + to_string(existencia) + ", '" + fecha_ingreso + "');";
            const char* c = insert.c_str();
            q_estado = mysql_query(cn.getConector(), c);

            if (!q_estado)
                cout << "--- Producto agregado correctamente ---\n";
            else
                cout << "XXX Error al agregar producto XXX\n";
        }
        else {
            cout << "XXX Error de conexión XXX\n";
        }
        cn.cerrar_conexion();
    }

    void leer() {
        ConexionBD cn;
        int q_estado;
        MYSQL_ROW fila;
        MYSQL_RES* resultado;

        cn.abrir_conexion();
        if (cn.getConector()) {
            cout << "---- LISTA DE PRODUCTOS ----\n";
            string consulta = "SELECT * FROM productos;";
            const char* c = consulta.c_str();
            q_estado = mysql_query(cn.getConector(), c);
            if (!q_estado) {
                resultado = mysql_store_result(cn.getConector());
                while ((fila = mysql_fetch_row(resultado))) {
                    cout << "ID: " << fila[0] << " | Producto: " << fila[1] << " | Marca: " << fila[2]
                        << " | Desc: " << fila[3] << " | Img: " << fila[4] << " | Costo: " << fila[5]
                        << " | Venta: " << fila[6] << " | Stock: " << fila[7] << " | Fecha: " << fila[8] << endl;
                }
            }
            else {
                cout << "XXX Error al leer datos XXX\n";
            }
        }
        else {
            cout << "XXX Error de conexión XXX\n";
        }
        cn.cerrar_conexion();
    }

    void actualizar() {
        ConexionBD cn;
        int q_estado = 0;
        cn.abrir_conexion();
        if (cn.getConector()) {
            string update = "UPDATE productos SET producto='" + producto + "', id_marca=" + to_string(id_marca) +
                ", descripcion='" + descripcion + "', imagen='" + imagen + "', precio_costo=" + to_string(precio_costo) +
                ", precio_venta=" + to_string(precio_venta) + ", existencia=" + to_string(existencia) +
                ", fecha_ingreso='" + fecha_ingreso + "' WHERE id_producto=" + to_string(id_producto) + ";";
            const char* c = update.c_str();
            q_estado = mysql_query(cn.getConector(), c);
            if (!q_estado)
                cout << "--- Producto actualizado correctamente ---\n";
            else
                cout << "XXX Error al actualizar producto XXX\n";
        }
        else {
            cout << "XXX Error de conexión XXX\n";
        }
        cn.cerrar_conexion();
    }

    void borrar() {
        ConexionBD cn;
        int q_estado = 0;
        cn.abrir_conexion();
        if (cn.getConector()) {
            string del = "DELETE FROM productos WHERE id_producto = " + to_string(id_producto) + ";";
            const char* c = del.c_str();
            q_estado = mysql_query(cn.getConector(), c);
            if (!q_estado)
                cout << "--- Producto eliminado correctamente ---\n";
            else
                cout << "XXX Error al eliminar producto XXX\n";
        }
        else {
            cout << "XXX Error de conexión XXX\n";
        }
        cn.cerrar_conexion();
    }
};


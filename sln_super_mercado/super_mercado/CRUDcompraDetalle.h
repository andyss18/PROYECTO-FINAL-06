#pragma once
#include "ConexionBD.h"
#include "compraDetalle.h"
#include <mysql.h>
#include <iostream>

class CRUDCompraDetalle : public CompraDetalle {
public:
    CRUDCompraDetalle() {}
    CRUDCompraDetalle(int c, int p, string cant, double precio)
        : CompraDetalle(c, p, cant, precio) {
    }

    bool crear() {
        ConexionBD cn;
        cn.abrir_conexion();
        if (cn.getConector()) {
            string query = "INSERT INTO compras_detalle(id_compra, id_producto, cantidad, precio_costo_unitario) VALUES (" +
                to_string(id_compra) + ", " + to_string(id_producto) + ", '" + cantidad + "', " + to_string(precio_costo_unitario) + ");";
            if (mysql_query(cn.getConector(), query.c_str()) == 0) {
                cout << "Producto agregado al detalle de compra." << endl;
                cn.cerrar_conexion();
                return true;
            }
            else {
                cout << "Error al insertar detalle: " << mysql_error(cn.getConector()) << endl;
            }
        }
        else {
            cout << "Error de conexión." << endl;
        }
        cn.cerrar_conexion();
        return false;
    }

    void leer(int id_compra_param) {
        ConexionBD cn;
        MYSQL_ROW fila;
        MYSQL_RES* resultado;
        cn.abrir_conexion();
        if (cn.getConector()) {
            string consulta = "SELECT * FROM compras_detalle WHERE id_compra = " + to_string(id_compra_param) + ";";
            if (!mysql_query(cn.getConector(), consulta.c_str())) {
                resultado = mysql_store_result(cn.getConector());
                cout << "ID | Compra | Producto | Cantidad | Precio Unitario" << endl;
                while ((fila = mysql_fetch_row(resultado))) {
                    cout << fila[0] << " | " << fila[1] << " | " << fila[2] << " | " << fila[3] << " | " << fila[4] << endl;
                }
            }
            else {
                cout << "Error al leer detalles." << endl;
            }
        }
        cn.cerrar_conexion();
    }

    void actualizar(int id_detalle) {
        ConexionBD cn;
        cn.abrir_conexion();
        if (cn.getConector()) {
            string query = "UPDATE compras_detalle SET id_producto = " + to_string(id_producto) +
                ", cantidad = '" + cantidad + "', precio_costo_unitario = " + to_string(precio_costo_unitario) +
                " WHERE id_compras_detalle = " + to_string(id_detalle) + ";";
            if (mysql_query(cn.getConector(), query.c_str()) == 0) {
                cout << "Detalle de compra actualizado correctamente." << endl;
            }
            else {
                cout << "Error al actualizar detalle: " << mysql_error(cn.getConector()) << endl;
            }
        }
        cn.cerrar_conexion();
    }

    void eliminar(int id_detalle) {
        ConexionBD cn;
        cn.abrir_conexion();
        if (cn.getConector()) {
            string query = "DELETE FROM compras_detalle WHERE id_compras_detalle = " + to_string(id_detalle) + ";";
            if (mysql_query(cn.getConector(), query.c_str()) == 0) {
                cout << "Detalle de compra eliminado correctamente." << endl;
            }
            else {
                cout << "Error al eliminar detalle: " << mysql_error(cn.getConector()) << endl;
            }
        }
        cn.cerrar_conexion();
    }

    void eliminarPorCompra(int id_compra_param) {
        ConexionBD cn;
        cn.abrir_conexion();
        if (cn.getConector()) {
            string query = "DELETE FROM compras_detalle WHERE id_compra = " + to_string(id_compra_param) + ";";
            if (mysql_query(cn.getConector(), query.c_str()) == 0) {
                cout << "Todos los detalles de la compra fueron eliminados." << endl;
            }
            else {
                cout << "Error al eliminar detalles: " << mysql_error(cn.getConector()) << endl;
            }
        }
        cn.cerrar_conexion();
    }
};

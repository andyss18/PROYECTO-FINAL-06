#pragma once
#include "ConexionBD.h"
#include "ventaDetalle.h"
#include <mysql.h>
#include <iostream>

class CRUDVentaDetalle : public VentaDetalle {
public:
    CRUDVentaDetalle() {}
    CRUDVentaDetalle(int v, int p, string c, double pu)
        : VentaDetalle(v, p, c, pu) {
    }

    bool crear() {
        ConexionBD cn;
        cn.abrir_conexion();
        if (cn.getConector()) {
            string query = "INSERT INTO ventas_detalle(id_venta, id_producto, cantidad, precio_unitario) VALUES (" +
                to_string(id_venta) + ", " + to_string(id_producto) + ", '" + cantidad + "', " + to_string(precio_unitario) + ");";
            if (mysql_query(cn.getConector(), query.c_str()) == 0) {
                cout << "Producto agregado al detalle de venta." << endl;
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

    void leer(int id_venta_param) {
        ConexionBD cn;
        MYSQL_ROW fila;
        MYSQL_RES* resultado;
        cn.abrir_conexion();
        if (cn.getConector()) {
            string consulta = "SELECT * FROM ventas_detalle WHERE id_venta = " + to_string(id_venta_param) + ";";
            if (!mysql_query(cn.getConector(), consulta.c_str())) {
                resultado = mysql_store_result(cn.getConector());
                cout << "ID | Venta | Producto | Cantidad | Precio Unitario" << endl;
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
            string query = "UPDATE ventas_detalle SET id_producto = " + to_string(id_producto) +
                ", cantidad = '" + cantidad + "', precio_unitario = " + to_string(precio_unitario) +
                " WHERE id_ventas_detalle = " + to_string(id_detalle) + ";";
            if (mysql_query(cn.getConector(), query.c_str()) == 0) {
                cout << "Detalle actualizado correctamente." << endl;
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
            string query = "DELETE FROM ventas_detalle WHERE id_ventas_detalle = " + to_string(id_detalle) + ";";
            if (mysql_query(cn.getConector(), query.c_str()) == 0) {
                cout << "Detalle eliminado correctamente." << endl;
            }
            else {
                cout << "Error al eliminar detalle: " << mysql_error(cn.getConector()) << endl;
            }
        }
        cn.cerrar_conexion();
    }

    void eliminarPorVenta(int id_venta_param) {
        ConexionBD cn;
        cn.abrir_conexion();
        if (cn.getConector()) {
            string query = "DELETE FROM ventas_detalle WHERE id_venta = " + to_string(id_venta_param) + ";";
            if (mysql_query(cn.getConector(), query.c_str()) == 0) {
                cout << "Todos los detalles de la venta fueron eliminados." << endl;
            }
            else {
                cout << "Error al eliminar detalles: " << mysql_error(cn.getConector()) << endl;
            }
        }
        cn.cerrar_conexion();
    }
};

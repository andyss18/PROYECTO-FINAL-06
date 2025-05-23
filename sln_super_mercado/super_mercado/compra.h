#pragma once
#include "ConexionBD.h"
#include <mysql.h>
#include <string>
#include <iostream>
using namespace std;

class Compra {
private:
    int id_compra;
    int no_orden_compra, id_proveedor;
    string fecha_orden, fecha_ingreso;

public:
    Compra() {}
    Compra(int no_orden, int id_prov, string fecha_orden_, string fecha_ing_) {
        no_orden_compra = no_orden;
        id_proveedor = id_prov;
        fecha_orden = fecha_orden_;
        fecha_ingreso = fecha_ing_;
    }

    bool crear() {
        ConexionBD cn;
        cn.abrir_conexion();
        if (cn.getConector()) {
            string insert = "INSERT INTO compras(no_orden_compra, id_proveedor, fecha_orden, fecha_ingreso) VALUES (" +
                to_string(no_orden_compra) + ", " + to_string(id_proveedor) + ", '" + fecha_orden + "', '" + fecha_ingreso + "');";
            if (mysql_query(cn.getConector(), insert.c_str()) == 0) {
                cout << "Compra registrada correctamente." << endl;
                cn.cerrar_conexion();
                return true;
            }
            else {
                cout << "Error al insertar compra: " << mysql_error(cn.getConector()) << endl;
            }
        }
        else {
            cout << "Error en la conexión a la base de datos." << endl;
        }
        cn.cerrar_conexion();
        return false;
    }

    void leer() {
        ConexionBD cn;
        MYSQL_ROW fila;
        MYSQL_RES* resultado;
        cn.abrir_conexion();
        if (cn.getConector()) {
            string consulta = "SELECT * FROM compras;";
            if (!mysql_query(cn.getConector(), consulta.c_str())) {
                resultado = mysql_store_result(cn.getConector());
                cout << "ID | No. Orden | Proveedor | Fecha Orden | Fecha Ingreso" << endl;
                while ((fila = mysql_fetch_row(resultado))) {
                    cout << fila[0] << " | " << fila[1] << " | " << fila[2] << " | " << fila[3] << " | " << fila[4] << endl;
                }
            }
            else {
                cout << "Error al leer compras." << endl;
            }
        }
        cn.cerrar_conexion();
    }

    void actualizar(int id) {
        ConexionBD cn;
        cn.abrir_conexion();
        if (cn.getConector()) {
            string query = "UPDATE compras SET no_orden_compra = " + to_string(no_orden_compra) +
                ", id_proveedor = " + to_string(id_proveedor) +
                ", fecha_orden = '" + fecha_orden +
                "', fecha_ingreso = '" + fecha_ingreso +
                "' WHERE id_compra = " + to_string(id) + ";";
            if (mysql_query(cn.getConector(), query.c_str()) == 0) {
                cout << "Compra actualizada correctamente." << endl;
            }
            else {
                cout << "Error al actualizar compra: " << mysql_error(cn.getConector()) << endl;
            }
        }
        cn.cerrar_conexion();
    }

    void eliminar(int id) {
        ConexionBD cn;
        cn.abrir_conexion();
        if (cn.getConector()) {
            string query = "DELETE FROM compras WHERE id_compra = " + to_string(id) + ";";
            if (mysql_query(cn.getConector(), query.c_str()) == 0) {
                cout << "Compra eliminada correctamente." << endl;
            }
            else {
                cout << "Error al eliminar compra: " << mysql_error(cn.getConector()) << endl;
            }
        }
        cn.cerrar_conexion();
    }
};

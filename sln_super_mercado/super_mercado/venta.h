#pragma once
#include "ConexionBD.h"
#include <mysql.h>
#include <string>
#include <iostream>
using namespace std;

class Venta {
private:
    int id_venta;
    int num_factura, id_cliente, id_empleado;
    string serie, fecha_factura, fecha_ingreso;

public:
    Venta() {}
    Venta(int nf, string s, string ff, int idc, int ide, string fi) {
        num_factura = nf;
        serie = s;
        fecha_factura = ff;
        id_cliente = idc;
        id_empleado = ide;
        fecha_ingreso = fi;
    }

    bool crear() {
        ConexionBD cn;
        cn.abrir_conexion();
        if (cn.getConector()) {
            string query = "INSERT INTO ventas(num_factura, serie, fecha_factura, id_cliente, id_empleado, fecha_ingreso) VALUES (" +
                to_string(num_factura) + ", '" + serie + "', '" + fecha_factura + "', " + to_string(id_cliente) + ", " +
                to_string(id_empleado) + ", '" + fecha_ingreso + "');";
            if (mysql_query(cn.getConector(), query.c_str()) == 0) {
                cout << "Venta registrada correctamente." << endl;
                cn.cerrar_conexion();
                return true;
            }
            else {
                cout << "Error al registrar venta: " << mysql_error(cn.getConector()) << endl;
            }
        }
        else {
            cout << "Error en la conexión." << endl;
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
            string consulta = "SELECT * FROM ventas;";
            if (!mysql_query(cn.getConector(), consulta.c_str())) {
                resultado = mysql_store_result(cn.getConector());
                cout << "ID | Factura | Serie | Fecha | Cliente | Empleado | Ingreso" << endl;
                while ((fila = mysql_fetch_row(resultado))) {
                    cout << fila[0] << " | " << fila[1] << " | " << fila[2] << " | " << fila[3]
                        << " | " << fila[4] << " | " << fila[5] << " | " << fila[6] << endl;
                }
            }
            else {
                cout << "Error al leer ventas." << endl;
            }
        }
        cn.cerrar_conexion();
    }

    void actualizar(int id) {
        ConexionBD cn;
        cn.abrir_conexion();
        if (cn.getConector()) {
            string query = "UPDATE ventas SET num_factura = " + to_string(num_factura) +
                ", serie = '" + serie + "', fecha_factura = '" + fecha_factura +
                "', id_cliente = " + to_string(id_cliente) +
                ", id_empleado = " + to_string(id_empleado) +
                ", fecha_ingreso = '" + fecha_ingreso +
                "' WHERE id_venta = " + to_string(id) + ";";
            if (mysql_query(cn.getConector(), query.c_str()) == 0) {
                cout << "Venta actualizada correctamente." << endl;
            }
            else {
                cout << "Error al actualizar: " << mysql_error(cn.getConector()) << endl;
            }
        }
        cn.cerrar_conexion();
    }

    void eliminar(int id) {
        ConexionBD cn;
        cn.abrir_conexion();
        if (cn.getConector()) {
            string query = "DELETE FROM ventas WHERE id_venta = " + to_string(id) + ";";
            if (mysql_query(cn.getConector(), query.c_str()) == 0) {
                cout << "Venta eliminada correctamente." << endl;
            }
            else {
                cout << "Error al eliminar: " << mysql_error(cn.getConector()) << endl;
            }
        }
        cn.cerrar_conexion();
    }
};

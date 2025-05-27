#pragma once
#include <iostream>
#include <vector>
#include "compra.h"
#include "compraDetalle.h"
#include "ConexionBD.h"

class CRUDCompraDetalle {
public:
    void realizarCompra() {
        ConexionBD cn;
        cn.abrir_conexion();
        MYSQL* con = cn.getConector();

        int id_proveedor;
        string fecha;
        cout << "Ingrese ID del proveedor: ";
        cin >> id_proveedor;
        cout << "Ingrese fecha de orden (YYYY-MM-DD): ";
        cin >> fecha;

   
        int no_orden = 1;
        MYSQL_RES* res;
        MYSQL_ROW row;
        string query_max = "SELECT MAX(no_orden_compra) FROM compras";
        if (mysql_query(con, query_max.c_str()) == 0) {
            res = mysql_store_result(con);
            row = mysql_fetch_row(res);
            if (row && row[0]) {
                no_orden = stoi(row[0]) + 1;
            }
        }

        string insert_compra =
            "INSERT INTO compras(no_orden_compra, id_proveedor, fecha_orden, fecha_ingreso) VALUES (" +
            to_string(no_orden) + ", " +
            to_string(id_proveedor) + ", '" +
            fecha + "', NOW())";

        if (mysql_query(con, insert_compra.c_str()) != 0) {
            cerr << "Error al insertar en 'compras': " << mysql_error(con) << endl;
            cn.cerrar_conexion();
            return;
        }

        int id_compra = (int)mysql_insert_id(con);

        vector<CompraDetalle> detalles;
        char opcion = 's';
        float total = 0;
        while (opcion == 's') {
            int id_producto, cantidad;
            float precio_costo;
            cout << "Ingrese ID del producto: ";
            cin >> id_producto;
            
            ConexionBD cn;
            cn.abrir_conexion();
            if (cn.getConector()) {
                string consulta = "SELECT producto, descripcion FROM productos WHERE id_producto = " + to_string(id_producto);
                const char* c = consulta.c_str();
                if (!mysql_query(cn.getConector(), c)) {
                    MYSQL_RES* resultado = mysql_store_result(cn.getConector());
                    MYSQL_ROW fila;
                    if ((fila = mysql_fetch_row(resultado))) {
                        cout << "Producto seleccionado: " << fila[0] << endl;
                        cout << "Descripcion: " << fila[1] << endl;
                    }
                    else {
                        cout << "Producto no encontrado." << endl;
                    }
                    mysql_free_result(resultado);
                }
                else {
                    cout << "Error al consultar producto." << endl;
                }
            }
            else {
                cout << "Error de conexion." << endl;
            }
            cn.cerrar_conexion();

            cout << "Ingrese cantidad: ";
            cin >> cantidad;
            cout << "Ingrese precio costo: ";
            cin >> precio_costo;

            total += precio_costo * cantidad;
            detalles.push_back(CompraDetalle(id_compra, id_producto, cantidad, precio_costo));

            cout << "¿Desea ingresar otro producto? (s/n): ";
            cin >> opcion;
        }

        for (auto& d : detalles) {
            string insert_det = "INSERT INTO compras_detalle(id_compra, id_producto, cantidad, precio_costo_unitario) VALUES(" +
                to_string(d.id_compra) + "," + to_string(d.id_producto) + "," + to_string(d.cantidad) + "," + to_string(d.precio_costo) + ")";

            if (mysql_query(con, insert_det.c_str()) != 0) {
                cerr << "Error al insertar en 'compras_detalle': " << mysql_error(con) << endl;
                cn.cerrar_conexion();
                return;
            }
        }

        cout << "\n=========== FACTURA COMPRA ===========\n";
        cout << "No. Orden Compra: " << no_orden << "\tFecha Orden: " << fecha << "\n";
        cout << "ID Proveedor: " << id_proveedor << "\n\n";
        cout << "PRODUCTO\n";
        for (auto& d : detalles) {
            cout << d.id_producto << "\tQ " << d.precio_costo << " x " << d.cantidad << "\n";
        }
        cout << "Total: Q " << total << "\nGracias por su compra.\n";

        cn.cerrar_conexion();
    }


    void leerCompras() {
        ConexionBD cn;
        cn.abrir_conexion();
        MYSQL* con = cn.getConector();
        MYSQL_ROW row;
        MYSQL_RES* res;

        string consulta =
            "SELECT c.id_compra, c.fecha_orden, c.no_orden_compra, p.proveedor "
            "FROM compras c INNER JOIN proveedores p ON c.id_proveedor = p.id_proveedor";

        if (mysql_query(con, consulta.c_str()) == 0) {
            res = mysql_store_result(con);
            cout << "\nCOMPRAS REGISTRADAS:\n";
            while ((row = mysql_fetch_row(res))) {
                cout << "ID Compra: " << (row[0] ? row[0] : "NULL")
                    << ", Fecha Orden: " << (row[1] ? row[1] : "NULL")
                    << ", No. Orden: " << (row[2] ? row[2] : "NULL")
                    << ", Proveedor: " << (row[3] ? row[3] : "NULL") << endl;
            }

        }
        else {
            cerr << "Error al leer compras: " << mysql_error(con) << endl;
        }

        cn.cerrar_conexion();
    }

    void actualizarCompra() {
        int id;
        cout << "Ingrese ID de la compra que desea actualizar: ";
        cin >> id;

        string nueva_fecha;
        cout << "Ingrese nueva fecha (YYYY-MM-DD): ";
        cin >> nueva_fecha;

        ConexionBD cn;
        cn.abrir_conexion();
        MYSQL* con = cn.getConector();

        string update = "UPDATE compras SET fecha_orden = '" + nueva_fecha + "' WHERE id_compra = " + to_string(id);
        if (mysql_query(con, update.c_str()) == 0) {
            cout << "Compra actualizada exitosamente.\n";
        }
        else {
            cerr << "Error al actualizar: " << mysql_error(con) << endl;
        }

        cn.cerrar_conexion();
    }

    void eliminarCompra() {
        int id;
        cout << "Ingrese ID de la compra a eliminar: ";
        cin >> id;

        ConexionBD cn;
        cn.abrir_conexion();
        MYSQL* con = cn.getConector();

        string del_detalle = "DELETE FROM compras_detalle WHERE id_compra = " + to_string(id);
        string del_compra = "DELETE FROM compras WHERE id_compra = " + to_string(id);

        if (mysql_query(con, del_detalle.c_str()) == 0 && mysql_query(con, del_compra.c_str()) == 0) {
            cout << "Compra eliminada correctamente.\n";
        }
        else {
            cerr << "Error al eliminar compra: " << mysql_error(con) << endl;
        }

        cn.cerrar_conexion();
    }



};

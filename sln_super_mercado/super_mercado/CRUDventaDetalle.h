#pragma once
#include <iostream>
#include <vector>
#include "venta.h"
#include "ventaDetalle.h"
#include "ConexionBD.h"

class CRUDVentaDetalle {
public:
    void realizarVenta() {
        ConexionBD cn;
        cn.abrir_conexion();
        MYSQL* con = cn.getConector();
        string nit, nombre, apellidos, nombre_completo, direccion;
        cout << "Ingrese NIT del cliente: ";
        cin >> nit;

        if (nit != "C/F" && !validarNIT(nit)) {
            cout << "NIT inválido.\n";
            return;
        }

        MYSQL_ROW row;
        MYSQL_RES* res;
        string consulta = "SELECT nombres, apellidos FROM cliente WHERE nit = '" + nit + "'";
        if (mysql_query(con, consulta.c_str()) == 0) {
            res = mysql_store_result(con);
            if (mysql_num_rows(res) > 0) {
                row = mysql_fetch_row(res);
                nombre = row[0];
                apellidos = row[1];
                nombre_completo = nombre + " " + apellidos;
                cin.ignore();
                cout << "Ingrese direccion: ";
                getline(cin, direccion);
            }
            else {
                cin.ignore();
                cout << "Cliente no encontrado. Ingrese nombres: ";
                getline(cin, nombre);
                cout << "Ingrese apellidos: ";
                getline(cin, apellidos);
                nombre_completo = nombre + " " + apellidos;

                cout << "Ingrese direccion: ";
                getline(cin, direccion); 

                cout << "Ingrese telefono: ";
                string telefono;
                getline(cin, telefono);

                
                string insert_cliente = "INSERT INTO cliente(nit, nombres, apellidos, telefono) VALUES ('" +
                    nit + "', '" + nombre + "', '" + apellidos + "', '" + telefono + "')";
                if (mysql_query(con, insert_cliente.c_str()) != 0) {
                    cout << "Error al insertar cliente: " << mysql_error(con) << endl;
                    cn.cerrar_conexion();
                    return;
                }
            }
        }

        string fecha;
        cout << "Ingrese fecha (YYYY-MM-DD): ";
        cin >> fecha;
        string serie = "A";  
        int no_factura = 1;
        string query_max_factura = "SELECT MAX(num_factura) FROM ventas WHERE serie = '" + serie + "'";
        if (mysql_query(con, query_max_factura.c_str()) == 0) {
            res = mysql_store_result(con);
            row = mysql_fetch_row(res);
            if (row && row[0]) no_factura = stoi(row[0]) + 1;
        }


        int id_cliente = 0;
        string cliente_query = "SELECT id_cliente FROM cliente WHERE nit = '" + nit + "'";
        if (mysql_query(con, cliente_query.c_str()) == 0) {
            res = mysql_store_result(con);
            row = mysql_fetch_row(res);
            if (row) id_cliente = stoi(row[0]);
        }

        string insert_venta = "INSERT INTO ventas(id_cliente, fecha_ingreso, num_factura, serie) VALUES (" +
            to_string(id_cliente) + ", '" + fecha + "', " + to_string(no_factura) + ", '" + serie + "')";
        mysql_query(con, insert_venta.c_str());
        int id_venta = (int)mysql_insert_id(con);

        vector<VentaDetalle> detalles;
        char opcion = 's';
        float total = 0;
        while (opcion == 's') {
            int id_producto, cantidad;
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

            string consulta_prod = "SELECT p.producto, m.marca, p.precio_venta FROM productos p INNER JOIN marca m ON p.id_marca = m.id_marca WHERE p.id_producto = " + to_string(id_producto);
            if (mysql_query(con, consulta_prod.c_str()) == 0) {
                res = mysql_store_result(con);
                if ((row = mysql_fetch_row(res))) {
                    string nombre_producto = row[0];
                    string marca = row[1];
                    float precio = stof(row[2]);
                    total += precio * cantidad;
                    detalles.push_back(VentaDetalle(id_venta, id_producto, cantidad, precio, nombre_producto, marca));
                }
                else {
                    cout << "\nProducto no encontrado en base de datos.\n";
                    continue;
                }
            }
            else {
                cout << "\nError al consultar producto.\n";
                continue;
            }

            cout << "¿Desea ingresar otro producto? (s/n): ";
            cin >> opcion;
        }

        for (auto& d : detalles) {
            string insert_det = "INSERT INTO ventas_detalle(id_venta, id_producto, cantidad, precio_unitario) VALUES(" +
                to_string(d.id_venta) + "," + to_string(d.id_producto) + "," + to_string(d.cantidad) + "," + to_string(d.precio_unitario) + ")";
            mysql_query(con, insert_det.c_str());
        }

        cout << "\n=========== FACTURA ===========\n";
        cout << "No Factura: " << no_factura << "\tFecha: " << fecha << "\n";
        cout << "NIT: " << nit << "\nCliente: " << nombre_completo << "\n\n";
        cout << "Direccion: " << direccion << "\n\n";
        cout << "PRODUCTO\n";
        for (auto& d : detalles) {
            cout << d.id_producto << "-" << d.nombre_producto << " marca " << d.marca << "\tQ " << d.precio_unitario << " x " << d.cantidad << "\n";
        }
        cout << "Total: Q " << total << "\nGracias por su compra.\n";

        cn.cerrar_conexion();
    }


    void leerVentas() {
        ConexionBD cn;
        cn.abrir_conexion();
        MYSQL* con = cn.getConector();
        MYSQL_ROW row;
        MYSQL_RES* res;

        string consulta =
            "SELECT v.id_venta, v.fecha_ingreso, v.num_factura, v.serie, c.nit, c.nombres, c.apellidos "
            "FROM ventas v INNER JOIN cliente c ON v.id_cliente = c.id_cliente WHERE v.anulada = 0;";


        if (mysql_query(con, consulta.c_str()) == 0) {
            res = mysql_store_result(con);
            cout << "\nVENTAS REGISTRADAS:\n";
            while ((row = mysql_fetch_row(res))) {
                cout << "ID Venta: " << row[0]
                    << ", Fecha: " << row[1]
                    << ", Factura: " << row[2] << "-" << row[3]
                    << ", NIT: " << row[4]
                    << ", Cliente: " << row[5] << " " << row[6] << endl;
            }
        }
        else {
            cerr << "Error al leer ventas: " << mysql_error(con) << endl;
        }

        cn.cerrar_conexion();
    }


    void actualizarVenta() {
        int id_venta;
        cout << "Ingrese ID de la venta que desea actualizar: ";
        cin >> id_venta;

        ConexionBD cn;
        cn.abrir_conexion();
        MYSQL* con = cn.getConector();

        
        string consulta = "SELECT anulada FROM ventas WHERE id_venta = " + to_string(id_venta);
        if (mysql_query(con, consulta.c_str()) != 0) {
            cerr << "Error al buscar la venta: " << mysql_error(con) << endl;
            cn.cerrar_conexion();
            return;
        }

        MYSQL_RES* res = mysql_store_result(con);
        MYSQL_ROW row = mysql_fetch_row(res);

        if (!row) {
            cout << "La venta no existe.\n";
            cn.cerrar_conexion();
            return;
        }

        if (string(row[0]) == "1") {
            cout << "La venta ya fue anulada. No se puede modificar.\n";
            cn.cerrar_conexion();
            return;
        }

        string nueva_fecha;
        cout << "Ingrese nueva fecha (YYYY-MM-DD): ";
        cin >> nueva_fecha;

        string update = "UPDATE ventas SET fecha_ingreso = '" + nueva_fecha + "' WHERE id_venta = " + to_string(id_venta);
        if (mysql_query(con, update.c_str()) == 0) {
            cout << "Fecha actualizada correctamente.\n";
        }
        else {
            cerr << "Error al actualizar la fecha: " << mysql_error(con) << endl;
        }

        cn.cerrar_conexion();
    }

    void eliminarVenta() {
        int id;
        cout << "Ingrese ID de la venta a eliminar: ";
        cin >> id;

        ConexionBD cn;
        cn.abrir_conexion();
        MYSQL* con = cn.getConector();

        string del_detalle = "DELETE FROM ventas_detalle WHERE id_venta = " + to_string(id);
        string del_venta = "DELETE FROM ventas WHERE id_venta = " + to_string(id);

        if (mysql_query(con, del_detalle.c_str()) == 0 && mysql_query(con, del_venta.c_str()) == 0) {
            cout << "Venta eliminada correctamente.\n";
        }
        else {
            cerr << "Error al eliminar venta: " << mysql_error(con) << endl;
        }

        cn.cerrar_conexion();
    }
   


private:
    bool validarNIT(string nit) {
        for (char c : nit) {
            if (!isdigit(c) && c != '-') return false;
        }
        return true;
    }
};

#include <iostream>
#include "Puestos.h"
#include "Marcas.h"
#include "Cliente.h"
#include "Empleado.h"
#include "CRUDventaDetalle.h"
#include "CRUDcompraDetalle.h"

using namespace std;

void menuVentas();
void menuCompras();

int main() {
    string puesto, marca;
    int id_puesto, id_marca = 0;
    int opcion1, opcion2;
    Puesto e;
    Marcas mar;
    Cliente cliente;
    Empleado empleado;

inicio:
    system("cls");
    cout << "INGRESE UNA OPERACION" << endl;
    cout << "1.INGRESAR A PUESTOS" << endl;
    cout << "2.INGRESAR A MARCAS" << endl;
    cout << "3.INGRESAR A CLIENTES" << endl;
    cout << "4.INGRESAR A EMPLEADOS" << endl;
    cout << "5.INGRESAR A SISTEMA DE VENTAS" << endl;
    cout << "6.INGRESAR A SISTEMA DE COMPRAS" << endl;
    cout << "0. Salir" << endl;
    cin >> opcion1;

    switch (opcion1) {
    case 1:
        while (true) {
            system("cls");
            cout << "Seleccione una Opcion:" << endl;
            cout << "1. Crear Puesto" << endl;
            cout << "2. Mostrar Puestos" << endl;
            cout << "3. Actualizar Puesto" << endl;
            cout << "4. Borrar Puesto" << endl;
            cout << "0. Salir" << endl;
            cout << "Ingrese una opcion: ";
            cin >> opcion2;

            switch (opcion2) {
            case 1:
                system("cls");
                cout << "Ingrese el Codigo del Puesto: ";
                cin >> id_puesto;
                cin.ignore();
                cin.ignore();
                cout << "Ingrese Nombre del Puesto: ";
                getline(cin, puesto);
                e = Puesto(id_puesto, puesto);
                e.crear();
                system("pause");
                break;
            case 2:
                system("cls");
                e.leer();
                system("pause");
                break;
            case 3:
                system("cls");
                cout << "Ingrese ID a modificar: ";
                cin >> id_puesto;
                cin.ignore();
                cout << "Ingrese Nombre del Puesto: ";
                getline(cin, puesto);
                e = Puesto(id_puesto, puesto);
                e.actualizar();
                system("pause");
                break;
            case 4:
                system("cls");
                cout << "Ingrese ID a Eliminar: ";
                cin >> id_puesto;
                cin.ignore();
                e = Puesto(id_puesto, puesto);
                e.borrar();
                system("pause");
                break;
            case 0:
                goto inicio;
            default:
                cout << "opcion no valida! Intente de nuevo." << endl;
            }
        }
    case 2:
        while (true) {
            system("cls");
            cout << "Seleccione una Opcion:" << endl;
            cout << "1. Crear marca" << endl;
            cout << "2. Mostrar marcas" << endl;
            cout << "3. Actualizar marcas" << endl;
            cout << "4. Borrar marca" << endl;
            cout << "0. Salir" << endl;
            cout << "Ingrese una opcion: ";
            cin >> opcion2;

            switch (opcion2) {
            case 1:
                system("cls");
                cout << "Ingrese el Codigo de la marca: ";
                cin >> id_marca;
                cin.ignore();
                cout << "Ingrese Nombre de la marca: ";
                getline(cin, marca);
                mar = Marcas(id_marca, marca);
                mar.crear();
                system("pause");
                break;
            case 2:
                system("cls");
                mar.leer();
                system("pause");
                break;
            case 3:
                system("cls");
                cout << "Ingrese ID de marca a modificar: ";
                cin >> id_marca;
                cin.ignore();
                cout << "Ingrese Nuevo Nombre de la marca: ";
                getline(cin, marca);
                mar = Marcas(id_marca, marca);
                mar.actualizar();
                system("pause");
                break;
            case 4:
                system("cls");
                cout << "Ingrese ID de marca a Eliminar: ";
                cin >> id_marca;
                cin.ignore();
                mar = Marcas(id_marca, marca);
                mar.borrar();
                system("pause");
                break;
            case 0:
                goto inicio;
            default:
                cout << "opcion no valida! Intente de nuevo." << endl;
            }
        }
    case 3:
        while (true) { 
            system("cls");
            cout << "Seleccione una Opcion:" << endl;
            cout << "1. Crear Cliente" << endl;
            cout << "2. Mostrar Clientes" << endl;
            cout << "3. Actualizar Cliente" << endl;
            cout << "4. Borrar Cliente" << endl;
            cout << "0. Salir" << endl;
            cout << "Ingrese una opcion: ";
            cin >> opcion2;

            
            int id_cl = 0, tel = 0;
            string nom, ape, nit, correo, fn, dir, fecha_ing;
            bool gen = 0;

            switch (opcion2) {
            case 1: // CREAR
                system("cls");
                cin.ignore();
                cout << "Nombres: ";
                getline(cin, nom);
                cout << "Apellidos: ";
                getline(cin, ape);
                cout << "NIT: ";
                getline(cin, nit);
                cout << "Genero (0 = Mujer, 1 = Hombre): ";
                cin >> gen;
                cout << "Telefono: ";
                cin >> tel;
                cin.ignore();
                cout << "Correo Electronico: ";
                getline(cin, correo);
                cout << "Fecha Ingreso (YYYY-MM-DD): ";
                getline(cin, fecha_ing);

                
                cliente = Cliente(nom, ape, dir, gen, tel, fn, nit, correo, fecha_ing, id_cl);
                cliente.crear();
                system("pause");
                break;

            case 2: // LEER
                system("cls");
                cliente.leer();
                system("pause");
                break;

            case 3: // ACTUALIZAR
                system("cls");
                cout << "ID del cliente a modificar: ";
                cin >> id_cl;
                cin.ignore();
                cout << "Nombres: ";
                getline(cin, nom);
                cout << "Apellidos: ";
                getline(cin, ape);
                cout << "NIT: ";
                getline(cin, nit);
                cout << "Genero (0 = Mujer, 1 = Hombre): ";
                cin >> gen;
                cout << "Telefono: ";
                cin >> tel;
                cin.ignore();
                cout << "Correo Electronico: ";
                getline(cin, correo);
                cout << "Fecha Ingreso (YYYY-MM-DD): ";
                getline(cin, fecha_ing);

                cliente = Cliente(nom, ape, dir, gen, tel, fn, nit, correo, fecha_ing, id_cl);
                cliente.actualizar();
                system("pause");
                break;

            case 4: // ELIMINAR
                system("cls");
                cout << "ID del cliente a eliminar: ";
                cin >> id_cl;
                cin.ignore();

                cliente = Cliente(nom, ape, dir, gen, tel, fn, nit, correo, fecha_ing, id_cl);
                cliente.borrar();
                system("pause");
                break;

            case 0:
                cout << "Saliendo..." << endl;
                goto inicio;
                break;
            default:
                cout << "opcion no valida! Intente de nuevo." << endl;
            } 
        }
    case 4: while (true) { 
        system("cls");
        cout << "Seleccione una Opcion:" << endl;
        cout << "1. Crear Empleado" << endl;
        cout << "2. Mostrar Empleado" << endl;
        cout << "3. Actualizar Empleado" << endl;
        cout << "4. Borrar Empleado" << endl;
        cout << "0. Salir" << endl;
        cout << "Ingrese una opcion: ";
        cin >> opcion2;

        
        string nom, ape, dir, fn, fecha_ini_lab, fecha_ing;
        int tel = 0, id_puesto = 0, dpi = 0, id_empleado = 0;
        bool gen = 0;

        Empleado empleado;

        switch (opcion2) {
        case 1:
            system("cls");
            cin.ignore();
            cout << "Nombres: ";
            getline(cin, nom);
            cout << "Apellidos: ";
            getline(cin, ape);
            cout << "Direccion: ";
            getline(cin, dir);
            cout << "Genero (0 = Mujer, 1 = Hombre): ";
            cin >> gen;
            cout << "Telefono: ";
            cin >> tel;
            cin.ignore();
            cout << "DPI: ";
            cin >> dpi;
            cin.ignore();
            cout << "Fecha Nacimiento (YYYY-MM-DD): ";
            getline(cin, fn);
            
            ConexionBD cn;
            cn.abrir_conexion();
            if (cn.getConector()) {
                string consulta = "SELECT id_puesto, puesto FROM puesto";
                const char* c = consulta.c_str();
                if (!mysql_query(cn.getConector(), c)) {
                    MYSQL_RES* resultado = mysql_store_result(cn.getConector());
                    MYSQL_ROW fila;
                    cout << "\n------ PUESTOS DISPONIBLES ------" << endl;
                    while ((fila = mysql_fetch_row(resultado))) {
                        cout << "ID: " << fila[0] << " | Puesto: " << fila[1] << endl;
                    }
                    mysql_free_result(resultado);
                }
                else {
                    cout << "❌ Error al consultar puestos.\n";
                }
            }
            cn.cerrar_conexion();

            cout << "ID Puesto: ";
            cin >> id_puesto;
            cin.ignore();
            
            cout << "Fecha Ingreso (YYYY-MM-DD): ";
            getline(cin, fecha_ing);

            empleado = Empleado(nom, ape, dir, gen, tel, fn, dpi, id_puesto, fecha_ing, id_empleado);

            empleado.crear();
            system("pause");
            break;

        case 2:
            system("cls");
            empleado.leer();
            system("pause");
            break;

        case 3: 
            system("cls");
            cout << "ID del empleado a modificar: ";
            cin >> id_empleado;
            cin.ignore();

            cout << "Nombres: ";
            getline(cin, nom);
            cout << "Apellidos: ";
            getline(cin, ape);
            cout << "Direccion: ";
            getline(cin, dir);
            cout << "Genero (0 = Mujer, 1 = Hombre): ";
            cin >> gen;
            cout << "Telefono: ";
            cin >> tel;
            cin.ignore();
            cout << "DPI: ";
            cin >> dpi;
            cin.ignore();
            cout << "Fecha Nacimiento (YYYY-MM-DD): ";
            getline(cin, fn);

            
            {
                ConexionBD cn;
                cn.abrir_conexion();
                if (cn.getConector()) {
                    string consulta = "SELECT id_puesto, puesto FROM puesto";
                    const char* c = consulta.c_str();
                    if (!mysql_query(cn.getConector(), c)) {
                        MYSQL_RES* resultado = mysql_store_result(cn.getConector());
                        MYSQL_ROW fila;
                        cout << "\n------ PUESTOS NUEVO (ACTUALIZAR) ------" << endl;
                        while ((fila = mysql_fetch_row(resultado))) {
                            cout << "ID: " << fila[0] << " | Puesto: " << fila[1] << endl;
                        }
                        mysql_free_result(resultado);
                    }
                    else {
                        cout << "❌ Error al consultar puestos.\n";
                    }
                }
                cn.cerrar_conexion();
            }

            cout << "ID Puesto: ";
            cin >> id_puesto;
            cin.ignore();

            cout << "Fecha Ingreso (YYYY-MM-DD): ";
            getline(cin, fecha_ing);

            empleado = Empleado(nom, ape, dir, gen, tel, fn, dpi, id_puesto, fecha_ing, id_empleado);

            empleado.actualizar();
            system("pause");
            break;



        case 4: 

            system("cls");
            cout << "ID del empleado a eliminar: ";
            cin >> id_empleado;
            cin.ignore();

            empleado = Empleado(nom, ape, dir, gen, tel, fn, dpi, id_puesto, fecha_ing, id_empleado);

            empleado.borrar();
            system("pause");
            break;
        case 0:
            cout << "Saliendo..." << endl;
            goto inicio;
            break;
        default:
            cout << "opcion no valida! Intente de nuevo." << endl;
        } //TERMINA EL CASE 4: Empleado
    }
    case 5:
        menuVentas();
        goto inicio;
    case 6:
        menuCompras();
        goto inicio;
    case 0:
        cout << "Saliendo..." << endl;
        break;
    default:
        cout << "opcion no valida! Intente de nuevo." << endl;
        goto inicio;
    }

    return 0;
}

void menuVentas() {
    CRUDVentaDetalle venta;
    int opcion;
    do {
        cout << "\n==== SISTEMA DE VENTAS ====" << endl;
        cout << "1. Realizar Venta" << endl;
        cout << "2. Leer Ventas" << endl;
        cout << "3. Actualizar Venta" << endl;
        cout << "4. Eliminar Venta" << endl;
        cout << "0. Regresar al menu principal" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            venta.realizarVenta();
            break;
        case 2:
            venta.leerVentas();
            break;
        case 3:
            venta.actualizarVenta();
            break;
        case 4:
            venta.eliminarVenta();
            break;
      
        case 0:
            break;
        default:
            cout << "Opcion invalida. Intente nuevamente." << endl;
        }
    } while (opcion != 0);
}

void menuCompras() {
    CRUDCompraDetalle compra;
    int opcion;
    do {
        cout << "\n==== SISTEMA DE COMPRAS ====" << endl;
        cout << "1. Realizar Compra" << endl;
        cout << "2. Leer Compras" << endl;
        cout << "3. Actualizar Compra" << endl;
        cout << "4. Eliminar Compra" << endl;
        cout << "0. Regresar al menu principal" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            compra.realizarCompra();
            break;
        case 2:
            compra.leerCompras();
            break;
        case 3:
            compra.actualizarCompra();
            break;
        case 4:
            compra.eliminarCompra();
            break;
        case 0:
            break;
        default:
            cout << "Opcion invalida. Intente nuevamente." << endl;
        }
    } while (opcion != 0);
}

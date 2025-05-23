#include <iostream>
#include <string>
#include "Puestos.h"
#include "Marcas.h"
#include "venta.h"
#include "CRUDventaDetalle.h"
#include "compra.h"
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

inicio:
    system("cls");
    cout << "======== MENU GENERAL DEL SISTEMA ========" << endl;
    cout << "1. INGRESAR A PUESTOS" << endl;
    cout << "2. INGRESAR A MARCAS" << endl;
    cout << "3. INGRESAR A VENTAS" << endl;
    cout << "4. INGRESAR A COMPRAS" << endl;
    cout << "5. INGRESAR A BBB" << endl;
    cout << "0. Salir" << endl;
    cin >> opcion1;

    switch (opcion1) {
    case 1:
        while (true) {
            system("cls");
            cout << "===== MENU: PUESTOS =====" << endl;
            cout << "1. Crear Puesto" << endl;
            cout << "2. Mostrar Puestos" << endl;
            cout << "3. Actualizar Puesto" << endl;
            cout << "4. Borrar Puesto" << endl;
            cout << "0. Volver" << endl;
            cout << "Ingrese una opcion: ";
            cin >> opcion2;

            switch (opcion2) {
            case 1:
                system("cls");
                cout << "Ingrese el Codigo del Puesto: ";
                cin >> id_puesto;
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
                e = Puesto(id_puesto, puesto);
                e.borrar();
                system("pause");
                break;
            case 0:
                goto inicio;
            default:
                cout << "Opción no válida." << endl;
            }
        }

    case 2:
        while (true) {
            system("cls");
            cout << "===== MENU: MARCAS =====" << endl;
            cout << "1. Crear Marca" << endl;
            cout << "2. Mostrar Marcas" << endl;
            cout << "3. Actualizar Marca" << endl;
            cout << "4. Borrar Marca" << endl;
            cout << "0. Volver" << endl;
            cout << "Ingrese una opcion: ";
            cin >> opcion2;

            switch (opcion2) {
            case 1:
                system("cls");
                cout << "Ingrese el Codigo de la Marca: ";
                cin >> id_marca;
                cin.ignore();
                cout << "Ingrese Nombre de la Marca: ";
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
                cout << "Ingrese ID de Marca a modificar: ";
                cin >> id_marca;
                cin.ignore();
                cout << "Ingrese Nuevo Nombre de la Marca: ";
                getline(cin, marca);
                mar = Marcas(id_marca, marca);
                mar.actualizar();
                system("pause");
                break;
            case 4:
                system("cls");
                cout << "Ingrese ID de Marca a Eliminar: ";
                cin >> id_marca;
                mar = Marcas(id_marca, marca);
                mar.borrar();
                system("pause");
                break;
            case 0:
                goto inicio;
            default:
                cout << "Opción no válida." << endl;
            }
        }

    case 3:
        menuVentas();
        goto inicio;
    case 4:
        menuCompras();
        goto inicio;
    case 0:
        cout << "Saliendo del sistema..." << endl;
        break;
    default:
        cout << "Opción inválida." << endl;
        goto inicio;
    }

    return 0;
}



void menuVentas() {
    int opcion;
    do {
        cout << "\n====== MENU VENTAS ======" << endl;
        cout << "1. Crear venta con detalles" << endl;
        cout << "2. Ver ventas" << endl;
        cout << "3. Actualizar venta" << endl;
        cout << "4. Eliminar venta" << endl;
        cout << "5. Ver detalles de una venta" << endl;
        cout << "0. Volver al menu principal" << endl;
        cout << "Selecciona una opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            int num_factura, id_cliente, id_empleado, total_productos, id_producto;
            string serie, fecha_factura, fecha_ingreso, cantidad;
            double precio_unitario;

            cout << "No. Factura: "; cin >> num_factura;
            cout << "Serie: "; cin >> serie;
            cout << "Fecha Factura (YYYY-MM-DD): "; cin >> fecha_factura;
            cout << "ID Cliente: "; cin >> id_cliente;
            cout << "ID Empleado: "; cin >> id_empleado;
            cin.ignore();
            cout << "Fecha Ingreso (YYYY-MM-DD HH:MM:SS): "; getline(cin, fecha_ingreso);

            Venta venta(num_factura, serie, fecha_factura, id_cliente, id_empleado, fecha_ingreso);
            if (venta.crear()) {
                cout << "Cantidad de productos a registrar: "; cin >> total_productos;
                for (int i = 0; i < total_productos; ++i) {
                    cout << "\n--- Producto " << (i + 1) << " ---" << endl;
                    cout << "ID Producto: "; cin >> id_producto;
                    cout << "Cantidad: "; cin >> cantidad;
                    cout << "Precio Unitario: "; cin >> precio_unitario;

                    CRUDVentaDetalle detalle(num_factura, id_producto, cantidad, precio_unitario);
                    detalle.crear();
                }
            }
        }
        else if (opcion == 2) {
            Venta v;
            v.leer();
        }
        else if (opcion == 3) {
            int id;
            int num_factura, id_cliente, id_empleado;
            string serie, fecha_factura, fecha_ingreso;

            cout << "ID de la venta a actualizar: "; cin >> id;
            cout << "Nuevo No. Factura: "; cin >> num_factura;
            cout << "Nueva Serie: "; cin >> serie;
            cout << "Nueva Fecha Factura: "; cin >> fecha_factura;
            cout << "Nuevo ID Cliente: "; cin >> id_cliente;
            cout << "Nuevo ID Empleado: "; cin >> id_empleado;
            cin.ignore();
            cout << "Nueva Fecha Ingreso: "; getline(cin, fecha_ingreso);

            Venta v(num_factura, serie, fecha_factura, id_cliente, id_empleado, fecha_ingreso);
            v.actualizar(id);
        }
        else if (opcion == 4) {
            int id;
            cout << "ID de la venta a eliminar: "; cin >> id;

            CRUDVentaDetalle cd;
            cd.eliminarPorVenta(id);

            Venta v;
            v.eliminar(id);
        }
        else if (opcion == 5) {
            int id;
            cout << "ID de la venta: "; cin >> id;
            CRUDVentaDetalle d;
            d.leer(id);
        }

    } while (opcion != 0);
}



void menuCompras() {
    int opcion;
    do {
        cout << "\n====== MENU COMPRAS ======" << endl;
        cout << "1. Crear compra con detalles" << endl;
        cout << "2. Ver compras" << endl;
        cout << "3. Actualizar compra" << endl;
        cout << "4. Eliminar compra" << endl;
        cout << "5. Ver detalles de una compra" << endl;
        cout << "0. Volver al menu principal" << endl;
        cout << "Selecciona una opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            int no_orden, id_proveedor, total_productos, id_producto;
            string fecha_orden, fecha_ingreso, cantidad;
            double precio_unitario;

            cout << "No. Orden de Compra: "; cin >> no_orden;
            cout << "ID Proveedor: "; cin >> id_proveedor;
            cout << "Fecha Orden (YYYY-MM-DD): "; cin >> fecha_orden;
            cin.ignore();
            cout << "Fecha Ingreso (YYYY-MM-DD HH:MM:SS): "; getline(cin, fecha_ingreso);

            Compra compra(no_orden, id_proveedor, fecha_orden, fecha_ingreso);
            if (compra.crear()) {
                cout << "Cantidad de productos a registrar: "; cin >> total_productos;
                for (int i = 0; i < total_productos; ++i) {
                    cout << "\n--- Producto " << (i + 1) << " ---" << endl;
                    cout << "ID Producto: "; cin >> id_producto;
                    cout << "Cantidad: "; cin >> cantidad;
                    cout << "Precio Costo Unitario: "; cin >> precio_unitario;

                    CRUDCompraDetalle detalle(no_orden, id_producto, cantidad, precio_unitario);
                    detalle.crear();
                }
            }
        }
        else if (opcion == 2) {
            Compra c;
            c.leer();
        }
        else if (opcion == 3) {
            int id, no_orden, id_proveedor;
            string fecha_orden, fecha_ingreso;

            cout << "ID de la compra a actualizar: "; cin >> id;
            cout << "Nuevo No. Orden: "; cin >> no_orden;
            cout << "Nuevo ID Proveedor: "; cin >> id_proveedor;
            cout << "Nueva Fecha Orden: "; cin >> fecha_orden;
            cin.ignore();
            cout << "Nueva Fecha Ingreso: "; getline(cin, fecha_ingreso);

            Compra c(no_orden, id_proveedor, fecha_orden, fecha_ingreso);
            c.actualizar(id);
        }
        else if (opcion == 4) {
            int id;
            cout << "ID de la compra a eliminar: "; cin >> id;

            CRUDCompraDetalle cd;
            cd.eliminarPorCompra(id);

            Compra c;
            c.eliminar(id);
        }
        else if (opcion == 5) {
            int id;
            cout << "ID de la compra: "; cin >> id;
            CRUDCompraDetalle d;
            d.leer(id);
        }

    } while (opcion != 0);
}

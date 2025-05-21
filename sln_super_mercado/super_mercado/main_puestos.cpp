#include <iostream>
#include "Puestos.h"
#include "Marcas.h"

using namespace std;

int main() {
    string puesto;
    int id_puesto, id_marca = 0;
    int opcion1, opcion2;
    Puesto e;

    cout << "INGRESE UNA OPERACION" << endl;
    cout << "1.INGRESAR A PUESTOS" << endl;
    cout << "2.INGRESAR A MARCAS" << endl;
    cout << "3.INGRESAR A  AAA" << endl;
    cout << "4.INGRESAR A BBB" << endl;
    cout << "5.INGRESAR A CCC" << endl;
    cin >> opcion1;

    switch (opcion1){
    case 1:
       while (true) { //ACA EMPIEZA EL MENU: PUESTOS
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
                cout << "Saliendo..." << endl;
                return 0;
            default:
                cout << "opcion no valida! Intente de nuevo." << endl;
            }

        }   // aca termina el switch case 1: puestos

    case 2:
        while (true) { //ACA EMPIEZA EL MENU: Marcas
            system("cls");
            cout << "Seleccione una Opcion:" << endl;
            cout << "1. Crear puesto" << endl;
            cout << "2. Mostrar Puestos" << endl;
            cout << "3. Actualizar Puesto" << endl;
            cout << "4. Borrar Puesto" << endl;
            cout << "0. Salir" << endl;
            cout << "Ingrese una opcion: ";
            cin >> opcion2;
            if (opcion2 == 0) {
                cout << "hola"<<endl;
            }
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
                cout << "Saliendo..." << endl;
                return 0;
            default:
                cout << "opcion no valida! Intente de nuevo." << endl;
            }

        }   // aca termina el switch case 2: marcas

    default:
        cout << "opcion no valida! Intente de nuevo." << endl;
        break;
    }
    return 0;
}


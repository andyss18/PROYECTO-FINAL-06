#pragma once
#include "ConexionBD.h"
#include <iostream>
#include <mysql.h>
#include <string>

	using namespace std;
	class Marcas {
		//atributos
	private: string marc;
		   int id_m = 0;
	
	public:
		//constructor
		Marcas() {}
		Marcas(int id_marca, string marca) {
			marc=marca;
			id_m=id_marca;
		}
		// SET
//		void setId_Marca(int idm) { id_marca = idm; }
//		void setmarca(string m) { marca = m; }

//		//GET	
//		int getId_Puesto() { return id_marca; }
//		string getPuesto() { return puesto; }

		//metodos
		void crear() {

			int q_estado = 0;
			ConexionBD cn = ConexionBD();
			cn.abrir_conexion();
			if (cn.getConector()) {
				string id_mm = to_string(id_m);
				string consulta = "INSERT INTO marca(id_marca, marca) VALUES (" + id_mm + ",'"+marc+"');";
				const char* c = consulta.c_str();
				q_estado = mysql_query(cn.getConector(), c);

				if (!q_estado) {

					cout << "--- Ingreso de Datos Exitoso !!!" << endl;
				}
				else {
					cout << "XXXX Consulta Fallida XXXX" << endl;
				}
			}
			else {
				cout << "XXX Conexion Fallida XXX" << endl;
			}
			cn.cerrar_conexion();
		}
		void leer() {
			int q_estado;
			ConexionBD cn;
			MYSQL_ROW fila;
			MYSQL_RES* resultado;

			cn.abrir_conexion();

			if (cn.getConector() != nullptr) {
				cout << "______ MARCAS ______" << endl;

				string consulta = "SELECT id_marca AS id, marca FROM marca;";
				const char* c = consulta.c_str();
				q_estado = mysql_query(cn.getConector(), c);
				if (!q_estado) {
					resultado = mysql_store_result(cn.getConector());
					while ((fila = mysql_fetch_row(resultado))) {
						cout << fila[0] << " | " << fila[1] << endl;
					}
				}
				else {
					cout << " XXX Consulta Fallo XXX" << endl;
				}
			}
			else {
				cout << " XXX Fallon la Conexion" << endl;
			}
			cn.cerrar_conexion();
		}
		void actualizar() {
			int q_estado = 0;
			ConexionBD cn = ConexionBD();
			cn.abrir_conexion();
			if (cn.getConector() != nullptr) {

				string idm = to_string(id_m);
				string consulta = "UPDATE marca SET marca = '" + marc + "' WHERE id_marca = " + idm;
				const char* c = consulta.c_str();
				q_estado = mysql_query(cn.getConector(), c);
				if (!q_estado) {
					cout << "--- Modificacion de Datos Exitoso !!!" << endl;
				}	
				else {
					cout << "XXXX Consulta Fallida XXXX" << endl;
				}
			}
			else {
				cout << "XXX Conexion Fallida XXX" << endl;
			}
			cn.cerrar_conexion();
		}
		void borrar() {
			int q_estado = 0;
			ConexionBD cn = ConexionBD();
			cn.abrir_conexion();
			if (cn.getConector()) {

				string idm = to_string(id_m);
				string consulta = "delete from marca  where id_marca = " + idm + "";

				const char* c = consulta.c_str();
				q_estado = mysql_query(cn.getConector(), c);
				if (!q_estado) {
					cout << "--- Eliminacion de Datos Exitoso !!!" << endl;
				}
				else {
					cout << "XXXX Consulta Fallida XXXX" << endl;
				}
			}
			else {
				cout << "XXX Conexion Fallida XXX" << endl;
			}
			cn.cerrar_conexion();
		}
	};


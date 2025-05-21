#pragma once
#include "ConexionBD.h"
#include <iostream>
#include <mysql.h>
#include <string>

using namespace std;
class Puesto {
	//atributos
private: string puesto;
	   int id_puesto = 0;
public:
	//constructor
	Puesto() {}
	Puesto(int id_p, string pt) {
		puesto = pt;
		id_puesto = id_p;
	}
	// SET
	void setId_Puesto(int idp) { id_puesto = idp; }
	void setPuesto(string p) { puesto = p; }
	
	//GET	
	int getId_Puesto()  { return id_puesto; }
	string getPuesto() { return puesto; }

	//metodos
	void crear() {
		int q_estado = 0;
		ConexionBD cn = ConexionBD();
		cn.abrir_conexion();
		if (cn.getConector()) {
			string id_pt = to_string(id_puesto);
			string consulta = "INSERT INTO puesto(id_puesto, puesto) VALUES (" + id_pt + ",'" + puesto + "');";
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConector(), c);
			
			if (!q_estado) {
				
				cout << "--- Ingreso de Datos Exitoso !!!" << endl;
			}else {
				cout << "XXXX Consulta Fallida XXXX" << endl;
			}
		}else{
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
			cout << "______ PUESTOS ______" << endl;

			string consulta = "SELECT id_puesto AS id, puesto FROM puesto;";
			const char* c = consulta.c_str(); 
			q_estado = mysql_query(cn.getConector(), c); 
			if (!q_estado) {
				resultado = mysql_store_result(cn.getConector());
				while ((fila = mysql_fetch_row(resultado))) { 
					cout << fila[0] << " | " << fila[1] << endl;
				}
			}else {
				cout << " XXX Consulta Fallo XXX" << endl;
			}
		}else {
			cout << " XXX Fallon la Conexion" << endl;
		}
		cn.cerrar_conexion();
	}
	void actualizar() {
		int q_estado = 0;
		ConexionBD cn = ConexionBD();
		cn.abrir_conexion();
		if (cn.getConector() != nullptr)  {

			string id_pt = to_string(id_puesto);
			string consulta = "UPDATE puesto SET puesto = '" + puesto + "' WHERE id_puesto = " + id_pt;
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConector(), c);
			if (!q_estado) {
				cout << "--- Modificacion de Datos Exitoso !!!" << endl;
			}else {
				cout << "XXXX Consulta Fallida XXXX" << endl;
			}
		}else {
			cout << "XXX Conexion Fallida XXX" << endl;
		}
		cn.cerrar_conexion();
	}
	void borrar() {
		int q_estado = 0;
		ConexionBD cn = ConexionBD();
		cn.abrir_conexion();
		if (cn.getConector()) {

			string id_pt = to_string(id_puesto);
			string consulta = "delete from puesto  where id_puesto = " + id_pt + "";

			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConector(), c);
			if (!q_estado) {
				cout << "--- Eliminacion de Datos Exitoso !!!" << endl;
			}else {
				cout << "XXXX Consulta Fallida XXXX" << endl;
			}
		}else {
			cout << "XXX Conexion Fallida XXX" << endl;
		}
		cn.cerrar_conexion();

	}
};	
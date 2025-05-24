#pragma once
#include "ConexionBD.h"
#include<iostream>
#include <mysql.h>
#include <string>

using namespace std;

class Proveedor
{
	//atributos
private: string proveedor, nit, direccion;
	   int id_proveedor = 0;
	   int telefono = 0;
	   //constructor
public:
	Proveedor() {}
	Proveedor(int idp, string prov, string n, string dir, int tel) {
		id_proveedor = idp;
		proveedor = prov;
		nit = n;
		direccion = dir;
		telefono = tel;
	}
	//metodos get y set
	// SET
	void setId_proveedor(int idp) { id_proveedor = idp; }
	void setProveedor(string prov) { proveedor = prov; }
	void setNit(string n) { nit = n; }
	void setDireccion(string dir) { direccion = dir; }
	void setTelefono(int t) { telefono = t; }

	//GET
	int getId_proveedor() { return id_proveedor; }
	string getProveedor() { return proveedor; }
	string getNit() { return nit; }
	string getDireccion() { return direccion; }
	int getTelefono() { return telefono; }



	//metodos
	void crear() {
		int q_estado = 0;
		ConexionBD cn = ConexionBD();
		cn.abrir_conexion();
		if (cn.getConector()) {
			string t = to_string(telefono);
			string idp = to_string(id_proveedor);
			string consulta = "INSERT INTO proveedores(id_proveedor, proveedor, nit, direccion, telefono) VALUES (" + idp + ",'" + proveedor + "','" + nit + "','" + direccion + "'," + t + ");";
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConector(), c);
			if (!q_estado) {
				cout << "Ingreso de Datos Exitoso..." << endl;
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
			cout << "______ PROVEEDORES ______" << endl;

			string consulta = "SELECT id_proveedor AS id, proveedor, nit, direccion, telefono FROM proveedores;";
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConector(), c);
			if (!q_estado) {
				resultado = mysql_store_result(cn.getConector());
				while ((fila = mysql_fetch_row(resultado))) {
					cout << fila[0] << " , " << fila[1] << "," << fila[2] << "," << fila[3] << "," << fila[4] << endl;
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

			string idp = to_string(id_proveedor);
			string t = to_string(telefono);
			string consulta = "UPDATE proveedores SET "
				"proveedor = '" + proveedor + "', "
				"nit = '" + nit + "', "
				"direccion = '" + direccion + "', "
				"telefono = '" + t + "' "
				"WHERE id_proveedor = " + idp + ";";
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

			string idp = to_string(id_proveedor);
			string consulta = "delete from proveedores  where id_proveedor = " + idp + "";

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

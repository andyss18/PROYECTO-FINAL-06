#pragma once
#include "Persona.h"
#include "ConexionBD.h"
#include <iostream>
#include <mysql.h>
#include <string>

using namespace std;

class Cliente : Persona {
	//atributos
private: string nit, correo, fecha_ingreso;
	   int id_cliente = 0;
	//constructor
public : 
	Cliente (){}
	Cliente (string nom, string ape, string dir, bool gen, int tel, string fn, string n, string c,string fi, int id_cl) : Persona (nom,ape,dir,gen,tel,fn) {
		nit = n;
		correo = c;
		fecha_ingreso = fi;
		id_cliente = id_cl;
	}
	// SET
	void setId_cliente(int cl) { id_cliente = cl; }
	void setNombres(string no) { nombres = no; }
	void setApellidos(string a) { apellidos = a; }
	void setNit(string ni) { nit = ni; }
	void setGenero(boolean g) { genero = g; }
	void setTelefono(int t) { telefono = t; }
	void setCorreo(string c) { correo = c; }
	void setFecha_ingreso(string fi) { fecha_ingreso = fi; }

	// GET
	int getId_cliente() { return id_cliente; }
	string getNombres() { return nombres; }
	string getApellidos() { return apellidos; }
	string getNit() { return nit; }
	boolean getGenero() { return genero; }
	int getTelefono() { return telefono; }
	string getCorreo_electronico() { return correo; }
	string getFecha_ingreso() { return fecha_ingreso; }

	
	//metodos
	void crear() {
		int q_estado;
		ConexionBD cn = ConexionBD();
		cn.abrir_conexion();
		if (cn.getConector()) {
			string t = to_string(telefono);
			string g = to_string(genero);
			string insert = "INSERT INTO cliente(nombres, apellidos, nit, genero, telefono, correo_electronico, fecha_ingreso) VALUES ('" + nombres + "','" + apellidos + "','" + nit + "'," + g + "," + t + ",'" + correo + "','" + fecha_ingreso + "');";
			const char* i = insert.c_str();
			q_estado = mysql_query(cn.getConector(), i);
			if (!q_estado)
				cout << "Inserción exitosa..." << endl;
			else
				cout << "Error al insertar..." << endl;
		}
		else {
			cout << "Fallo la conexión." << endl;
		}
		cn.cerrar_conexion();
	}

	     
	
	void leer(){
		int q_estado = 0;
		ConexionBD cn = ConexionBD();
		MYSQL_ROW fila;
		MYSQL_RES* resultado;
		cn.abrir_conexion();
		if (cn.getConector()) {
			cout << "____ Datos del Cliente ________" << endl;
			string consulta = "select * from cliente;";
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConector(), c);
			if (!q_estado) {
				resultado = mysql_store_result(cn.getConector());
				while (fila = mysql_fetch_row(resultado)) {
					cout << fila[0] << "," << fila[1] << "," << fila[2] << "," << fila[3] << "," << fila[4] << "," << fila[5] << "," << fila[6] << "," << fila[7]<<endl;


				}
			}

		}else {
			cout << "XxXX Fallo la Conexion XXXX" << endl;
		}
		cn.cerrar_conexion();
    }
	void actualizar() {
		int q_estado;
		ConexionBD cn = ConexionBD();
		cn.abrir_conexion();
		if (cn.getConector()) {
			string t = to_string(telefono);
			string g = to_string(genero);
			string id = to_string(id_cliente);
			string update = "UPDATE cliente SET nombres='" + nombres + "', apellidos='" + apellidos + "', nit='" + nit + "', genero=" + g + ", telefono=" + t + ", correo_electronico='" + correo + "', fecha_ingreso='" + fecha_ingreso + "' WHERE id_cliente=" + id + ";";
			const char* u = update.c_str();
			q_estado = mysql_query(cn.getConector(), u);
			if (!q_estado)
				cout << "Actualización exitosa..." << endl;
			else
				cout << "Error al actualizar..." << endl;
		}
		else {
			cout << "Fallo la conexión." << endl;
		}
		cn.cerrar_conexion();
	}

	//void borrar(){}
	void borrar() {
		int q_estado;
		ConexionBD cn = ConexionBD();
		cn.abrir_conexion();
		if (cn.getConector()) {
			string id = to_string(id_cliente);
			string del = "DELETE FROM cliente WHERE id_cliente=" + id + ";";
			const char* d = del.c_str();
			q_estado = mysql_query(cn.getConector(), d);
			if (!q_estado)
				cout << "Eliminación exitosa..." << endl;
			else
				cout << "Error al eliminar..." << endl;
		}
		else {
			cout << "Fallo la conexión." << endl;
		}
		cn.cerrar_conexion();
	}

		
};


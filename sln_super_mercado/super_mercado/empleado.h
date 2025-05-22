#pragma once
#include "Persona.h"
#include "ConexionBD.h"
#include <iostream>
#include <mysql.h>
#include <string>

using namespace std;

class Empleado : Persona {
private:
	int id_empleado = 0, id_puesto = 0;
	string dpi, fecha_nacimiento, fecha_inicio_labores, fecha_ingreso;

public:
	Empleado() {}
	Empleado(string nom, string ape, string dir, bool gen, int tel, string fn,
		string d, int id_p, string fil, string fi, int id_e)
		: Persona(nom, ape, dir, gen, tel, fn) {
		dpi = d;
		id_puesto = id_p;
		fecha_inicio_labores = fil;
		fecha_ingreso = fi;
		id_empleado = id_e;
		fecha_nacimiento = fn;
	}

	// SET
	void setId_empleado(int id) { id_empleado = id; }
	void setDpi(string d) { dpi = d; }
	void setId_puesto(int p) { id_puesto = p; }
	void setFecha_nacimiento(string fn) { fecha_nacimiento = fn; }
	void setFecha_inicio_labores(string fil) { fecha_inicio_labores = fil; }
	void setFecha_ingreso(string fi) { fecha_ingreso = fi; }

	// GET
	int getId_empleado() { return id_empleado; }
	string getDpi() { return dpi; }
	int getId_puesto() { return id_puesto; }
	string getFecha_nacimiento() { return fecha_nacimiento; }
	string getFecha_inicio_labores() { return fecha_inicio_labores; }
	string getFecha_ingreso() { return fecha_ingreso; }

	// MÉTODOS
	void crear() {
		int q_estado;
		ConexionBD cn = ConexionBD();
		cn.abrir_conexion();
		if (cn.getConector()) {
			string t = to_string(telefono);
			string g = to_string(genero);
			string p = to_string(id_puesto);
			string insert = "INSERT INTO empleado(nombres, apellidos, direccion, telefono, dpi, genero, fecha_nacimiento, id_puesto, fecha_inicio_labores, fecha_ingreso) VALUES ('" + nombres + "','" + apellidos + "','" + direccion + "'," + t + ",'" + dpi + "'," + g + ",'" + fecha_nacimiento + "'," + p + ",'" + fecha_inicio_labores + "','" + fecha_ingreso + "');";
			const char* i = insert.c_str();
			q_estado = mysql_query(cn.getConector(), i);
			if (!q_estado)
				cout << "Empleado insertado exitosamente..." << endl;
			else {
				cout << "Error al insertar empleado..." << endl;
				cerr << "MySQL Error: " << mysql_error(cn.getConector()) << endl;
			}

		}
		else {
			cout << "Fallo la conexión." << endl;
		}
		cn.cerrar_conexion();
	}

	void leer() {
		int q_estado = 0;
		ConexionBD cn = ConexionBD();
		MYSQL_ROW fila;
		MYSQL_RES* resultado;
		cn.abrir_conexion();
		if (cn.getConector()) {
			cout << "____ Datos de Empleados ________" << endl;
			string consulta = "SELECT * FROM empleado;";
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConector(), c);
			if (!q_estado) {
				resultado = mysql_store_result(cn.getConector());
				while ((fila = mysql_fetch_row(resultado))) {
					cout << fila[0] << " | " << fila[1] << " | " << fila[2] << " | " << fila[3]
						<< " | " << fila[4] << " | " << fila[5] << " | " << fila[6]
						<< " | " << fila[7] << " | " << fila[8] << " | " << fila[9]
						<< " | " << fila[10] << endl;
				}
			}
		}
		else {
			cout << "Fallo la conexión." << endl;
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
			string p = to_string(id_puesto);
			string id = to_string(id_empleado);
			string update = "UPDATE empleado SET nombres='" + nombres + "', apellidos='" + apellidos + "', direccion='" + direccion + "', telefono=" + t + ", dpi='" + dpi + "', genero=" + g + ", fecha_nacimiento='" + fecha_nacimiento + "', id_puesto=" + p + ", fecha_inicio_labores='" + fecha_inicio_labores + "', fecha_ingreso='" + fecha_ingreso + "' WHERE id_empleado=" + id + ";";
			const char* u = update.c_str();
			q_estado = mysql_query(cn.getConector(), u);
			if (!q_estado)
				cout << "Empleado actualizado exitosamente..." << endl;
			else
				cout << "Error al actualizar empleado..." << endl;
		}
		else {
			cout << "Fallo la conexión." << endl;
		}
		cn.cerrar_conexion();
	}

	void borrar() {
		int q_estado;
		ConexionBD cn = ConexionBD();
		cn.abrir_conexion();
		if (cn.getConector()) {
			string id = to_string(id_empleado);
			string del = "DELETE FROM empleado WHERE id_empleado=" + id + ";";
			const char* d = del.c_str();
			q_estado = mysql_query(cn.getConector(), d);
			if (!q_estado)
				cout << "Empleado eliminado exitosamente..." << endl;
			else
				cout << "Error al eliminar empleado..." << endl;
		}
		else {
			cout << "Fallo la conexión." << endl;
		}
		cn.cerrar_conexion();
	}
};

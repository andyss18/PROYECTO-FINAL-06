#pragma once
#include <iostream>

using namespace std;

class Persona{
	//atributos
public : string nombres, apellidos, direccion, fecha_nacimiento;
		 int telefono = 0; 
		 bool genero = false;

		 //constructor
		 Persona () {}
		 Persona (string nom, string ape, string dir, bool gen, int tel,  string fn) {
			 nombres = nom;
			 apellidos = ape;
			 direccion = dir;
			 genero = gen;
			 telefono = tel;
			 fecha_nacimiento = fn;
		 }
		 //metodos
};


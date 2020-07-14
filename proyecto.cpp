#include<stdio.h>
#include<stdlib.h>

struct fecha{
	int yy;
	int mm;
	int dd; 
};

struct lugar{
	char ciudad[40];
	char direccion[40];
};

struct infracciones{
	int numeroInfraccion;
	struct fecha fechaInfraccion;
	char tipoInfraccion[40];
	int monto;
	int pagado;
};

struct vehiculos{
	char placa[10];
	char marca[10];
	char modelo[10];
	struct fecha yyVehiculo;
	char color[10];
	struct infracciones * datosInfraccion;
};

struct persona{
	long int cedula;
	char nombre[20];
	struct fecha fechaNacimiento;
	struct lugar direccionNacimiento;
	struct persona *personaProx;
};



int main(){

	return 0;
}




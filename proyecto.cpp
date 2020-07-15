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
	
	int opcion = 1;
	
	while(opcion){
		printf("\t\t\t\t\tMENU DE CONTROL DE MULTAS\n");
		printf("\t\t\t\tALCALDIA DEL MUNICIPIO DE CHACAO, CARACAS\n\n");
		printf("\t\t\t\t {POR FAVOR ESCRIBA LA OPCION QUE DESEA}\n\n");
		printf("\t\t\t\t\t(1)--MANTENIMIENTO\n");
		printf("\t\t\t\t\t(2)--OPERACIONES Y CONSULTAS\n");
		printf("\t\t\t\t\t(3)--SALIR\n\n\t\t\t\t\t\t\t");
		scanf("%i",&opcion);
		system("cls");
	}
		
	
	return 0;
}




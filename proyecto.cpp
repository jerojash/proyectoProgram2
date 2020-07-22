#include<stdio.h>
#include<stdlib.h>
#include"iostream"
#include <string.h>

using namespace std;

struct fecha{
	int yy;
	int mm;
	int dd; 
};

struct lugar{
	char ciudad[80];
	char direccion[80];
};

struct infraccion{
	int numeroInfraccion;
	struct fecha fechaInfraccion;
	char tipoInfraccion[40];
	int monto;
	int pagado;
	struct infraccion *infraccionProx;
};

struct vehiculo{
	char placa[10];
	char marca[10];
	char modelo[10];
	struct fecha annio;
	char color[10];
	struct vehiculo *vehiculoProx;
	struct infraccion * datosInfraccion;
};

struct persona{
	char nombre[40];
	char apellidos[40];
	long int cedula;
	struct fecha fechaNacimiento;
	struct lugar place;
	struct persona *personaProx;
	struct vehiculo *datosVehiculo;
};

void freeBuffer(){
	char c;
	while ((c = getchar()) != '\n' && c != EOF);
}

struct persona *p = NULL; 

void encabezado();

int validarCedula(struct persona *n, int x);

void agregarPersona(struct persona **p);

void menuPersonas();

void menuVehiculos();

void menuMantenimiento();

void menuConsultas();

void menuOperacionesConsultas();


int main(){         //*************************FUNCION PRINCIPAL***************************

	int opcion = 1;	
	while(opcion){ //   **************************MENU PRINCIPAL*************************
		encabezado();
		printf("\t\t\t\t {POR FAVOR ESCRIBA LA OPCION QUE DESEA}\n\n");
		printf("\t\t\t\t\t(1)--MANTENIMIENTO\n");
		printf("\t\t\t\t\t(2)--OPERACIONES Y CONSULTAS\n\n");
		printf("\t\t\t\t\t(0)--SALIR\n\n\t\t\t\t\t\t\t");
		scanf("%i",&opcion);
		system("cls");
		
		switch (opcion){
			case 1: menuMantenimiento();//LLAMADA A LA FUNCION menuMantenimiento
				break;
			case 2: menuOperacionesConsultas();//LLAMADA A LA FUNCION menuOperaciones
				break;
		}
	}
	return 0;
}


void encabezado(){
		printf("\t\t\t\t\tMENU DE CONTROL DE MULTAS\n");
		printf("\t\t\t\tALCALDIA DEL MUNICIPIO DE CHACAO, CARACAS\n\n");
}

int validarCedula(struct persona *n, int x, int cont){ //Devuelve 1 si lo encuentra. Devuelve 0 si no.
	if (n){
			if (n->cedula == x) return cont; //Se encontro una cedula igual, es verdadero
			else return validarCedula(n->personaProx, x, ++cont);
	}else return 0; //Es decir que no se encontró ninguna cedula igual, es falso
}

struct vehiculo * agregarVehiculo(){

	freeBuffer();
	struct vehiculo *auxVehiculo = new struct vehiculo;  //RESERVO MEMORIA DEL TIPO DE ESTRUCTURA DEL VEHICULO
	printf("\n\t\t\tIngrese la placa (8 caracteres max): "); 
	gets(auxVehiculo->placa);
	while(strlen(auxVehiculo->placa)>8){                                     //**********VALIDACION DEL NOMBRE*****************************
		printf("\n\n\t\t\t\tSolo se permiten max 8 caracteres\n\n");
		system("pause");
		system("cls");
		printf("\n\t\t\tIngrese la placa (8 caracteres max): "); 
		gets(auxVehiculo->placa);
	}
	printf("\n\t\t\tIngrese la marca del vehiculo: "); 
	gets(auxVehiculo->marca);
	printf("\n\t\t\tIngrese el modelo del vehiculo: "); 
	gets(auxVehiculo->modelo);
	printf("\n\t\t\tIngrese el a%co (yyyy): ",164); 
	scanf("%i",&auxVehiculo->annio.yy);
	printf("\n\t\t\tIngrese el color del vehiculo: "); 
	gets(auxVehiculo->color);
	
	auxVehiculo->datosInfraccion = NULL;
	
	return auxVehiculo;
}

void agregarPersona(struct persona **p){
	
	freeBuffer();
	int num = 0;
	struct persona *aux = new struct persona;
	system("cls");
	
	printf("\n\t\t\tIngrese el nombre (20 caracteres max): "); 
	gets(aux->nombre);
	
	while(strlen(aux->nombre)>20){                                     //******************VALIDACION DEL NOMBRE********************
		printf("\n\n\t\t\t\tSolo se permiten max 20 caracteres\n\n");
		system("pause");
		system("cls");
		printf("\n\t\t\tIngrese el nombre (20 caracteres max): "); 
		gets(aux->nombre);
	}
	
	printf("\n\t\t\tIngrese los apellidos (20 caracteres max): "); 
	gets(aux->apellidos);
	
	while(strlen(aux->apellidos)>20){                                //********************VALIDACION DEL APELLIDO*****************************
		printf("\n\n\t\t\t\tSolo se permiten max 20 caracteres\n\n");
		system("pause");
		system("cls");
		printf("\n\t\t\tIngrese el nombre (20 caracteres max): %s",aux->nombre);
		printf("\n\n\t\t\tIngrese los apellidos (20 caracteres max): "); 
		gets(aux->apellidos);
	}
	
	printf("\n\t\t\tIngrese la cedula: ");
	scanf("%li",&aux->cedula);
	
	while(validarCedula((*p), aux->cedula, num)||(aux->cedula<=0)){      //*****************VALIDACION DE CEDULA***********************
		system("cls");
		printf("\n\n\t\t\tEsa cedula ya esta registrada en el sistema o es una cedula invalida.\n\n");
		system("pause");
		system("cls");
		printf("\n\t\t\tIngrese el nombre (20 caracteres max): %s",aux->nombre);
		printf("\n\n\t\t\tIngrese los apellidos (20 caracteres max): %s",aux->apellidos);
		printf("\n\n\t\t\tIngrese la cedula: ");
		scanf("%li",&aux->cedula);
	}
	
	printf("\n\t\t\tIngrese el dia (dd) de nacimiento: ");
	cin>>(*aux).fechaNacimiento.dd;
	
	while(aux->fechaNacimiento.dd>31||(aux->fechaNacimiento.dd<=0)){ //**********VALIDACION DE DIA DE NACIMIENTO************************
		system("cls");
		printf("\n\n\t\t\t\tIngrese un valor valido (1-31)\n\n");
		system("pause");
		system("cls");
		printf("\n\t\t\tIngrese el nombre (20 caracteres max): %s",aux->nombre);
		printf("\n\n\t\t\tIngrese los apellidos (20 caracteres max): %s",aux->apellidos);
		printf("\n\n\t\t\tIngrese la cedula: %li",aux->cedula);	
		printf("\n\n\t\t\tIngrese el dia (dd) de nacimiento: ");
		cin>>(*aux).fechaNacimiento.dd;
	}
	
	printf("\n\t\t\tIngrese el mes (mm) de nacimiento: ");
	cin>>(*aux).fechaNacimiento.mm;
	
	while((aux->fechaNacimiento.mm>12)||(aux->fechaNacimiento.mm<=0)){ //**********VALIDACION DEL MES DE NACIMIENTO************************
		system("cls");
		printf("\n\n\t\t\t\tIngrese un valor valido (1-12)\n\n");
		system("pause");
		system("cls");
		printf("\n\t\t\tIngrese el nombre (20 caracteres max): %s",aux->nombre);
		printf("\n\n\t\t\tIngrese los apellidos (20 caracteres max): %s",aux->apellidos);
		printf("\n\n\t\t\tIngrese la cedula: %li",aux->cedula);	
		printf("\n\n\t\t\tIngrese el dia (dd) de nacimiento: %i",aux->fechaNacimiento.dd);
		printf("\n\n\t\t\tIngrese el mes (mm) de nacimiento: ");
		cin>>(*aux).fechaNacimiento.mm;
	}
	
	printf("\n\t\t\tIngrese el a%co (yyyy) de nacimiento: ",164);
	scanf("%i",&aux->fechaNacimiento.yy);
	
	freeBuffer();
	printf("\n\t\t\tIngrese la ciudad de nacimiento (40 caracteres max): ");
	gets(aux->place.ciudad);
	
	while(strlen(aux->place.ciudad)>40){                                //**********VALIDACION DE LA CIUDAD**********
		system("cls");
		printf("\n\n\t\t\t\tSolo se permiten max 40 caracteres\n\n");
		system("pause");
		system("cls");
		printf("\n\t\t\tIngrese el nombre (20 caracteres max): %s",aux->nombre);
		printf("\n\n\t\t\tIngrese los apellidos (20 caracteres max): %s",aux->apellidos);
		printf("\n\n\t\t\tIngrese la cedula: %li",aux->cedula);	
		printf("\n\n\t\t\tIngrese el dia (dd) de nacimiento: %i",aux->fechaNacimiento.dd);
		printf("\n\n\t\t\tIngrese el mes (mm) de nacimiento: %i",aux->fechaNacimiento.mm);
		printf("\n\n\t\t\tIngrese el a%co (yyyy) de nacimiento: %i",164,aux->fechaNacimiento.yy);
		printf("\n\n\t\t\tIngrese la ciudad de nacimiento (40 caracteres max): ");
		gets(aux->place.ciudad);
	}
	
	printf("\n\t\t\tIngrese la direccion (40 caracteres max): ");
	gets(aux->place.direccion);
	
	while(strlen(aux->place.direccion)>40){                  //**********VALIDACION DE LA DIRECCION**********
		system("cls");                                   
		printf("\n\n\t\t\t\tSolo se permiten max 40 caracteres\n\n");
		system("pause");
		system("cls");
		printf("\n\t\t\tIngrese el nombre (20 caracteres max): %s",aux->nombre);
		printf("\n\n\t\t\tIngrese los apellidos (20 caracteres max): %s",aux->apellidos);
		printf("\n\n\t\t\tIngrese la cedula: %li",aux->cedula);	
		printf("\n\n\t\t\tIngrese el dia (dd) de nacimiento: %i",aux->fechaNacimiento.dd);
		printf("\n\n\t\t\tIngrese el mes (mm) de nacimiento: %i",aux->fechaNacimiento.mm);
		printf("\n\n\t\t\tIngrese el a%co (yyyy) de nacimiento: %i",164,aux->fechaNacimiento.yy);
		printf("\n\n\t\t\tIngrese la ciudad de nacimiento (40 caracteres max): %s",aux->place.ciudad);
		printf("\n\n\t\t\tIngrese la direccion (40 caracteres max): ");
		gets(aux->place.direccion);
	}
	aux->datosVehiculo = NULL;
	struct vehiculo *auxVehiculo;
	printf("\n\n\t\t\tDesea agregar un vehiculo a este usuario?");
	printf("\n\t\t\tEscriba (1) si desea subir los datos: ");
	scanf("%i",&num);
	if (num==1) {
		auxVehiculo = agregarVehiculo();
		auxVehiculo->vehiculoProx = aux->datosVehiculo;
	}
	while(num==1){
		printf("\n\n\t\t\tDesea agregar otro vehiculo a este usuario?");
		printf("\n\t\t\tEscriba (1) si desea cargar los datos: ");
		scanf("%i",&num);
		if (num==1){
			auxVehiculo = agregarVehiculo();
			auxVehiculo->vehiculoProx = aux->datosVehiculo;
		}
	}
	printf("\n\n\t\t\tDesea guardar todos los datos?");
	printf("\n\t\t\tEscriba (1) si desea cargar los datos: ");
	scanf("%i",&num);
	if (num == 1){
		aux->personaProx= *p;
		*p = aux;
	}
	freeBuffer();
	system("cls");
}

void menuPersonas(){
	
int opcion;
	while(opcion){
		encabezado();
		printf("\t\t\t\t\t MANTENIMIENTO->PERSONAS\n\n");
		printf("\t\t\t\t {POR FAVOR ESCRIBA LA OPCION QUE DESEA}\n\n");
		printf("\t\t\t\t\t(1)--AGREGAR\n");
		printf("\t\t\t\t\t(2)--MODIFICAR\n");
		printf("\t\t\t\t\t(3)--CONSULTAR\n");
		printf("\t\t\t\t\t(4)--BORRAR\n");
		printf("\t\t\t\t\t(0)--ATRAS\n\n\t\t\t\t\t\t\t");
		scanf("%i",&opcion);
		system("cls");
		
		switch (opcion){
			case 1: agregarPersona(&p);//LLAMADA A LA FUNCION agregarPersona
				break;
			case 2: //LLAMADA A LA FUNCION modificarPersona
				break;
			case 3: //LLAMADA A LA FUNCION consultarPersona
				break;
			case 4: //LLAMADA A LA FUNCION borrarPersona

				break;
		}
	}
}

struct persona * devPersona(struct persona *A, int pos){
	if (pos) return devPersona(A->personaProx, --pos);
	else return A;
}

void llamadaAgregarVehiculo(struct persona **p){
	int cedula, posicion;
	struct persona *auxPersona;
	if(!*p){
		printf("\n\n\t\t\tNo existen usuarios ingresados al sistema. Por favor cargue uno\n\n");
		system("pause");
		return;
	}
	printf("\n\tIngrese la cedula del propietario del vehiculo (Ya debe estar registrado en el sistema)");
	printf("\n\n\t\t\t(0) Salir\n\n\t\t\t\t");
	scanf("%i",&cedula);
	posicion=validarCedula(*p,cedula,1); //Devuelve un valor mayor a cero si la cedula esta en el sistema
	while((!posicion)&&(cedula)){
		
		system("cls");
		printf("\n\n\t\t\t\tEsa cedula no se encuentra en el sistema\n\n");
		system("pause");
		system("cls");
		printf("\n\t\tIngrese la cedula del propietario del vehiculo\n\t\t(Ya debe estar registrado en el sistema)");
		printf("\n\n\t\t(0) Salir\n\n\t\t");
		scanf("%i",&cedula);
		
	}if(!cedula) return;
	system("cls");
	//freeBuffer();
	auxPersona = devPersona(*p,posicion);
	
	struct vehiculo *auxVehiculo = agregarVehiculo();
	
	printf("\n\n\t\t\t     Desea guardar estos datos?");
	printf("\n\t\t      Escriba (1) si desea cargar los datos: ");
	scanf("%i",&posicion);
	if (posicion == 1){
		
		auxVehiculo->vehiculoProx = auxPersona->datosVehiculo;
		auxPersona->datosVehiculo = auxVehiculo;
		
	}
}

void menuVehiculos(){
		int opcion=1;
		encabezado();
	while(opcion){

		printf("\t\t\t\t\tMANTENIMIENTO->VEHICULOS\n\n");
		printf("\t\t\t\t {POR FAVOR ESCRIBA LA OPCION QUE DESEA}\n\n");
		printf("\t\t\t\t\t(1)--AGREGAR\n");
		printf("\t\t\t\t\t(2)--MODIFICAR\n");
		printf("\t\t\t\t\t(3)--CONSULTAR\n");
		printf("\t\t\t\t\t(4)--BORRAR\n");
		printf("\t\t\t\t\t(0)--ATRAS\n\n\t\t\t\t\t\t\t");
		scanf("%i",&opcion);
		system("cls");
		
		switch (opcion){
			case 1: llamadaAgregarVehiculo(&p);//LLAMADA A LA FUNCION llamadaAgregarVehiculo()
				break;
			case 2: //LLAMADA A LA FUNCION modificarVehiculo
				break;
			case 3: //LLAMADA A LA FUNCION consultarVehiculo
				break;
			case 4: //LLAMADA A LA FUNCION borrarVehiculo
				break;
		}
	}
}	

void menuMantenimiento(){
	int opcion;
	while(opcion){
		encabezado();
		printf("\t\t\t\t\t      MANTENIMIENTO\n\n");
		printf("\t\t\t\t {POR FAVOR ESCRIBA LA OPCION QUE DESEA}\n\n");
		printf("\t\t\t\t\t(1)--PERSONAS\n");
		printf("\t\t\t\t\t(2)--VEHICULOS\n\n");
		printf("\t\t\t\t\t(0)--ATRAS\n\n\t\t\t\t\t\t\t");
		scanf("%i",&opcion);
		system("cls");
		
		switch (opcion){
			case 1: //LLAMADA A LA FUNCION menuPersonas
				menuPersonas();
				break;
			case 2: //LLAMADA A LA FUNCION menuVehiculos
				menuVehiculos();
				break;
		}
	}
}

void menuOperaMultas(){
	
	int opcion;
	while(opcion){
		encabezado();
		printf("\t\t\t     OPERACIONES Y CONSULTAS->OPERACIONES CON MULTAS\n\n");
		printf("\t\t\t\t {POR FAVOR ESCRIBA LA OPCION QUE DESEA}\n\n");
		printf("\t\t\t\t\t(1)--AGREGAR\n");
		printf("\t\t\t\t\t(2)--PAGAR\n");
		printf("\t\t\t\t\t(3)--CONSULTAR POR NUMERO DE MULTA\n");
		printf("\t\t\t\t\t(4)--MOVER O ELIMINAR\n\n");
		printf("\t\t\t\t\t(0)--ATRAS\n\n\t\t\t\t\t\t\t");
		scanf("%i",&opcion);
		system("cls");
		
		switch (opcion){
			case 1: //LLAMADA A LA FUNCION agregarMulta
				break;
			case 2: //LLAMADA A LA FUNCION pagarMulta
				break;
			case 3: //LLAMADA A LA FUNCION consultarPorMulta
				break;
			case 4: //LLAMADA A LA FUNCION moverEliminarMulta
				break;
		}
	}

}

void menuConsultas(){
	int opcion;
	while(opcion){
		encabezado();
		printf("\t\t\t\t   OPERACIONES Y CONSULTAS->CONSULTAS\n\n");
		printf("\t\t\t\t {POR FAVOR ESCRIBA LA OPCION QUE DESEA}\n\n");
		printf("\t\t\t\t\t(1)--POR EL NOMBRE DE UNA PERSONA\n");
		printf("\t\t\t\t\t(2)--POR CEDULA DE IDENTIDAD\n");
		printf("\t\t\t\t\t(3)--POR PLACA DE VEHICULO\n");
		printf("\t\t\t\t\t(4)--POR NUMERO DE INFRACCION\n\n");
		printf("\t\t\t\t\t(0)--ATRAS\n\n\t\t\t\t\t\t\t");
		scanf("%i",&opcion);
		system("cls");
		
		switch (opcion){
			case 1: //LLAMADA A LA FUNCION consultaPorPersona
				break;
			case 2: //LLAMADA A LA FUNCION consultaPorCedula
				break;
			case 3: //LLAMADA A LA FUNCION consultaPorPlaca
				break;
			case 4: //LLAMADA A LA FUNCION consultaPorInfraccion
				break;
		}
	}
}

void menuOperacionesConsultas(){
	int opcion;
	while(opcion){
		encabezado();
		printf("\t\t\t\t\t  OPERACIONES Y CONSULTAS\n\n");
		printf("\t\t\t\t {POR FAVOR ESCRIBA LA OPCION QUE DESEA}\n\n");
		printf("\t\t\t\t\t(1)--OPERACIONES CON MULTAS\n");
		printf("\t\t\t\t\t(2)--CONSULTAS\n\n");
		printf("\t\t\t\t\t(0)--ATRAS\n\n\t\t\t\t\t\t\t");
		scanf("%i",&opcion);
		system("cls");
		
		switch (opcion){
			case 1: //LLAMADA A LA FUNCION menuOperaMultas
				menuOperaMultas();
				break;
			case 2: //LLAMADA A LA FUNCION menuConsultas
				menuConsultas();
				break;
		}
	}
}

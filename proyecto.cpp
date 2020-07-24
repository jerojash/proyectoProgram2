#include<stdio.h>
#include<stdlib.h>
#include <string.h>

struct fecha{                                        //ESTRUCTURA FECHA
	int yy;                                            //AÑO
	int mm;                                            //MES
	int dd;                                            //DIA
};

struct lugar{                                        //ESTRUCTURA LUGAR
	char ciudad[80];                                   //CIUDAD
	char direccion[80];                                //DIRECCION
};

struct infraccion{                                   //ESTRUCTURA INFRACCION
	int numero;                              //NUMERO DE INFRACCION
	struct fecha fechaInfraccion;                      //FECHA DE INFRACCION
	char tipo[40];                           //TIPO DE INFRACCION
	int monto;                                         //MONTO
	char pagado[2];                                    //PAGADO
	struct infraccion *infraccionProx;                 //APUNTADOR QUE VA A OTRAS INFRACCIONES
};

struct vehiculo{                                     //ESTRUCTURA FECHA
	char placa[20];                                    //PLACA (UNICO)
	char marca[20];                                    //MARCA
	char modelo[20];                                   //MODELO
	struct fecha annio;                                //AÑO DEL VEHICULO
	char color[10];                                    //COLOR DEL VEHICULO
	struct vehiculo *vehiculoProx;                     //APUNTADOR AL PROXIMO VEHICULO
	struct infraccion * datosInfraccion;               //APUNTADOR A LAS INFRACCION DE ESTE VEHICULO
};

struct persona{                                      //ESTRUCTURA PERSONA
	char nombre[40];                                   //NOMBRE
	char apellidos[40];                                //APELLIDOS
	long int cedula;                                   //CEDULA
	struct fecha fechaNacimiento;                      //FECHA DE NACIMIENTO (ESTRUCTURA ANIDADA)
	struct lugar place;                                //LUGAR (ESTRUCTURA ANIDADA)
	struct persona *personaProx;                       //APUNTADOR A LA PROXIMA PERSONA
	struct vehiculo *datosVehiculo;                    //APUNTADOR AL VEHICULO DE ESTA PERSONA
};

void freeBuffer(){                                   //LIBERARA EL BUFFER DE BASURA
	char c;
	while ((c = getchar()) != '\n' && c != EOF);
}

struct persona *p = NULL;                            //VARIABLE GLOBAL, NO SE DECLARA EN MAIN PARA PODER
//													   DECLARARSE EN LAS FUNCIONES. APUNTA A LA PRIMERA PERSONA

void encabezado();                                   //ENCABEZADO PARA MOSTRAR EN LOS MENÚS

int validarCedula(struct persona *n, int x, int cont);//VALIDAR CEDULA, DEVUELVE EN QUE POSICION SE ENCUENTRA LA CEDULA
//                                                    DEVUELVE CERO SI NO SE ENCUENTRA

struct vehiculo * agregarVehiculo();                 //DEVULEVE UN APUNTADOR DE TIPO VEHICULO (NODO)

void agregarPersona(struct persona **p);             //AGREGAR UNA PERSONA AL SISTEMA

void menuPersonas();                                 //MENU DE PERSONAS

struct persona * devPersona(struct persona *A, int pos); //DEVUELVE UN APUNTADOR DE TIPO PERSONA EN UNA POSICION DADA

void llamadaAgregarVehiculo(struct persona **p);      //FUNCION PARA PODER AGREGAR OTRO VEHICULO A UNA CEDULA INGRESADA

void menuVehiculos();                                //MENU VEHICULOS

void menuMantenimiento();                            //MENU MANTENIMIENTO. DOS ENTRADA (PERSONAS Y VEHICULOS)

void menuOperaMultas();                              //MENU OPERACIONES CON MULTAS

void menuConsultas();                                //MENU CONSULTAS

void menuOperacionesConsultas();                     //MENU OPERACIONES Y CONSULTAS

void modificarPersona(struct persona **p);           //MODIFICAR LA INFORMACION DE UNA PERSONA CARGADA AL SISTEMA

void menuConsultarPersona();

void buscarPersonaName(struct persona *p, char name[20]);

void consultarPersonaNombre(struct persona *p);

void buscarPersonaID(struct persona *p, int id);

void consultarPersonaCedula(struct persona *p);

struct infraccion * agregarInfraccion();

int validarPlaca(struct persona *q, char placa[8]);

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
			case 1: menuMantenimiento();             //LLAMADA A LA FUNCION menuMantenimiento
				break;
			case 2: menuOperacionesConsultas();      //LLAMADA A LA FUNCION menuOperaciones
				break;
		}
	}
	return 0;
}


void encabezado(){                                   //ENCABEZADO PARA MOSTRAR EN LOS MENÚS
		printf("\t\t\t\t\tMENU DE CONTROL DE MULTAS\n");
		printf("\t\t\t\tALCALDIA DEL MUNICIPIO DE CHACAO, CARACAS\n\n");
}

int validarCedula(struct persona *n, int x, int cont){//VALIDAR CEDULA, DEVUELVE EN QUE POSICION SE ENCUENTRA LA CEDULA. 0 SI NO
	if (n){
			if (n->cedula == x) return cont;//Se encontro una cedula igual, es verdadero
			else return validarCedula(n->personaProx, x, ++cont); 
	}else return 0; //Es decir que no se encontró ninguna cedula igual, es falso
}

struct infraccion * agregarInfraccion(){
	int num;
	//freeBuffer();
	struct infraccion *auxInfraccion = new struct infraccion;  //RESERVO MEMORIA DEL TIPO DE ESTRUCTURA DEL VEHICULO

	printf("\n\t\t\tIngrese el numero de infraccion: "); 
	scanf("%i",&auxInfraccion->numero);
	printf("\n\t\t\t%i",auxInfraccion->numero);
	freeBuffer();
	printf("\n\t\t\tIngrese el tipo de infraccion: "); 
	gets(auxInfraccion->tipo);
	printf("\n\t\t\t%i",auxInfraccion->numero);
	printf("\n\t\t%s",auxInfraccion->tipo);
	//freeBuffer();
	printf("\n\t\t\tIngrese el monto de la infraccion: "); 
	scanf("%i",&auxInfraccion->monto);
	printf("\n\t\t\t%i",auxInfraccion->numero);
	printf("\n\t\t\t%s",auxInfraccion->tipo);
	printf("\n\t\t\t%i",auxInfraccion->monto);

	printf("\n\t\t\tIngrese el dia en que se registro la infraccion: "); 
	scanf("%i",&auxInfraccion->fechaInfraccion.dd);
	printf("\n\t\t\t%i",auxInfraccion->numero);
	printf("\n\t\t\t%s",auxInfraccion->tipo);
	printf("\n\t\t\t%i",auxInfraccion->monto);
	printf("\n\t\t\t%i",auxInfraccion->fechaInfraccion.dd);
	printf("\n\t\t\tIngrese el mes en que se registro la infraccion: "); 
	scanf("%i",&auxInfraccion->fechaInfraccion.mm);
	printf("\n\t\t\t%i",auxInfraccion->numero);
	printf("\n\t\t\t%s",auxInfraccion->tipo);
	printf("\n\t\t\t%i",auxInfraccion->monto);
	printf("\n\t\t\t%i",auxInfraccion->fechaInfraccion.dd);
	printf("\n\t\t\t%i",auxInfraccion->fechaInfraccion.mm);
	printf("\n\t\t\tIngrese el a�o en que se registro la infraccion: "); 
	scanf("%i",&auxInfraccion->fechaInfraccion.yy);
	printf("\n\t\t\t%i",auxInfraccion->numero);
	printf("\n\t\t\t%s",auxInfraccion->tipo);
	printf("\n\t\t\t%i",auxInfraccion->monto);
	printf("\n\t\t\t%i",auxInfraccion->fechaInfraccion.dd);
	printf("\n\t\t\t%i",auxInfraccion->fechaInfraccion.mm);
	printf("\n\t\t\t%i",auxInfraccion->fechaInfraccion.yy);
	freeBuffer();
	printf("\n\t\t\tIngrese si la multa ha sido pagada (SI/NO): "); 
	gets(auxInfraccion->pagado);
	printf("\n\t\t\t%i",auxInfraccion->numero);
	printf("\n\t\t\t%s",auxInfraccion->tipo);
	printf("\n\t\t\t%i",auxInfraccion->monto);
	printf("\n\t\t\t%i",auxInfraccion->fechaInfraccion.dd);
	printf("\n\t\t\t%i",auxInfraccion->fechaInfraccion.mm);
	printf("\n\t\t\t%i",auxInfraccion->fechaInfraccion.yy);	
	printf("\n\t\t\t%s",auxInfraccion->pagado);
	
	
	auxInfraccion->infraccionProx = NULL;
	return auxInfraccion;
}

struct vehiculo * agregarVehiculo(){
	int num;
	freeBuffer();
	struct vehiculo *auxVehiculo = new struct vehiculo;  //RESERVO MEMORIA DEL TIPO DE ESTRUCTURA DEL VEHICULO
	printf("\n\t\t\tIngrese la placa (8 caracteres max): "); 
	gets(auxVehiculo->placa);
	strcpy(auxVehiculo->placa,strupr(auxVehiculo->placa));  //CONVIERTO LA PLACA EN PURAS MAYUSCULAS
	while(strlen(auxVehiculo->placa)>8){                                     //**********VALIDACION DE LA LONGITUD DE LA PLACA*****
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
	freeBuffer();
	printf("\n\t\t\tIngrese el color del vehiculo: "); 
	gets(auxVehiculo->color);
	
	auxVehiculo->datosInfraccion = NULL;
	struct infraccion *auxInfraccion;
	printf("\n\n\t\t\tDesea registrar una infraccion a este vehiculo?");
	printf("\n\t\t\tEscriba (1) si desea cargar los datos: ");
	scanf("%i",&num);
	if (num==1) {
		auxInfraccion = agregarInfraccion();
		auxInfraccion->infraccionProx = auxVehiculo->datosInfraccion;
		auxVehiculo->datosInfraccion = auxInfraccion;
	}
	while(num==1){
		printf("\n\n\t\t\tDesea registrar otra infraccion a este vehiculo? ");
		printf("\n\t\t\tEscriba (1) si desea cargar los datos: ");
		scanf("%i",&num);
		if (num==1) {
			auxInfraccion = agregarInfraccion();
			auxInfraccion->infraccionProx = auxVehiculo->datosInfraccion;
			auxVehiculo->datosInfraccion = auxInfraccion;
		}
	}
	
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
	strcpy(aux->nombre,strupr(aux->nombre));
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
	strcpy(aux->apellidos,strupr(aux->apellidos));
	
	printf("\n\t\t\tIngrese la cedula: ");
	scanf("%li",&aux->cedula);
	
	while((validarCedula((*p), aux->cedula, 1)!=0)||(aux->cedula<=0)){      //*****************VALIDACION DE CEDULA***********************
		system("cls");
		printf("\n\n\t\t\tEsa cedula ya esta registrada en el sistema o es una cedula invalida.\n\n");
		system("pause");
		system("cls");
		printf("\n\t\t\tIngrese el nombre (20 caracteres max): %s",aux->nombre);
		printf("\n\n\t\t\tIngrese los apellidos (20 caracteres max): %s",aux->apellidos);
		printf("\n\n\t\t\tIngrese la cedula: ");
		scanf("%li",&aux->cedula);
	}
	
	printf("\n\t\t\tIngrese el dia de nacimiento: ");
	scanf("%i",&(*aux).fechaNacimiento.dd);
	
	while(aux->fechaNacimiento.dd>31||(aux->fechaNacimiento.dd<=0)){ //**********VALIDACION DE DIA DE NACIMIENTO************************
		system("cls");
		printf("\n\n\t\t\t\tIngrese un valor valido (1-31)\n\n");
		system("pause");
		system("cls");
		printf("\n\t\t\tIngrese el nombre (20 caracteres max): %s",aux->nombre);
		printf("\n\n\t\t\tIngrese los apellidos (20 caracteres max): %s",aux->apellidos);
		printf("\n\n\t\t\tIngrese la cedula: %li",aux->cedula);	
		printf("\n\n\t\t\tIngrese el dia (dd) de nacimiento: ");
		scanf("%i",&(*aux).fechaNacimiento.dd);
	}
	
	printf("\n\t\t\tIngrese el mes de nacimiento: ");
	scanf("%i",&(*aux).fechaNacimiento.mm);
	
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
		scanf("%i",&(*aux).fechaNacimiento.mm);
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
	
	printf("\n\t\t\tIngrese la direccion de vivienda (40 caracteres max): ");
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
	printf("\n\t\t\tEscriba (1) si desea cargar los datos: ");
	scanf("%i",&num);
	if (num==1) {
		auxVehiculo = agregarVehiculo();
		auxVehiculo->vehiculoProx = aux->datosVehiculo;
		aux->datosVehiculo = auxVehiculo;
	}
	while(num==1){
		printf("\n\n\t\t\tDesea agregar otro vehiculo a este usuario?");
		printf("\n\t\t\tEscriba (1) si desea cargar los datos: ");
		scanf("%i",&num);
		if (num==1){
			auxVehiculo = agregarVehiculo();
			auxVehiculo->vehiculoProx = aux->datosVehiculo;
			aux->datosVehiculo = auxVehiculo;
		}
	}
	printf("\n\n\t\t\tDesea guardar todos los datos?");
	printf("\n\t\t\tEscriba (1) si desea cargar los datos: ");
	freeBuffer();
	scanf("%i",&num);
	if (num == 1){
		aux->personaProx= *p;
		*p = aux;
	}
	freeBuffer();
	system("cls");
}

void menuPersonas(){
	
	int opcion = 1;
	while(opcion){
		system("cls");
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
			case 2: modificarPersona(&p);//LLAMADA A LA FUNCION modificarPersona
				break;
			case 3: menuConsultarPersona();//LLAMADA A LA FUNCION menuConsultarPersona
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
	struct vehiculo *auxVehiculo;
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
	auxPersona = devPersona(*p,--posicion);
	
	auxVehiculo = agregarVehiculo();
	
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
	while(opcion){
		system("cls");
		encabezado();
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
	system("cls");
	int opcion=1;
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
	system("cls");
	int opcion = 1;
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
	system("cls");
	int opcion = 1;
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
	system("cls");
	int opcion= 1;
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

void modificarPersona(struct persona **p){
	system("cls");
	int cedula,posicion, respuesta=0;
	struct persona *aux;
	
	if(!*p){ //VALIDO PARA SABER SI LA BASE DE DATOS ESTA VACIA
		printf("\n\t\t\tLa base de datos esta vacia. Ingrese una persona al sistema para continuar\n");
		system("pause");
		return;
	}
	
	while(respuesta!=1){
		system("cls");
		printf("\n\t\t\tIngrese una cedula para buscar en el sistema.");
		printf("\n\t\t\t(0) Para salir\n\t\t\t");
		scanf("%i",&cedula);
		if (!cedula) return;
		posicion=validarCedula(*p, cedula, 1);
		
		while(!posicion){
			system("cls");
			printf("\n\t\t\tLa cedula no se encuentra en el sistema, intente de nuevo: \n");
			system("pause");
			system("cls");
			printf("\n\t\t\tIngrese una cedula para buscar en el sistema.");
			printf("\n\t\t\t(0) Para salir\n\t\t");
			scanf("%i",&cedula);
			if (!cedula) return;                         
			posicion = validarCedula(*p,cedula,1);    //BUG
		
		}
		aux = devPersona(*p, --posicion);		
		printf("\n\n\t\t\tDesea modificar los datos de esta persona?\n\t\t\tIngrese 1 si desea hacerlo");
		printf("\n\n\t\t\tNombre: %s   Apellido: %s",aux->nombre,aux->apellidos);
		printf("\n\t\t\tCedula: %i\n\n\t\t\t\t\t\t",cedula);
		scanf("%i",&respuesta);
	}
	freeBuffer();
	
	printf("\n\t\t\tIngrese el nombre (20 caracteres max): "); 
	gets(aux->nombre);
	
	while(strlen(aux->nombre)>20){                                     //******************VALIDACION DEL NOMBRE********************
		printf("\n\n\t\t\t\tSolo se permiten max 20 caracteres\n\n");
		system("pause");
		system("cls");
		printf("\n\t\t\tIngrese el nombre (20 caracteres max): "); 
		gets(aux->nombre);
	}
	strcpy(aux->nombre,strupr(aux->nombre));
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
	strcpy(aux->apellidos,strupr(aux->apellidos));
	printf("\n\n\t\t\tCedula: %i (NO SE PUEDE MODIFICAR)",aux->cedula);
	
	printf("\n\n\t\t\tIngrese el dia (dd) de nacimiento: ");
	scanf("%i",&(*aux).fechaNacimiento.dd);
	
	while(aux->fechaNacimiento.dd>31||(aux->fechaNacimiento.dd<=0)){ //**********VALIDACION DE DIA DE NACIMIENTO************************
		system("cls");
		printf("\n\n\t\t\t\tIngrese un valor valido (1-31)\n\n");
		system("pause");
		system("cls");
		printf("\n\t\t\tIngrese el nombre (20 caracteres max): %s",aux->nombre);
		printf("\n\n\t\t\tIngrese los apellidos (20 caracteres max): %s",aux->apellidos);
		printf("\n\n\t\t\tCedula: %i (NO SE PUEDE MODIFICAR)",aux->cedula);	
		printf("\n\n\t\t\tIngrese el dia (dd) de nacimiento: ");
		scanf("%i",&(*aux).fechaNacimiento.dd);
	}
	
	printf("\n\t\t\tIngrese el mes (mm) de nacimiento: ");
	scanf("%i",&(*aux).fechaNacimiento.mm);
	
	while((aux->fechaNacimiento.mm>12)||(aux->fechaNacimiento.mm<=0)){ //**********VALIDACION DEL MES DE NACIMIENTO************************
		system("cls");
		printf("\n\n\t\t\t\tIngrese un valor valido (1-12)\n\n");
		system("pause");
		system("cls");
		printf("\n\t\t\tIngrese el nombre (20 caracteres max): %s",aux->nombre);
		printf("\n\n\t\t\tIngrese los apellidos (20 caracteres max): %s",aux->apellidos);
		printf("\n\n\t\t\tCedula: %i (NO SE PUEDE MODIFICAR)",aux->cedula);	
		printf("\n\n\t\t\tIngrese el dia (dd) de nacimiento: %i",aux->fechaNacimiento.dd);
		printf("\n\n\t\t\tIngrese el mes (mm) de nacimiento: ");
		scanf("%i",&(*aux).fechaNacimiento.mm);
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
		printf("\n\n\t\t\tCedula: %i (NO SE PUEDE MODIFICAR)",aux->cedula);	
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
		printf("\n\n\t\t\tCedula: %i (NO SE PUEDE MODIFICAR)",aux->cedula);	
		printf("\n\n\t\t\tIngrese el dia (dd) de nacimiento: %i",aux->fechaNacimiento.dd);
		printf("\n\n\t\t\tIngrese el mes (mm) de nacimiento: %i",aux->fechaNacimiento.mm);
		printf("\n\n\t\t\tIngrese el a%co (yyyy) de nacimiento: %i",164,aux->fechaNacimiento.yy);
		printf("\n\n\t\t\tIngrese la ciudad de nacimiento (40 caracteres max): %s",aux->place.ciudad);
		printf("\n\n\t\t\tIngrese la direccion (40 caracteres max): ");
		gets(aux->place.direccion);
	}
	
	printf("\n\n\t\t\t\tDATOS GUARDADOS CON EXITO\n");
	system("pause");
	freeBuffer();
	system("cls");
}

void menuConsultarPersona(){
	int opcion = 1;
	while(opcion){
		system("cls");
		encabezado();
		printf("\t\t\t\t   MANTENIMIENTO->PERSONAS->CONSULTAR\n\n");
		printf("\t\t\t\t {POR FAVOR ESCRIBA LA OPCION QUE DESEA}\n\n");
		printf("\t\t\t\t\t(1)--CONSULTAR POR NOMBRE\n");
		printf("\t\t\t\t\t(2)--CONSULTAR POR CEDULA\n");
		printf("\t\t\t\t\t(0)--ATRAS\n\n\t\t\t\t\t\t\t");
		scanf("%i",&opcion);
		system("cls");
		
		switch (opcion){
			case 1: consultarPersonaNombre(p);//LLAMADA A LA FUNCION agregarPersona
				break;
			case 2: consultarPersonaCedula(p);//consultarPersonaCedula(p);//LLAMADA A LA FUNCION modificarPersona
				break;
		}
	}
}

void buscarPersonaName(struct persona *p, char name[20]){
	if (p){
		if(!strcmp(name, p->nombre)){
			printf("\n\n\t\t\tNombre: %s",p->nombre);
			printf("\n\n\t\t\tApellidos: %s",p->apellidos);
			printf("\n\n\t\t\tCedula: %i",p->cedula);
			printf("\n\n\t\t\tFecha de nacimiento: %i/%i/%i",p->fechaNacimiento.dd,p->fechaNacimiento.mm,p->fechaNacimiento.yy);
			printf("\n\n\t\t\tLugar de nacimiento: %s",p->place.ciudad);
			printf("\n\n\t\t\tDireccion actual de residencia: %s\n\n",p->place.direccion);
			system("pause");
		}
		buscarPersonaName(p->personaProx, name);
	}
}

void consultarPersonaNombre(struct persona *p){
	system("cls");
	char nombre[20];
	freeBuffer();
	if(!p){
		printf("\n\n\t\tLa base de datos esta vacia. Agregue una persona al sistema primero\n");
		system("pause");
		return;
	}
	printf("\n\n\t\t\tIngrese el nombre que desea buscar");
	printf("\n\t\t\tDebe ser el mismo que se ingreso en el sistema (No importan las mayusculas)\n\n\t\t\t\t\t");
	gets(nombre);
	strcpy(nombre,strupr(nombre));
	printf("\n%s\n",nombre);
	printf("\n\n\t\t\t\tSE ENCONTRARON LOS SIGUIENTES DATOS\n\n");
	buscarPersonaName(p, nombre);
	printf("\n\n\t\t\t\t    NO SE ENCONTRARON MAS DATOS\n\n");
	system("pause");
	system("cls");
}

void buscarPersonaID(struct persona *p, int id){
	if (p){
		if(p->cedula == id){
			printf("\n\n\t\t\tNombre: %s",p->nombre);
			printf("\n\n\t\t\tApellidos: %s",p->apellidos);
			printf("\n\n\t\t\tCedula: %i",p->cedula);
			printf("\n\n\t\t\tFecha de nacimiento: %i/%i/%i",p->fechaNacimiento.dd,p->fechaNacimiento.mm,p->fechaNacimiento.yy);
			printf("\n\n\t\t\tLugar de nacimiento: %s",p->place.ciudad);
			printf("\n\n\t\t\tDireccion actual de residencia: %s\n\n",p->place.direccion);
		}
		else buscarPersonaID(p->personaProx, id);
	} else printf("\n\n\t\t\t\tNO SE ENCONTRO ESA CEDULA EN EL SISTEMA\n\n");
}

void consultarPersonaCedula(struct persona *p){
	system("cls");
	int cedula = 0;
	freeBuffer();
	if(!p){
		printf("\n\n\t\tLa base de datos esta vacia. Agregue una persona al sistema primero\n");
		system("pause");
		return;
	}
	printf("\n\n\t\t\tIngrese la cedula que desea buscar\n\n\t\t\t\t\t");
	scanf("%i",&cedula);
	buscarPersonaID(p, cedula);
	system("pause");
	system("cls");
}

struct vehiculo *validarPlaca(struct persona *q, char placa[8], int cont){ //Retorna NULL si no consigue la placa.			   											   //sino, retorna el apuntador de esa placa
	while(q){
		struct vehiculo *vehiculo = q->datosVehiculo;
		while(vehiculo){
			if (!strcmp(vehiculo->placa, placa)) return vehiculo;
			vehiculo = vehiculo->vehiculoProx;
		}
		q = q->personaProx;
	} return NULL;
}

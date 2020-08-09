 /*Integrantes: Jose Alayon C.I 26.546.441
            	Ashly Colmenares C.I 28.052.693
	    		Javier Rojas C.I 28.472.023
	       		Alejandro Sangiacomo C.I 26.763.470 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct fecha{                                        //ESTRUCTURA FECHA
	int yy;                                            //AÃ‘O
	int mm;                                            //MES
	int dd;                                            //DIA
};

struct lugar{                                        //ESTRUCTURA LUGAR
	char ciudad[80];                                   //CIUDAD
	char direccion[80];                                //DIRECCION
};

struct infraccion{                                   //ESTRUCTURA INFRACCION
	int numero;                                        //NUMERO DE INFRACCION
	struct fecha fechaInfraccion;                      //FECHA DE INFRACCION
	char tipo[40];                                     //TIPO DE INFRACCION
	int monto;                                         //MONTO
	char pagado[2];                                    //PAGADO
	struct infraccion *infraccionProx;                 //APUNTADOR QUE VA A OTRAS INFRACCIONES
};

struct vehiculo{                                     //ESTRUCTURA FECHA
	char placa[20];                                    //PLACA (UNICO)
	char marca[20];                                    //MARCA
	char modelo[20];                                   //MODELO
	struct fecha annio;                                //AÃ‘O DEL VEHICULO
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

void guardarData(struct persona *p){
	FILE* fichero;
	char linea[20];
	struct vehiculo *v;
	struct infraccion *f;
	fichero = fopen("dataproyecto.txt", "w"); 
	while(p){
		fputs("PERSONA\n",fichero);
		fputs(p->nombre,fichero);
		fputs("\n",fichero);
		fputs(p->apellidos,fichero);
		fputs("\n",fichero);
		fprintf(fichero, "%li\n",p->cedula);
		fprintf(fichero, "%i\n",p->fechaNacimiento.dd);
		fprintf(fichero, "%i\n",p->fechaNacimiento.mm);
		fprintf(fichero, "%i\n",p->fechaNacimiento.yy);
		fputs(p->place.ciudad,fichero);
		fputs("\n",fichero);
		fputs(p->place.direccion,fichero);
		fputs("\n",fichero);
		v = p->datosVehiculo;
		while(v){
			fputs("VEHICULO\n",fichero);
			fputs(v->placa,fichero);
			fputs("\n",fichero);
			fputs(v->marca,fichero);
			fputs("\n",fichero);
			fputs(v->modelo,fichero);
			fputs("\n",fichero);
			fprintf(fichero, "%i\n",v->annio.yy);
			fputs(v->color,fichero);
			fputs("\n",fichero);
			f = v->datosInfraccion;
			while(f){
				fputs("MULTAS\n",fichero);
				fprintf(fichero, "%i\n",f->numero);
				fputs(f->tipo,fichero);
				fputs("\n",fichero);
				fprintf(fichero, "%i\n",f->monto);
				//fputs("\n",fichero);
				fprintf(fichero, "%i\n",f->fechaInfraccion.dd);
				//fputs("\n",fichero);
				fprintf(fichero, "%i\n",f->fechaInfraccion.mm);
				//fputs("\n",fichero);
				fprintf(fichero, "%i\n",f->fechaInfraccion.yy);
				//fputs("\n",fichero);
				fputs(f->pagado,fichero);
				fputs("\n",fichero);
				f = f->infraccionProx;
			} 
			v = v->vehiculoProx;
		} 
	p=p->personaProx;
	};
 	fclose(fichero);
}

void freeBuffer(){                                   //LIBERARA EL BUFFER DE BASURA
	char c;
	while ((c = getchar()) != '\n' && c != EOF);
}

void llenarData(struct persona **p){
	struct persona *persona;
	struct vehiculo *vehiculo;
	struct infraccion *infraccion;
	FILE* fichero;
	char linea[20];
	char lineaaux[20];
	fichero = fopen("dataproyecto.txt", "r"); 
	
	if (fichero == NULL){
	 	printf("No existe el fichero!\n");
	 	system("pause");
	 	return;
	 }
	 
	while(!feof(fichero)){
		fgets(linea,20,fichero);
		if(feof(fichero))break;
		if (!strcmp(linea,"PERSONA\n")){
			persona = new struct persona;
			
			fgets(linea,20,fichero);
			  strncpy(persona->nombre,linea,strlen(linea)-1);
			  persona->nombre[strlen(linea)-1] = '\0';
			  
			fgets(linea,20,fichero);
			  strncpy(persona->apellidos,linea,strlen(linea)-1);
			  persona->apellidos[strlen(linea)-1] = '\0';
			  
			fgets(linea,20,fichero);
			  persona->cedula = atoi(linea);
			  
			fgets(linea,20,fichero);
			  persona->fechaNacimiento.dd = atoi(linea);
			  
			fgets(linea,20,fichero);
			  persona->fechaNacimiento.mm = atoi(linea);
			  
			fgets(linea,20,fichero);
			  persona->fechaNacimiento.yy = atoi(linea);
			  
			fgets(linea,20,fichero);
			  strncpy(persona->place.ciudad,linea,strlen(linea)-1);
			  persona->place.ciudad[strlen(linea)-1] = '\0';
			  
			fgets(linea,20,fichero);
			  strncpy(persona->place.direccion,linea,strlen(linea)-1);
			  persona->place.direccion[strlen(linea)-1] = '\0';
			  
			persona->datosVehiculo = NULL;
			
			persona->personaProx = *p;
			*p = persona;
			
		} else if (!strcmp(linea,"VEHICULO\n")){
			vehiculo = new struct vehiculo;
			
			fgets(linea,20,fichero);
			  strncpy(vehiculo->placa,linea,strlen(linea)-1);
			  vehiculo->placa[strlen(linea)-1] = '\0';
			  
			fgets(linea,20,fichero);
			  strncpy(vehiculo->marca,linea,strlen(linea)-1);
			  vehiculo->marca[strlen(linea)-1] = '\0';
			  
			fgets(linea,20,fichero);
			  strncpy(vehiculo->modelo,linea,strlen(linea)-1);
			  vehiculo->modelo[strlen(linea)-1] = '\0';
			  
			fgets(linea,20,fichero);
			  vehiculo->annio.yy=atoi(linea);
			  
			fgets(linea,20,fichero);
			  strncpy(vehiculo->color,linea,strlen(linea)-1);
			  vehiculo->color[strlen(linea)-1] = '\0';
			  
			vehiculo->datosInfraccion = NULL;
			
			vehiculo->vehiculoProx = (*p)->datosVehiculo;
			(*p)->datosVehiculo = vehiculo;
			
		}else if (!strcmp(linea,"MULTAS\n")){
			infraccion = new struct infraccion;
			
			fgets(linea,20,fichero);
			  infraccion->numero=atoi(linea);
			  
			fgets(linea,20,fichero);
			  strncpy(infraccion->tipo,linea,strlen(linea)-1);
			  infraccion->tipo[strlen(linea)-1] = '\0';
			  
			fgets(linea,20,fichero);
			infraccion->monto=atoi(linea);
			
			fgets(linea,20,fichero);
			infraccion->fechaInfraccion.dd=atoi(linea);
			
			fgets(linea,20,fichero);
			infraccion->fechaInfraccion.mm=atoi(linea);
			
			fgets(linea,20,fichero);
			infraccion->fechaInfraccion.yy=atoi(linea);
			
			fgets(linea,20,fichero);
			  strncpy(infraccion->pagado,linea,strlen(linea)-1);
			  infraccion->pagado[strlen(linea)-1] = '\0';
			  
			infraccion->infraccionProx = (*p)->datosVehiculo->datosInfraccion;
			(*p)->datosVehiculo->datosInfraccion = infraccion;
		}
	}
	fclose(fichero);
}

struct persona *p = NULL;                            //VARIABLE GLOBAL, NO SE DECLARA EN MAIN PARA PODER
//													   DECLARARSE EN LAS FUNCIONES. APUNTA A LA PRIMERA PERSONA

void encabezado();                                   //ENCABEZADO PARA MOSTRAR EN LOS MENÃšS

void validarDia(struct persona **t);                   //VALIDA EL DIA DE NACIMIENTO

void validarMes(struct persona **t);                  //VALIDA EL MES DE NACIMIENTO

void validarDia(struct persona **t);                   //VALIDA EL DIA DE NACIMIENTO

void validarMes(struct persona **t);                  //VALIDA EL MES DE NACIMIENTO

void validarAnnio(struct persona **t);                //VALIDA EL AÃ‘O DE NACIMIENTO

struct vehiculo * agregarVehiculo();                 //DEVULEVE UN APUNTADOR DE TIPO VEHICULO (NODO)

void validarAnnioV(struct vehiculo **x);             //VALIDA EL AÃ‘O DEL MODELO VEHICULO

void agregarPersona(struct persona **p);             //AGREGAR UNA PERSONA AL SISTEMA

void menuPersonas();                                 //MENU DE PERSONAS

struct persona * devPersona(struct persona *A, int pos); //DEVUELVE UN APUNTADOR DE TIPO PERSONA EN UNA POSICION DADA

void llamadaAgregarVehiculo(struct persona **p);      //FUNCION PARA PODER AGREGAR OTRO VEHICULO A UNA CEDULA INGRESADA

void menuVehiculos();                                //MENU VEHICULOS

void menuMantenimiento();                            //MENU MANTENIMIENTO. DOS ENTRADA (PERSONAS Y VEHICULOS)

void menuOperaMultas();                              //MENU OPERACIONES CON MULTAS

void menuConsultasdos();                             //MENU CONSULTAS 2.2

void menuConsultascuatro();                          //MENU CONSULTAS 2.4

void menuConsultas();                                //MENU CONSULTAS

void menuOperacionesConsultas();                     //MENU OPERACIONES Y CONSULTAS

void modificarPersona(struct persona **p);           //MODIFICAR LA INFORMACION DE UNA PERSONA CARGADA AL SISTEMA

void menuConsultarPersona();                         //MENU CONSULTA-PERSONA

void consultarPersonaNombre(struct persona *p);      //CONSULTAR PERSONA POR NOMBRE

struct persona * buscarCedula(struct persona *r, int cedula);    //BUSCA LA CEDULA DE LA PERSONA EN EL SISTEMA

struct vehiculo *buscarPlaca(struct persona *q, char placa[8]);  //BUSCA LA PLACA DE UN VEHICULO EN EL SISTEMA

void consultarPersonaCedula(int cedula);             //CONSULTAR PERSONA POR LA CEDULA

void consultarVehiculoPlaca(struct persona *r);      //CONSULTAR VEHICULO POR PLACA

void menuConsultarVehiculo();                         //MENU CONSULTAS-VEHICULO

void buscarPersonaNombre(struct persona *p, char name[20]);

void consultarVehiculoCedula(struct persona *r);

void llamadaEliminarPersona();

void eliminarPersona(struct persona **p, int cedula);                                          //ELIMINA A UNA PERSONA DEL SISTEMA

void eliminarVehiculo(struct persona **p, struct vehiculo **v, char placa[8]);                 //ELIMINA UN VEHICULO DEL SISTEMA

void eliminarInfraccion(struct vehiculo **v, struct infraccion **f, int numeroInfraccion);     //ELIMINA UNA INFRACCION DEL SISTEMA

struct persona *buscarTitularVehiculo(struct persona *q, char placa[8]);                       //BUSCA EL TITULAR DE UN VEHICULO

void modificarVehiculo(struct persona **p);                                                    //MODIFICA UN VEHICULO EN EL SISTEMA

void llamadaEliminarVehiculo();                                                                

struct infraccion * buscarInfraccion(int numero);

struct persona * buscarInfraccionPersona(int numero);

struct vehiculo * buscarInfraccionVehiculo(int numero);

void consultarInfraccion(struct persona *f);

void llamadaAgregarInfraccion(struct persona **p);

void pagarInfraccion();             //PAGA UNA INFRACCION

void moverInfraccion();             //MUEVE LA INFRACCION

void llamadaEliminarInfraccion();

void funcionDosDosUno (struct persona *p);           //FUNCION DE LA OPCION 2.2.1

void funcionDosDosDos(struct persona *p);            //FUNCION DE LA OPCION 2.2.2

void funcionDosDosTres(struct persona *p);   //FUNCION DE LA OPCION 2.2.3

void funcionDosDosCuatro(struct persona *p); //FUNCION DE LA OPCION 2.2.4

void funcionDosDosCinco(struct persona *p);  //FUNCION DE LA OPCION 2.2.5

void funcionDosTres(struct persona *p);              //FUNCION DE LA OPCION 2.3

void funcionesDosCuatro(struct persona *q, int num); //FUNCION DE LA OPCION 2.4

void mostrarPersona(struct persona *persona);

void mostrarVehiculos(struct vehiculo *vehiculos);

void mostrarInfracciones(struct infraccion *datosInfraccion);

void swapStr( char A[],char B[]);  //INTERCAMBIA CARACTERES

void swapInt(int *A, int *B);      //INTERCAMBIA ENTEROS

void swapApun(struct infraccion **A, struct infraccion **B); //INTERCAMBIA APUNTADORES

void ordenarBurbujaPlaca(struct vehiculo **v);   //ORDENA POR EL METODO BURBUJA LOS VEHICULOS POR SUS PLACAS

void ordenarBurbujaNumeroMulta(struct infraccion **f);    //ORDENA POR EL METODO BURBUJA LAS MULTAS POR SU NUMERO

void ordenarPersonaCedula(struct persona **p, int btn);   //ORDENA POR EL METODO BURBUJA LAS PERSONAS POR SU CEDULA

void ordenarBurbujaIFecha(struct infraccion **i);          //ORDENA POR EL METODO BURBUJA LAS INFRACCIONES POR SU FECHA

int main(){         //*************************FUNCION PRINCIPAL***************************
	llenarData(&p);
	int opcion = 1;	
	while(opcion){ //   **************************MENU PRINCIPAL*************************
		system("cls");
		encabezado();
		printf("\t\t\t\t {POR FAVOR ESCRIBA LA OPCION QUE DESEA}\n\n");
		printf("\t\t\t\t\t(1)--MANTENIMIENTO\n");
		printf("\t\t\t\t\t(2)--OPERACIONES Y CONSULTAS\n");
		printf("\t\t\t\t\t(0)--SALIR\n\n\t\t\t\t\t\t\t");
		printf("\n\t\t\t\t\t\tOpcion: "); 
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

void encabezado(){                                   //ENCABEZADO PARA MOSTRAR EN LOS MENUS
		printf("\t\t\t\t-------------------------------------------\n");
		printf("\t\t\t\t\t MENU DE CONTROL DE MULTAS\n");
		printf("\t\t\t\t ALCALDIA DEL MUNICIPIO DE CHACAO, CARACAS\n");
		printf("\t\t\t\t-------------------------------------------\n\n");
}

///////////////////////////////////////////////////////////FUNCIONES MENUS///////////////////////////////////////////////////////////////

void menuPersonas(){            //MENU MANTENIMIENTO-PERSONAS
	
	int opcion = 1;
	while(opcion){
		system("cls");
		encabezado();
		printf("\t\t\t\t\t-------------------------\n");
		printf("\t\t\t\t\t MANTENIMIENTO->PERSONAS\n");
		printf("\t\t\t\t\t-------------------------\n\n");
		printf("\t\t\t\t {POR FAVOR ESCRIBA LA OPCION QUE DESEA}\n\n");
		printf("\t\t\t\t\t(1)--AGREGAR\n");
		printf("\t\t\t\t\t(2)--MODIFICAR\n");
		printf("\t\t\t\t\t(3)--CONSULTAR\n");
		printf("\t\t\t\t\t(4)--BORRAR\n");
		printf("\t\t\t\t\t(0)--ATRAS\n\n\t\t\t\t\t\t\t");
		printf("\n\t\t\t\t\t\tOpcion: "); 
		scanf("%i",&opcion);
		system("cls");
		
		switch (opcion){
			case 1: agregarPersona(&p);//LLAMADA A LA FUNCION agregarPersona
				break;
			case 2: modificarPersona(&p);//LLAMADA A LA FUNCION modificarPersona
				break;
			case 3: menuConsultarPersona();//LLAMADA A LA FUNCION menuConsultarPersona
				break;
			case 4: llamadaEliminarPersona();//LLAMADA A LA FUNCION llamadaEliminarPersona

				break;
		}
	}
}

void menuVehiculos(){        //MENU MANTENIMIENTO-VEHICULOS
	int opcion=1;
	while(opcion){
		system("cls");
		encabezado();
		printf("\t\t\t\t\t--------------------------\n");
		printf("\t\t\t\t\t MANTENIMIENTO->VEHICULOS\n");
		printf("\t\t\t\t\t--------------------------\n\n");
		printf("\t\t\t\t {POR FAVOR ESCRIBA LA OPCION QUE DESEA}\n\n");
		printf("\t\t\t\t\t(1)--AGREGAR\n");
		printf("\t\t\t\t\t(2)--MODIFICAR\n");
		printf("\t\t\t\t\t(3)--CONSULTAR\n");
		printf("\t\t\t\t\t(4)--BORRAR\n");
		printf("\t\t\t\t\t(0)--ATRAS\n\n\t\t\t\t\t\t\t");
		printf("\n\t\t\t\t\t\tOpcion: "); 
		scanf("%i",&opcion);
		system("cls");
		
		switch (opcion){
			case 1: llamadaAgregarVehiculo(&p);//LLAMADA A LA FUNCION llamadaAgregarVehiculo
				break;
			case 2: modificarVehiculo(&p);//LLAMADA A LA FUNCION modificarVehiculo
				break;
			case 3: menuConsultarVehiculo();//LLAMADA A LA FUNCION consultarVehiculo
				break;
			case 4: llamadaEliminarVehiculo();//LLAMADA A LA FUNCION eliminarVehiculo
				break;
		}
	}
}

void menuMantenimiento(){       //MENU MANTENIMIENTO
	int opcion=1;
	while(opcion){
		system("cls");
		encabezado();
		printf("\t\t\t\t\t     ---------------\n");
		printf("\t\t\t\t\t      MANTENIMIENTO\n");
		printf("\t\t\t\t\t     ---------------\n\n");
		printf("\t\t\t\t {POR FAVOR ESCRIBA LA OPCION QUE DESEA}\n\n");
		printf("\t\t\t\t\t(1)--PERSONAS\n");
		printf("\t\t\t\t\t(2)--VEHICULOS\n\n");
		printf("\t\t\t\t\t(0)--ATRAS\n\n\t\t\t\t\t\t\t");
		printf("\n\t\t\t\t\t\tOpcion: "); 
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

void menuOperaMultas(){   //MENU OPERACIONES Y CONSULTAS - OPERACIONES CON MULTAS
	int opcion = 1;
	while(opcion){
		system("cls");
		encabezado();
		printf("\t\t\t    -------------------------------------------------\n");
		printf("\t\t\t     OPERACIONES Y CONSULTAS->OPERACIONES CON MULTAS\n");
		printf("\t\t\t    -------------------------------------------------\n\n");
		printf("\t\t\t\t {POR FAVOR ESCRIBA LA OPCION QUE DESEA}\n\n");
		printf("\t\t\t\t\t(1)--AGREGAR\n");
		printf("\t\t\t\t\t(2)--PAGAR\n");
		printf("\t\t\t\t\t(3)--CONSULTAR POR NUMERO DE MULTA\n");
		printf("\t\t\t\t\t(4)--MOVER\n");
		printf("\t\t\t\t\t(5)--ELIMINAR\n\n");
		printf("\t\t\t\t\t(0)--ATRAS\n\n\t\t\t\t\t\t\t");
		printf("\n\t\t\t\t\t\tOpcion: "); 
		scanf("%i",&opcion);
		system("cls");
		
		switch (opcion){
			case 1: llamadaAgregarInfraccion(&p);//LLAMADA A LA FUNCION agregarMulta
				break;
			case 2: pagarInfraccion();//LLAMADA A LA FUNCION pagarMulta
				break;
			case 3: consultarInfraccion(p);//LLAMADA A LA FUNCION consultarPorMulta
				break;
			case 4: moverInfraccion();//LLAMADA A LA FUNCION moverMulta
				break;
			case 5: llamadaEliminarInfraccion();//LLAMADA A LA FUNCIÓN eliminarMulta
				break;
		}
	}

}

void menuConsultasdos(){   //MENU OPERACIONES Y CONSULTAS - CONSULTAS (OPCION 2.2)
	int opcion = 2;
	while(opcion){
		system("cls");
		encabezado();
		printf("\t\t\t\t  ------------------------------------\n");
		printf("\t\t\t\t   OPERACIONES Y CONSULTAS->CONSULTAS\n");
		printf("\t\t\t\t  ------------------------------------\n\n");
		printf("\t\t\t2.2 DADA UNA CEDULA DE IDENTIDAD MOSTRAR:...\n");
		printf("\t\t\t\t {POR FAVOR ESCRIBA LA OPCION QUE DESEA}\n\n");
		printf("\t\t(1)--2.2.1 LOS DATOS COMPLETOS DEL TITULAR Y SUS VEHICULOS (PLACA, MARCA\n"); 
		printf("\t\t           MODELO, A%cO Y COLOR) CON EL TOTAL DE VEHICULOS QUE POSEE Y EL TOTAL\n",164);
		printf("\t\t           DE MULTAS QUE ADEUDA EL TITULAR EN TOTAL\n\n");
		printf("\t\t(2)--2.2.2 APELLIDOS Y NOMBRE DEL TITULAR, SU CEDULA\n"); 
		printf("\t\t           LA PLACA DE CADA VEHICULO, MARCA, MODELO, A%cO Y EL TOTAL DE MULTAS\n",164); 
		printf("\t\t           PAGADAS Y NO PAGADAS DE CADA UNO\n\n"); 
		printf("\t\t(3)--2.2.3 DETALLES COMPLETOS DE LAS MULTAS NO PAGADAS DE TODOS SUS VEHICULOS\n");
		printf("\t\t           ORDENADAS POR NUMERO DE PLACA (ASCENDENTE) Y EL TOTAL ADEUDADO\n\n"); 
		printf("\t\t(4)--2.2.4 DADA UNA PLACA MOSTRAR TODAS LAS MULTAS COMPLETAS QUE HA TENIDO\n");
		printf("\t\t           ORDENADAS POR FECHA ASCENDENTE. PRIMERO LAS QUE NO HAN SIDO PAGADAS\n"); 
		printf("\t\t           Y LUEGO LAS YA CANCELADAS\n\n"); 
		printf("\t\t(5)--2.2.5 DADO UN TIPO DE INFRACCION MOSTRAR LAS MULTAS COMPLETAS QUE HA TENIDO\n");
		printf("\t\t           AGRUPADAS POR: VEHICULO (PLACA, MARCA, A%cO) Y ORDENAR POR FECHA DE\n",164); 
		printf("\t\t           INFRACCION (ASCENDENTE)\n\n"); 
		printf("\t\t(0)--ATRAS\n\n\t\t\t\t\t\t\t");
		printf("\n\t\t\t\t\t\tOpcion: "); 
		scanf("%i",&opcion);
		system("cls");
		switch (opcion){
			case 1: funcionDosDosUno (p); //LLAMADA A LA FUNCION 2.2.1 PARA BUSCAR LAS DEUDAS
				break;
			case 2: funcionDosDosDos (p);//LLAMADA A LA FUNCION 2.2.2
				break;
			case 3: funcionDosDosTres(p);//LLAMADA A LA FUNCION 2.2.3
				break;
			case 4: funcionDosDosCuatro(p);//LLAMADA A LA FUNCION 2.2.4
				break;
			case 5: funcionDosDosCinco(p);//LLAMADA A LA FUNCION 2.2.5
		}
	}
}

void menuConsultascuatro(){   //MENU OPERACIONES Y CONSULTAS - CONSULTAS (OPCION 2.4)
	int opcion = 4;
	while(opcion){
		system("cls");
		encabezado();
		printf("\t\t\t\t  ------------------------------------\n");
		printf("\t\t\t\t   OPERACIONES Y CONSULTAS->CONSULTAS\n");
		printf("\t\t\t\t  ------------------------------------\n\n");
		printf("\t\t\t2.4 DADO UN TIPO DE INFRACCION Y DOS A%cOS (PUEDE SER EL MISMO):...\n",164);
		printf("\t\t\t\t {POR FAVOR ESCRIBA LA OPCION QUE DESEA}\n\n");
		printf("\t\t(1)--2.4.1 TODAS LAS MULTAS NO PAGADAS (CEDULA, APELLIDOS Y NOMBRE, \n"); 
		printf("\t\t           PLACA, MARCA, A%cO, FECHA DE MULTA, MONTO) ORDENADO POR \n",164);
		printf("\t\t           NUMERO DE CEDULA DE LOS INFRACTORES (DESCENDENTE) Y EL \n");
		printf("\t\t           TOTAL DE INGRESO PENDIENTE POR MULTAS NO PAGADAS\n\n",164); 
		printf("\t\t(2)--2.4.2 TODAS LAS MULTAS PAGADAS (CEDULA, APELLIDOS Y NOMBRE, PLACA, \n");
		printf("\t\t           MARCA A%cO, FECHA DE MULTA, MONTO) ORDENADO POR NUMERO DE \n",164); 
		printf("\t\t           CEDULA DE LOS INFRACTORES (ASCENDIENTE) Y EL TOTAL DE INGRESO\n"); 
		printf("\t\t           POR MULTAS YA PAGADAS\n\n");
		printf("\t\t(0)--ATRAS\n\n\t\t\t\t\t\t\t");
		printf("\n\t\t\t\t\t\tOpcion: "); 
		scanf("%i",&opcion);
		system("cls");
		switch (opcion){
			case 1: funcionesDosCuatro(p,0);//LLAMADA A LA FUNCION consultaPorPersona
				break;
			case 2: funcionesDosCuatro(p,1);//LLAMADA A LA FUNCION 
				break;
		}
	}
}

void menuConsultas(){    //MENU OPERACIONES Y CONSULTAS - CONSULTAS
	int opcion = 1;
	while(opcion){
		system("cls");
		encabezado();
		printf("\t\t\t\t  ------------------------------------\n");
		printf("\t\t\t\t   OPERACIONES Y CONSULTAS->CONSULTAS\n");
		printf("\t\t\t\t  ------------------------------------\n\n");
		printf("\t\t\t\t {POR FAVOR ESCRIBA LA OPCION QUE DESEA}\n\n");
		printf("\t\t(1)--2.1 DADO EL NOMBRE DE UNA PERSONA:\n"); 
		printf("\t\t            BUSCAR TODOS LOS SINONIMOS QUE HAY EN EL SISTEMA Y\n");
		printf("\t\t            MOSTRAR CEDULA, APELLIDOS Y NOMBRES, FECHA DE NACIMIENTO,\n");
		printf("\t\t            DIRECCION Y CIUDAD DE NACIMIENTO (PARA TRATAR DE UBICAR \n");
		printf("\t\t            LA CEDULA DE LA PERSONA QUE NOS INTERESA)\n\n");
		printf("\t\t(2)--2.2 DADA UNA CEDULA DE IDENTIDAD:...\n\n"); 
		printf("\t\t(3)--2.3 DADA (SOLO) UNA PLACA MOSTRAR:\n"); 
		printf("\t\t            TODAS LAS MULTAS DE ESE VEHICULO ORDENADAS POR NUMERO DE MULTA\n"); 
		printf("\t\t            (ASCENDENTE), EL TOTAL DE MULTAS PAGADAS Y EL DE LAS NO PAGADAS\n\n"); 
		printf("\t\t(4)--2.4 DADO EL TIPO DE INFRACCION Y DOS A%cOS (PUEDE SER EL MISMO):...\n\n",164); 
		printf("\t\t(0)--ATRAS\n\n\t\t\t\t\t\t\t");
		printf("\n\t\t\t\t\t\tOpcion: "); 
		scanf("%i",&opcion);
		system("cls");
		switch (opcion){
			case 1: consultarPersonaNombre(p);//LLAMADA A LA FUNCION consultaPorPersona
				break;
			case 2: //LLAMADA A LA FUNCION menu2.2
				menuConsultasdos();
				break;
			case 3: funcionDosTres(p);//LLAMADA A LA FUNCION consultaPorPlaca
				break;
			case 4: //LLAMADA A LA FUNCION menu2.4
				menuConsultascuatro();
				break;
		}
	}
}

void menuOperacionesConsultas(){  //MENU OPERACIONES Y CONSULTAS
	int opcion= 1;
	while(opcion){
		system("cls");
		encabezado();
		printf("\t\t\t\t\t -------------------------\n");
		printf("\t\t\t\t\t  OPERACIONES Y CONSULTAS\n");
		printf("\t\t\t\t\t -------------------------\n\n");
		printf("\t\t\t\t {POR FAVOR ESCRIBA LA OPCION QUE DESEA}\n\n");
		printf("\t\t\t\t\t(1)--OPERACIONES CON MULTAS\n");
		printf("\t\t\t\t\t(2)--CONSULTAS\n\n");
		printf("\t\t\t\t\t(0)--ATRAS\n\n\t\t\t\t\t\t\t");
		printf("\n\t\t\t\t\t\tOpcion: "); 
		scanf("%i",&opcion);
		system("cls");
		
		switch (opcion){
			case 1: menuOperaMultas();//LLAMADA A LA FUNCION menuOperaMultas
				break;
			case 2: //LLAMADA A LA FUNCION menuConsultas
				menuConsultas();
				break;
		}
	}
}

void menuConsultarPersona(){ //MENU MANTENIMIENTO - PERSONAS - CONSULTAR
	int opcion = 1;
	while(opcion){
		encabezado();
		printf("\t\t\t\t  ------------------------------------\n");
		printf("\t\t\t\t   MANTENIMIENTO->PERSONAS->CONSULTAR\n");
		printf("\t\t\t\t  ------------------------------------\n\n");
		printf("\t\t\t\t {POR FAVOR ESCRIBA LA OPCION QUE DESEA}\n\n");
		printf("\t\t\t\t\t(1)--CONSULTAR POR NOMBRE, APELLIDO O NOMBRE COMPLETO\n");
		printf("\t\t\t\t\t(2)--CONSULTAR POR CEDULA\n");
		printf("\t\t\t\t\t(0)--ATRAS\n\n\t\t\t\t\t\t\t");
		printf("\n\t\t\t\t\t\tOpcion: "); 
		scanf("%i",&opcion);
		system("cls");
		
		switch (opcion){
			case 1: consultarPersonaNombre(p);//LLAMADA A LA FUNCION agregarPersona
				break;
			case 2: consultarPersonaCedula(0);//LLAMADA A LA FUNCION modificarPersona
					printf("\n\n");
					system("pause");
					system("cls");
				break;
		}
	}
}

void menuConsultarVehiculo(){  //MENU MANTENIMIENTO - VEHICULO - CONSULTAR
	int opcion = 1;
	while(opcion){
		system("cls");
		encabezado();
		printf("\t\t\t\t  ------------------------------------\n");
		printf("\t\t\t\t   MANTENIMIENTO->VEHICULO->CONSULTAR\n");
		printf("\t\t\t\t  ------------------------------------\n\n");
		printf("\t\t\t\t {POR FAVOR ESCRIBA LA OPCION QUE DESEA}\n\n");
		printf("\t\t\t\t\t(1)--CONSULTAR POR PLACA\n");
		printf("\t\t\t\t\t(2)--CONSULTAR POR CEDULA DE PROPIETARIO\n");
		printf("\t\t\t\t\t(0)--ATRAS\n\n\t\t\t\t\t\t\t");
		printf("\n\t\t\t\t\t\tOpcion: "); 
		scanf("%i",&opcion);
		system("cls");
		
		switch (opcion){
			case 1: consultarVehiculoPlaca(p);
				break;
			case 2: consultarVehiculoCedula(p);
				break;
		}
	}
}
///////////////////////////////////////////////////////////FUNCIONES MENUS///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////FUNCIONES AGREGAR///////////////////////////////////////////////////////////////

struct infraccion * agregarInfraccion(){  //FUNCION PARA AGREGAR UNA INFRACCION AL VEHICULO
	int num;

	struct infraccion *auxInfraccion = new struct infraccion;  //RESERVO MEMORIA DEL TIPO DE ESTRUCTURA DEL VEHICULO
	system("cls");
	printf("\n\t\t\tIngrese el numero de infraccion: "); 
	scanf("%i",&auxInfraccion->numero);
	
		while(buscarInfraccion(auxInfraccion->numero)){
			system("cls");
			printf("\n\n\t\t\t\tEse numero de infraccion ya está registrado\n\n");
			system("pause");
			system("cls");
			printf("\n\t\t\tIngrese el numero de infraccion: "); 
			scanf("%i",&auxInfraccion->numero);
		}
	
	freeBuffer();
	printf("\n\t\t\tIngrese el tipo de infraccion: "); 
	gets(auxInfraccion->tipo);
	strcpy(auxInfraccion->tipo,strupr(auxInfraccion->tipo));
	
	printf("\n\t\t\tIngrese el monto de la infraccion: "); 
	scanf("%i",&auxInfraccion->monto);

	printf("\n\t\t\tIngrese el dia en que se registro la infraccion: ");
	scanf("%i",&(*auxInfraccion).fechaInfraccion.dd);
	
	while(auxInfraccion->fechaInfraccion.dd>31||(auxInfraccion->fechaInfraccion.dd<=0)){ //**********VALIDACION DE DIA DE REGISTRO DE INFRACCION************************
		system("cls");
		printf("\n\n\t\t\t\tIngrese un valor valido (1-31)\n\n");
		system("pause");
		system("cls");
		printf("\n\n\t\t\t- Numero de infraccion: %i",auxInfraccion->numero);
		printf("\n\n\t\t\t- Tipo de infraccion: %s",auxInfraccion->tipo);
		printf("\n\n\t\t\t- Monto de la infraccion: %i \n",auxInfraccion->monto);
		printf("\n\n\t\t\tIngrese el dia en que se registro la infraccion: ");
		scanf("%i",&(*auxInfraccion).fechaInfraccion.dd);
	}
	
	printf("\n\t\t\tIngrese el mes en que se registro la infraccion: "); 
	scanf("%i",&(*auxInfraccion).fechaInfraccion.mm);
	
	while((auxInfraccion->fechaInfraccion.mm>12)||(auxInfraccion->fechaInfraccion.mm<=0)){ //**********VALIDACION DEL MES DE REGISTRO INFRACCION************************
		system("cls");
		printf("\n\n\t\t\t\tIngrese un valor valido (1-12)\n\n");
		system("pause");
		system("cls");
		printf("\n\n\t\t\t- Numero de infraccion: %i",auxInfraccion->numero);
		printf("\n\n\t\t\t- Tipo de infraccion: %s",auxInfraccion->tipo);
		printf("\n\n\t\t\t- Monto de la infraccion: %i",auxInfraccion->monto);
		printf("\n\n\t\t\t- Dia en que se registro la infraccion: %i \n",auxInfraccion->fechaInfraccion.dd);
		printf("\n\n\t\t\tIngrese el mes en que se registro la infraccion: ");
		scanf("%i",&(*auxInfraccion).fechaInfraccion.mm);
	}

	printf("\n\t\t\tIngrese el a%co en que se registro la infraccion: ",164); 
	scanf("%i",&(*auxInfraccion).fechaInfraccion.yy);
	
	while((auxInfraccion->fechaInfraccion.yy>2020)||(auxInfraccion->fechaInfraccion.yy<1)){  //**********VALIDACION DEL AÃ‘O DE REGISTRO INFRACCION****************
		system("cls");
		printf("\n\n\t\t\t\tIngrese un valor valido (desde 1 hasta 2020)\n\n");
		system("pause");
		system("cls");
		printf("\n\n\t\t\t- Numero de infraccion: %i",auxInfraccion->numero);
		printf("\n\n\t\t\t- Tipo de infraccion: %s",auxInfraccion->tipo);
		printf("\n\n\t\t\t- Monto de la infraccion: %i",auxInfraccion->monto);
		printf("\n\n\t\t\t- Dia en que se registro la infraccion: %i",auxInfraccion->fechaInfraccion.dd);
		printf("\n\n\t\t\t- Mes en que se registro la infraccion: %i \n",auxInfraccion->fechaInfraccion.mm);
		printf("\n\t\t\tIngrese el a%co en que se registro la infraccion: ",164);
		scanf("%i",&(*auxInfraccion).fechaInfraccion.yy);
	}
	
	freeBuffer();
	printf("\n\t\t\tIngrese si la multa ha sido pagada (SI/NO): "); 
	gets(auxInfraccion->pagado);
	strcpy(auxInfraccion->pagado,strupr(auxInfraccion->pagado));
	
	while ((strcmp(auxInfraccion->pagado,"SI")!=0)&&(strcmp(auxInfraccion->pagado,"NO")!=0)){   //******************VALIDACION SI PAGO MULTA O NO********************
		printf("\n\n\t\t\t\tLa respuesta introducida no es valida\n\n");
		printf("\n\n\t\t\t\tSolo se permiten las siguientes respuestas: 'SI' o 'NO'\n\n");
		system("pause");
		system("cls");
		printf("\n\n\t\t\t- Numero de infraccion: %i",auxInfraccion->numero);
		printf("\n\n\t\t\t- Tipo de infraccion: %s",auxInfraccion->tipo);
		printf("\n\n\t\t\t- Monto de la infraccion: %i",auxInfraccion->monto);
		printf("\n\n\t\t\t- Dia en que se registro la infraccion: %i",auxInfraccion->fechaInfraccion.dd);
		printf("\n\n\t\t\t- Mes en que se registro la infraccion: %i",auxInfraccion->fechaInfraccion.mm);
		printf("\n\n\t\t\t- A%co en que se registro la infraccion: %i \n",164,auxInfraccion->fechaInfraccion.yy);
		printf("\n\n\t\t\tIngrese si la multa ha sido pagada (SI/NO): "); 
		gets(auxInfraccion->pagado);
	}
	
	//auxInfraccion->infraccionProx = NULL;
	return auxInfraccion;
}

struct vehiculo * agregarVehiculo(){ //FUNCION PARA AGREGAR UN VEHICULO A UNA PERSONA
	system("cls");
	int num=0;
	char resp[2];
	freeBuffer();
	struct vehiculo *auxVehiculo = new struct vehiculo;  //RESERVO MEMORIA DEL TIPO DE ESTRUCTURA DEL VEHICULO

	printf("\n\t\t\tIngrese la placa (8 caracteres max): "); 
	gets(auxVehiculo->placa);
	
	strcpy(auxVehiculo->placa,strupr(auxVehiculo->placa));  //CONVIERTO LA PLACA EN PURAS MAYUSCULAS
	while((strlen(auxVehiculo->placa)>8)||buscarPlaca(p, auxVehiculo->placa)){                                     //**********VALIDACION DE LA LONGITUD DE LA PLACA*****
		if (buscarPlaca(p, auxVehiculo->placa)) printf("\n\n\t\t\t\tLa placa ya esta registrada en el sistema\n\n");
		else printf("\n\n\t\t\t\tIngreso una placa invalida (MAX 8 CARACTERES)\n\n");
		system("pause"); 
		system("cls");
		printf("\n\t\t\tIngrese la placa (8 caracteres max): "); 
		gets(auxVehiculo->placa);
		strcpy(auxVehiculo->placa,strupr(auxVehiculo->placa));  //CONVIERTO LA PLACA EN PURAS MAYUSCULAS
	}
	
	struct vehiculo *auxV = p->datosVehiculo;
	auxVehiculo->vehiculoProx = p->datosVehiculo;
	p->datosVehiculo = auxVehiculo;
	
	printf("\n\t\t\tIngrese la marca del vehiculo: "); 
	gets(auxVehiculo->marca);
	strcpy(auxVehiculo->marca,strupr(auxVehiculo->marca));
	
	printf("\n\t\t\tIngrese el modelo del vehiculo: "); 
	gets(auxVehiculo->modelo);
	strcpy(auxVehiculo->modelo,strupr(auxVehiculo->modelo));
	
	printf("\n\t\t\tIngrese el a%co (yyyy): ",164); 
	scanf("%i",&auxVehiculo->annio.yy);
	validarAnnioV(&auxVehiculo);             //**********VALIDACION DEL AÃ‘O DEL MODELO VEHICULO************************
		
	freeBuffer();
	printf("\n\t\t\tIngrese el color del vehiculo: "); 
	gets(auxVehiculo->color);
	strcpy(auxVehiculo->color,strupr(auxVehiculo->color));
	
	auxVehiculo->datosInfraccion = NULL;
	struct infraccion *auxInfraccion;
	printf("\n\n\t\t\tDesea registrar una infraccion a este vehiculo? (SI-NO): ");
	scanf("%s",resp);
	strcpy(resp,strupr(resp));
	while (num==0){
		while ((strcmp(resp,"SI")!=0)&&(strcmp(resp,"NO")!=0)){   //******************VALIDACION SI O NO********************
			printf("\n\n\t\t\t\tLa respuesta introducida no es valida\n\n");
			printf("\n\n\t\t\t\tSolo se permiten las siguientes respuestas: 'SI' o 'NO'\n\n");
			system("pause");
			system("cls");
			printf("\n\n\t\t\tDesea registrar una infraccion a este vehiculo? (SI-NO): "); 
			scanf("%s",resp);
			strcpy(resp,strupr(resp));
		}
		if (strcmp(resp,"SI")==0) {
			auxInfraccion = agregarInfraccion();
			auxInfraccion->infraccionProx = auxVehiculo->datosInfraccion;
			auxVehiculo->datosInfraccion = auxInfraccion;
			num=1;
		}
		if (strcmp(resp,"NO")==0) num=2;
	}
	while(num==1){
		printf("\n\n\t\t\tDesea registrar otra infraccion a este vehiculo? (SI-NO): ");
		scanf("%s",resp);
		strcpy(resp,strupr(resp));
		while ((strcmp(resp,"SI")!=0)&&(strcmp(resp,"NO")!=0)){   //******************VALIDACION SI O NO********************
			printf("\n\n\t\t\t\tLa respuesta introducida no es valida\n\n");
			printf("\n\n\t\t\t\tSolo se permiten las siguientes respuestas: 'SI' o 'NO'\n\n");
			system("pause");
			system("cls");
			printf("\n\n\t\t\tDesea registrar otra infraccion a este vehiculo? (SI-NO): "); 
			scanf("%s",resp);
			strcpy(resp,strupr(resp));
		}
		if (strcmp(resp,"SI")==0) {
			auxInfraccion = agregarInfraccion();
			auxInfraccion->infraccionProx = auxVehiculo->datosInfraccion;
			auxVehiculo->datosInfraccion = auxInfraccion;
			num=1;
		}
		if (strcmp(resp,"NO")==0) num=2;
	}
	p->datosVehiculo = auxV;
	return auxVehiculo;
}

void agregarPersona(struct persona **p){ //FUNCION PARA AGREGAR UNA PERSONA
	
	freeBuffer();
	int num = 0;
	char resp[2];
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
		printf("\n\t\t\t- Nombre: %s \n",aux->nombre);
		printf("\n\n\t\t\tIngrese los apellidos (20 caracteres max): "); 
		gets(aux->apellidos);
	}
	strcpy(aux->apellidos,strupr(aux->apellidos));
	
	printf("\n\t\t\tIngrese la cedula: ");
	scanf("%li",&aux->cedula);
	
	while((buscarCedula(*p, aux->cedula))||(aux->cedula<=0)){                     //*****************VALIDACION DE CEDULA***********************	
		system("cls");
		printf("\n\n\t\t\tEsa cedula ya esta registrada en el sistema o es una cedula invalida.\n\n");
		system("pause");
		system("cls");
		printf("\n\t\t\t- Nombre: %s",aux->nombre);
		printf("\n\n\t\t\t- Apellidos (20 caracteres max): %s \n",aux->apellidos);
		printf("\n\n\t\t\tIngrese la cedula: ");
		scanf("%li",&aux->cedula);
	}
	struct persona *auxP = *p;
	aux->personaProx = *p;
	*p = aux;
	
	printf("\n\t\t\tIngrese el dia de nacimiento: ");
	scanf("%i",&(*aux).fechaNacimiento.dd);
	validarDia(&aux);                       //**********VALIDACION DE DIA DE NACIMIENTO************************
	
	printf("\n\t\t\tIngrese el mes de nacimiento: ");
	scanf("%i",&(*aux).fechaNacimiento.mm);
	validarMes(&aux);                       //**********VALIDACION DEL MES DE NACIMIENTO************************
	
	printf("\n\t\t\tIngrese el a%co (yyyy) de nacimiento: ",164);
	scanf("%i",&aux->fechaNacimiento.yy);
	validarAnnio(&aux);                     //**********VALIDACION DEL AÃ‘O DE NACIMIENTO************************
	
	freeBuffer();
	printf("\n\t\t\tIngrese la ciudad de nacimiento (40 caracteres max): ");
	gets(aux->place.ciudad);
	
	while(strlen(aux->place.ciudad)>40){                                //**********VALIDACION DE LA CIUDAD**********
		system("cls");
		printf("\n\n\t\t\t\tSolo se permiten max 40 caracteres\n\n");
		system("pause");
		system("cls");
		printf("\n\t\t\t- Nombre: %s",aux->nombre);
		printf("\n\n\t\t\t- Apellidos: %s",aux->apellidos);
		printf("\n\n\t\t\t- Cedula: %li",aux->cedula);	
		printf("\n\n\t\t\t- Dia (dd) de nacimiento: %i",aux->fechaNacimiento.dd);
		printf("\n\n\t\t\t- Mes (mm) de nacimiento: %i",aux->fechaNacimiento.mm);
		printf("\n\n\t\t\t- A%co (yyyy) de nacimiento: %i \n",164,aux->fechaNacimiento.yy);
		printf("\n\n\t\t\tIngrese la ciudad de nacimiento (40 caracteres max): ");
		gets(aux->place.ciudad);
	}
	strcpy(aux->place.ciudad,strupr(aux->place.ciudad));
	
	printf("\n\t\t\tIngrese la direccion de vivienda (40 caracteres max): ");
	gets(aux->place.direccion);
	
	while(strlen(aux->place.direccion)>40){                  //**********VALIDACION DE LA DIRECCION**********
		system("cls");                                   
		printf("\n\n\t\t\t\tSolo se permiten max 40 caracteres\n\n");
		system("pause");
		system("cls");
		printf("\n\t\t\t- Nombre: %s",aux->nombre);
		printf("\n\n\t\t\t- Apellidos: %s",aux->apellidos);
		printf("\n\n\t\t\t- Cedula: %li",aux->cedula);	
		printf("\n\n\t\t\t- Dia (dd) de nacimiento: %i",aux->fechaNacimiento.dd);
		printf("\n\n\t\t\t- Mes (mm) de nacimiento: %i",aux->fechaNacimiento.mm);
		printf("\n\n\t\t\t- A%co (yyyy) de nacimiento: %i",164,aux->fechaNacimiento.yy);
		printf("\n\n\t\t\t- Ciudad de nacimiento (40 caracteres max): %s \n",aux->place.ciudad);
		printf("\n\n\t\t\tIngrese la direccion (40 caracteres max): ");
		gets(aux->place.direccion);
	}
	strcpy(aux->place.direccion,strupr(aux->place.direccion));
	
	aux->datosVehiculo = NULL;
	struct vehiculo *auxVehiculo;
	printf("\n\n\t\t\tDesea registrar un vehiculo a este usuario? (SI-NO): ");
	scanf("%s",resp);
	strcpy(resp,strupr(resp));
	while (num==0){
		while ((strcmp(resp,"SI")!=0)&&(strcmp(resp,"NO")!=0)){   //******************VALIDACION SI O NO********************
			printf("\n\n\t\t\t\tLa respuesta introducida no es valida\n\n");
			printf("\n\n\t\t\t\tSolo se permiten las siguientes respuestas: 'SI' o 'NO'\n\n");
			system("pause");
			system("cls");
			printf("\n\n\t\t\tDesea registrar un vehiculo a este usuario? (SI-NO): "); 
			scanf("%s",resp);
			strcpy(resp,strupr(resp));
		}
		if (strcmp(resp,"SI")==0) {
			auxVehiculo = agregarVehiculo();
			auxVehiculo->vehiculoProx = aux->datosVehiculo;
			aux->datosVehiculo = auxVehiculo;
			num=1;
		}
		if (strcmp(resp,"NO")==0) num=2;
	}
	while(num==1){
		printf("\n\n\t\t\tDesea agregar otro vehiculo a este usuario? (SI-NO): "); 
		scanf("%s",resp);
		strcpy(resp,strupr(resp));
		while ((strcmp(resp,"SI")!=0)&&(strcmp(resp,"NO")!=0)){   //******************VALIDACION SI O NO********************
			printf("\n\n\t\t\t\tLa respuesta introducida no es valida\n\n");
			printf("\n\n\t\t\t\tSolo se permiten las siguientes respuestas: 'SI' o 'NO'\n\n");
			system("pause");
			system("cls");
			printf("\n\n\t\t\tDesea agregar otro vehiculo a este usuario? (SI-NO): "); 
			scanf("%s",resp);
			strcpy(resp,strupr(resp));
		}
		if (strcmp(resp,"SI")==0) {
			auxVehiculo = agregarVehiculo();
			auxVehiculo->vehiculoProx = aux->datosVehiculo;
			aux->datosVehiculo = auxVehiculo;
			num=1;
		}
		if (strcmp(resp,"NO")==0) num=2;
	}
	system("cls");
	//ordenarBurbuja(&aux->datosVehiculo);
	mostrarPersona(aux);
	//freeBuffer();
	printf("\n\n\t\t\tDesea guardar estos datos? (SI-NO): ");
	scanf("%s",&resp);
	strcpy(resp,strupr(resp));
	while ((strcmp(resp,"SI")!=0)&&(strcmp(resp,"NO")!=0)){   //******************VALIDACION SI O NO********************
		printf("\n\n\t\t\t\tLa respuesta introducida no es valida\n\n");
		printf("\n\n\t\t\t\tSolo se permiten las siguientes respuestas: 'SI' o 'NO'\n\n");
		system("pause");
		system("cls");
		printf("\n\n\t\t\tDesea guardar estos datos? (SI-NO): "); 
		scanf("%s",&resp);
		strcpy(resp,strupr(resp));
	}
	if (strcmp(resp,"SI")==0) guardarData(*p);
	else *p = auxP;
	system("cls");
}

void llamadaAgregarVehiculo(struct persona **p){ //FUNCION PARA VERIFICAR ANTES DE AGREGAR UN VEHICULO A UNA PERSONA
	int cedula, posicion;
	char resp[2];
	struct persona *auxPersona = NULL;
	struct vehiculo *auxVehiculo;
	if(!*p){
		printf("\n\n\t\t\tNo existen usuarios ingresados al sistema. Por favor cargue uno\n\n");
		system("pause");
		return;
	}
	while(!auxPersona){
		
		printf("\n\tIngrese la cedula del propietario del vehiculo (Ya debe estar registrado en el sistema)");
		printf("\n\n\t\t\t(0) Salir\n\n\t\t\t\t");
		scanf("%i",&cedula);
		if(!cedula) return;
		auxPersona=buscarCedula(*p,cedula);
		if (!auxPersona){
			system("cls");
			printf("\n\n\t\t\t\tEsa cedula no se encuentra en el sistema\n\n");
			system("pause");
			system("cls");	
		}	
	}
	system("cls");
	//freeBuffer();
	auxVehiculo = agregarVehiculo();
	printf("\n\n\t\t\tDesea guardar estos datos? (SI-NO): ");
	scanf("%s",&resp);
	strcpy(resp,strupr(resp));
	while ((strcmp(resp,"SI")!=0)&&(strcmp(resp,"NO")!=0)){   //******************VALIDACION SI O NO********************
		printf("\n\n\t\t\t\tLa respuesta introducida no es valida\n\n");
		printf("\n\n\t\t\t\tSolo se permiten las siguientes respuestas: 'SI' o 'NO'\n\n");
		system("pause");
		system("cls");
		printf("\n\n\t\t\tDesea guardar estos datos? (SI-NO): "); 
		scanf("%s",&resp);
		strcpy(resp,strupr(resp));
	}
	if (strcmp(resp,"SI")==0) {
		auxVehiculo->vehiculoProx = auxPersona->datosVehiculo;
		auxPersona->datosVehiculo = auxVehiculo;
		guardarData(*p);
	}
	//ordenarBurbuja(&aux->datosVehiculo);
}

void llamadaAgregarInfraccion(struct persona **p){  //FUNCION PARA VERIFICAR ANTES DE AGREGAR UNA INFRACCION A UN VEHICULO
	int posicion;
	char placa[8],resp[2];
	struct vehiculo *auxVehiculo = NULL;
	struct infraccion * auxInfraccion;
	if(!*p){
		printf("\n\n\t\t\tNo existen usuarios ingresados al sistema. Por favor cargue uno\n\n");
		system("pause");
		return;
	}
	while(!auxVehiculo){
		
		printf("\n\tIngrese la placa del vehiculo (Ya debe estar registrado en el sistema)");
		printf("\n\n\t\t\t(0) Salir\n\n\t\t\t\t");
		freeBuffer();
		gets(placa);
		if(!strcmp(placa,"0")) return;
		strcpy(placa,strupr(placa));
		auxVehiculo=buscarPlaca(*p,placa);
		if (!auxVehiculo){
			system("cls");
			printf("\n\n\t\t\t\tEsa placa no se encuentra en el sistema\n\n");
			system("pause");
			system("cls");	
		}	
	}
	system("cls");
	//freeBuffer();
	auxInfraccion = agregarInfraccion();
	printf("\n\n\t\t\tDesea guardar estos datos? (SI-NO): ");
	scanf("%s",resp);
	strcpy(resp,strupr(resp));
	while ((strcmp(resp,"SI")!=0)&&(strcmp(resp,"NO")!=0)){   //******************VALIDACION SI O NO********************
		printf("\n\n\t\t\t\tLa respuesta introducida no es valida\n\n");
		printf("\n\n\t\t\t\tSolo se permiten las siguientes respuestas: 'SI' o 'NO'\n\n");
		system("pause");
		system("cls");
		printf("\n\n\t\t\tDesea guardar estos datos? (SI-NO): "); 
		scanf("%s",resp);
		strcpy(resp,strupr(resp));
	}
	if (strcmp(resp,"SI")==0) {
		auxInfraccion->infraccionProx = auxVehiculo->datosInfraccion;
		auxVehiculo->datosInfraccion = auxInfraccion;
		guardarData(*p);
	}
}

///////////////////////////////////////////////////////////FUNCIONES AGREGAR///////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////FUNCIONES MODIFICAR/MOVER///////////////////////////////////////////////////////////////

void modificarVehiculo(struct persona **p){   //FUNCION PARA MODIFICAR EN EL SISTEMA A UN VEHICULO
	system("cls");
	int respuesta=0;
	char placa[8],resp[2];
	struct persona *persona;
	struct vehiculo *vehiculo = NULL;
	freeBuffer();
	if(!*p){ //VALIDO PARA SABER SI LA BASE DE DATOS ESTA VACIA
		printf("\n\t\t\tLa base de datos esta vacia. Ingrese una persona al sistema para continuar\n\n");
		system("pause");
		return;
	}
	while(strcmp(resp,"SI")!=0&&strcmp(resp,"NO")!=0){
		while(!vehiculo){
			printf("\n\t\t\tIngrese una placa para buscar en el sistema.");
			printf("\n\t\t\t(0) Para salir\n\t\t\t");
			gets(placa);
			if (!strcmp(placa,"0")) return;
			strcpy(placa,strupr(placa));
			vehiculo = buscarPlaca(*p, placa);
			if(!vehiculo){
				system("cls");
				printf("\n\t\t\tLa placa no se encuentra en el sistema, intente de nuevo: \n");
				system("pause");
				system("cls");
			}
		}
		persona = buscarTitularVehiculo(*p, placa);
		printf("\n\n\t\t\tDesea modificar los datos de este vehiculo? (SI-NO): \n\t\t\t");
		printf("\n\n\t\t\t- Propietario: %s %s",persona->nombre,persona->apellidos);
		printf("\n\t\t\t- Cedula: %i",persona->cedula);
		printf("\n\n\t\t- Placa: %s",vehiculo->placa);
		printf("\n\n\t\t- Marca: %s",vehiculo->marca);
		printf("\n\n\t\t- Modelo: %s",vehiculo->modelo);
		printf("\n\n\t\t- A%co: %i",164,vehiculo->annio.yy);
		printf("\n\t\t\t- Color: %s\n\n\t\t\t\t\t\t",vehiculo->color);
		scanf("%s",&resp);
		strcpy(resp,strupr(resp));
		while ((strcmp(resp,"SI")!=0)&&(strcmp(resp,"NO")!=0)){   //******************VALIDACION SI O NO********************
			printf("\n\n\t\t\t\tLa respuesta introducida no es valida\n\n");
			printf("\n\n\t\t\t\tSolo se permiten las siguientes respuestas: 'SI' o 'NO'\n\n");
			system("pause");
			system("cls");
			printf("\n\n\t\t\tDesea modificar los datos del vehiculo? (SI-NO): "); 
			scanf("%s",&resp);
			strcpy(resp,strupr(resp));
		}
	}
	freeBuffer();
	if (!strcmp(resp,"SI")){
		printf("\n\n\t\t\t- Placa: %s \n",vehiculo->placa);
		printf("\n\n\t\t\tIngrese la marca del vehiculo: "); 
		gets(vehiculo->marca);
		strcpy(vehiculo->marca,strupr(vehiculo->marca));
	
		printf("\n\n\t\t\tIngrese el modelo del vehiculo: "); 
		gets(vehiculo->modelo);
		strcpy(vehiculo->modelo,strupr(vehiculo->modelo));
	
		printf("\n\n\t\t\tIngrese el a%co (yyyy): ",164); 
		scanf("%i",&vehiculo->annio.yy);
		validarAnnioV(&vehiculo);             //**********VALIDACION DEL AÃ‘O DEL MODELO VEHICULO************************
		guardarData(*p);
		printf("\n\n\t\t\t\tDATOS GUARDADOS CON EXITO\n");
	}
	system("pause");
	freeBuffer();
	system("cls");
}

void modificarPersona(struct persona **p){  //FUNCION PARA MODIFICAR EN EL SISTEMA A UNA PERSONA
	system("cls");
	char resp[2];
	int cedula;
	struct persona *aux;
	strcpy(resp, "  ");
	if(!*p){ //VALIDO PARA SABER SI LA BASE DE DATOS ESTA VACIA
		printf("\n\t\t\tLa base de datos esta vacia. Ingrese una persona al sistema para continuar\n");
		system("pause");
		return;
	}
	while(strcmp(resp,"SI")!=0&&strcmp(resp,"NO")!=0){
		system("cls");
		printf("\n\t\t\tIngrese una cedula para buscar en el sistema.");
		printf("\n\t\t\t(0) Para salir\n\t\t\t");
		scanf("%i",&cedula);
		if (!cedula) return;
		aux = buscarCedula(*p, cedula);
		
		while(!aux){
			system("cls");
			printf("\n\t\t\tLa cedula no se encuentra en el sistema, intente de nuevo: \n");
			system("pause");
			system("cls");
			printf("\n\t\t\tIngrese una cedula para buscar en el sistema.");
			printf("\n\t\t\t(0) Para salir\n\t\t\t");
			scanf("%i",&cedula);
			if (!cedula) return;
			aux = buscarCedula(*p, cedula);
		}
		printf("\n\n\t\t\tDesea modificar los datos de esta persona? (SI-NO): \n\t\t\t");
		printf("\n\n\t\t\t- Nombre: %s   Apellido: %s",aux->nombre,aux->apellidos);
		printf("\n\t\t\t- Cedula: %i\n\n\t\t\t\t\t\t",cedula);
		scanf("%s",&resp);
		strcpy(resp,strupr(resp));
		while ((strcmp(resp,"SI")!=0)&&(strcmp(resp,"NO")!=0)){   //******************VALIDACION SI O NO********************
			printf("\n\n\t\t\t\tLa respuesta introducida no es valida\n\n");
			printf("\n\n\t\t\t\tSolo se permiten las siguientes respuestas: 'SI' o 'NO'\n\n");
			system("pause");
			system("cls");
			printf("\n\n\t\t\tDesea modificar los datos de la persona? (SI-NO): "); 
			scanf("%s",&resp);
			strcpy(resp,strupr(resp));
		}
	}
	freeBuffer();
	if (!strcmp(resp,"SI")){
		//freeBuffer();
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
			printf("\n\t\t\t- Nombre: %s \n",aux->nombre);
			printf("\n\n\t\t\tIngrese los apellidos (20 caracteres max): "); 
			gets(aux->apellidos);
		}
		strcpy(aux->apellidos,strupr(aux->apellidos));
		printf("\n\t\t\tCedula: %i (NO SE PUEDE MODIFICAR)",aux->cedula);
	
		printf("\n\t\t\tIngrese el dia de nacimiento: ");
		scanf("%i",&(*aux).fechaNacimiento.dd);
		validarDia(&aux);                       //**********VALIDACION DE DIA DE NACIMIENTO************************
		
		printf("\n\t\t\tIngrese el mes de nacimiento: ");
		scanf("%i",&(*aux).fechaNacimiento.mm);
		validarMes(&aux);                       //**********VALIDACION DEL MES DE NACIMIENTO************************
	
		printf("\n\t\t\tIngrese el a%co (yyyy) de nacimiento: ",164);
		scanf("%i",&aux->fechaNacimiento.yy);
		validarAnnio(&aux);                     //**********VALIDACION DEL AÃ‘O DE NACIMIENTO************************
	
		freeBuffer();
		printf("\n\t\t\tIngrese la ciudad de nacimiento (40 caracteres max): ");
		gets(aux->place.ciudad);
	
		while(strlen(aux->place.ciudad)>40){                                //**********VALIDACION DE LA CIUDAD**********
			system("cls");
			printf("\n\n\t\t\t\tSolo se permiten max 40 caracteres\n\n");
			system("pause");
			system("cls");
			printf("\n\t\t\t- Nombre: %s",aux->nombre);
			printf("\n\n\t\t\t- Apellidos: %s",aux->apellidos);
			printf("\n\n\t\t\t- Cedula: %i",aux->cedula);	
			printf("\n\n\t\t\t- Dia (dd) de nacimiento: %i",aux->fechaNacimiento.dd);
			printf("\n\n\t\t\t- Mes (mm) de nacimiento: %i",aux->fechaNacimiento.mm);
			printf("\n\n\t\t\t- A%co (yyyy) de nacimiento: %i \n",164,aux->fechaNacimiento.yy);
			printf("\n\n\t\t\tIngrese la ciudad de nacimiento (40 caracteres max): ");
			gets(aux->place.ciudad);
		}
		strcpy(aux->place.ciudad,strupr(aux->place.ciudad));
		
		printf("\n\t\t\tIngrese la direccion (40 caracteres max): ");
		gets(aux->place.direccion);
		
		while(strlen(aux->place.direccion)>40){                  //**********VALIDACION DE LA DIRECCION**********
			system("cls");                                   
			printf("\n\n\t\t\t\tSolo se permiten max 40 caracteres\n\n");
			system("pause");
			system("cls");
			printf("\n\t\t\t- Nombre: %s",aux->nombre);
			printf("\n\n\t\t\t- Apellidos: %s",aux->apellidos);
			printf("\n\n\t\t\t- Cedula: %i",aux->cedula);	
			printf("\n\n\t\t\t- Dia (dd) de nacimiento: %i",aux->fechaNacimiento.dd);
			printf("\n\n\t\t\t- Mes (mm) de nacimiento: %i",aux->fechaNacimiento.mm);
			printf("\n\n\t\t\t- A%co (yyyy) de nacimiento: %i",164,aux->fechaNacimiento.yy);
			printf("\n\n\t\t\t- Ciudad de nacimiento (40 caracteres max): %s \n",aux->place.ciudad);
			printf("\n\n\t\t\tIngrese la direccion (40 caracteres max): ");
			gets(aux->place.direccion);
		}
		strcpy(aux->place.direccion,strupr(aux->place.direccion));
		guardarData(*p);
		printf("\n\n\t\t\t\tDATOS GUARDADOS CON EXITO\n");	
	}
	system("pause");
	//freeBuffer();
	system("cls");
}

void pagarInfraccion(){   //FUNCION PARA REGISTRAR EL PAGO DE UNA INFRACCION
	int numero;
	char resp[2];
	struct infraccion * aux = NULL;
	if(!p){
		printf("\n\n\t\t\tNo existen usuarios ingresados al sistema. Por favor cargue uno\n\n");
		system("pause");
		return;
	}
	while(!aux){
		
		printf("\n\tIngrese el numero de infraccion que desea pagar (Ya debe estar registrado en el sistema)");
		printf("\n\n\t\t\t(0) Salir\n\n\t\t\t\t");
		freeBuffer();
		scanf("%i",&numero);
		if(!numero) return;
		aux=buscarInfraccion(numero);
		if (!aux){
			system("cls");
			printf("\n\n\t\t\t\tEse numero de infraccion no se encuentra en el sistema\n\n");
			system("pause");
			system("cls");	
		}
	}
	system("cls");
	if (!strcmp(aux->pagado,"SI")){
		printf("\n\n\n\n\t\t\t\tLa multa de numero %i ya ha sido pagada\n\n",aux->numero);
		system("pause");
		return;
	}
	struct persona *r =buscarInfraccionPersona(numero);
	struct vehiculo *v = buscarInfraccionVehiculo(numero);
	printf("\n\n\t\t\t\tDatos del propietario:");
	printf("\n\n\t\t\t\t\t- Nombre y apellidos: %s %s",r->nombre,r->apellidos);
	printf("\n\n\t\t\t\tDatos del vehiculo");
	printf("\n\n\t\t\t\t\t- Placa del vehiculo: %s",v->placa);
	printf("\n\n\t\t\t\tDatos de la infraccion");
	printf("\n\n\t\t\t\t\t- Tipo de multa: %s", aux->tipo);
	printf("\n\n\t\t\t\t\t- Multa numero: %i  Monto: %i",aux->numero,aux->monto);
	printf("\n\n\t\t\t\t\t- Fecha: %i/%i/%i  \n",aux->fechaInfraccion.dd,aux->fechaInfraccion.mm,aux->fechaInfraccion.yy);
	printf("\n\n\t\t\tDesea pagar esta multa? (SI-NO): ");
	scanf("%s",resp);
	strcpy(resp,strupr(resp));
	system("cls");
	while ((strcmp(resp,"SI")!=0)&&(strcmp(resp,"NO")!=0)){   //******************VALIDACION SI O NO********************
		printf("\n\n\t\t\t\tLa respuesta introducida no es valida\n\n");
		printf("\n\n\t\t\t\tSolo se permiten las siguientes respuestas: 'SI' o 'NO'\n\n");
		system("pause");
		system("cls");
		printf("\n\n\t\t\tDesea guardar estos datos? (SI-NO): "); 
		scanf("%s",resp);
		strcpy(resp,strupr(resp));
	}
	if (strcmp(resp,"SI")==0) {
		strcpy(aux->pagado, "SI");
		printf("\n\n\n\n\t\t\t\t\tLA MULTA SE HA PAGADO CON EXITO\n\n\n");
		guardarData(p);
	}
	else printf("\n\n\n\n\t\t\t\t    NO SE HA PAGADO LA MULTA, INTENTE DE NUEVO\n\n\n");
	system("pause");
}

void moverInfraccion(){  //FUNCION PARA MOVER LA INFRACCION
	system("cls");
	int numero;
	char placa[8],resp[2];
	struct infraccion *f=NULL;
	struct vehiculo *vOrigen;
	struct vehiculo *vDestino = NULL;
	struct persona *hOrigen;
	struct persona *hDestino;
	if(!p){
		printf("\n\n\t\t\tNo existen usuarios ingresados al sistema. Por favor cargue uno\n\n");
		system("pause");
		return;
	}
	while(!f){
		printf("\n\n\t\t\tIngrese el numero de la infraccion que desea mover:\n\t\t\t\t\t\t");
		scanf("%i",&numero);
		if (numero==0)return;
		f=buscarInfraccion(numero);
		if(!f){
			system("cls");
			printf("\n\n\t\t\t\tEse numero de infraccion no se encuentra en el sistema\n\n");
			system("pause");
			system("cls");
		}
	}
	vOrigen= buscarInfraccionVehiculo(f->numero);
	hOrigen= buscarInfraccionPersona(f->numero);
	while(!vDestino){
		printf("\n\n\t\tIngrese la placa del vehiculo al que se le agregara la infraccion:\n\t\t\t\t\t\t");
		freeBuffer();
		gets(placa);
		strcpy(placa,strupr(placa));
		vDestino = buscarPlaca(p,placa);
		if(!vDestino){
			system("cls");
			printf("\n\n\t\t\t\tEsa placa no se encuentra en el sistema\n\n");
			system("pause");
			system("cls");
		}
	}
	hDestino= buscarTitularVehiculo(p,placa);
	printf("\n\n\t\tDatos origen:\t\t\tDatos destino:");
	printf("\n\n\t\t  - Vehiculo: %s\t\t\t  Vehiculo: %s",vOrigen->placa,vDestino->placa);
	printf("\n\t\t  - Propietario: %s\t\t  Propietario %s",hOrigen->nombre,hDestino->nombre);
	printf("\n\n\t\t\tDesea mover la infraccion desde Datos origen a Datos destino? (SI-NO): ");
	scanf("%s",resp);
	strcpy(resp,strupr(resp));
	system("cls");
	while ((strcmp(resp,"SI")!=0)&&(strcmp(resp,"NO")!=0)){   //******************VALIDACION SI O NO********************
		printf("\n\n\t\t\t\tLa respuesta introducida no es valida\n\n");
		printf("\n\n\t\t\t\tSolo se permiten las siguientes respuestas: 'SI' o 'NO'\n\n");
		system("pause");
		system("cls");
		printf("\n\n\t\t\tDesea guardar estos datos? (SI-NO): "); 
		scanf("%s",resp);
		strcpy(resp,strupr(resp));
	}
	if (strcmp(resp,"SI")==0) {
		vOrigen->datosInfraccion = vOrigen->datosInfraccion->infraccionProx;
		f->infraccionProx = vDestino->datosInfraccion;
		vDestino->datosInfraccion = f;
		guardarData(p);
		printf("\n\n\n\t\t\tDATOS MODIFICADOS EXITOSAMENTE");
		system("pause");
	}
}
////////////////////////////////////////////////////////FUNCIONES MODIFICAR/MOVER///////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////FUNCIONES CONSULTA/BUSCAR///////////////////////////////////////////////////////////////

struct persona *buscarTitularVehiculo(struct persona *q, char placa[8]){ //Retorna NULL si no consigue la placa.			   	   //sino, retorna el apuntador de esa placa
	while(q){
		struct vehiculo *vehiculo = q->datosVehiculo;
		while(vehiculo){
			if (!strcmp(vehiculo->placa, placa)) return q;
			vehiculo = vehiculo->vehiculoProx;
		}
		q = q->personaProx;
	} return NULL;
}

struct vehiculo *buscarPlaca(struct persona *q, char placa[8]){ //Retorna NULL si no consigue la placa.			   	   //sino, retorna el apuntador de esa placa
	while(q){
		struct vehiculo *vehiculo = q->datosVehiculo;
		while(vehiculo){
			if (!strcmp(vehiculo->placa, placa)) return vehiculo;
			vehiculo = vehiculo->vehiculoProx;
		}
		q = q->personaProx;
	} return NULL;
}

struct vehiculo *buscarPlaca2(struct persona *q, char placa[8]){ //Retorna NULL si no consigue la placa.			   	   //sino, retorna el apuntador de esa placa
	struct vehiculo *vehiculo = q->datosVehiculo;
	while(vehiculo){
		if (!strcmp(placa,vehiculo->placa)) return vehiculo;
		vehiculo=vehiculo->vehiculoProx;
	} return NULL;
}
	
struct persona * buscarCedula(struct persona *r, int cedula){ //Retorna NULL si no consigue la cedula.		  //sino, retorna el apuntador de esa placa
	while(r){
		if(r->cedula == cedula) return r;
		r = r->personaProx;
	} return NULL;
}

struct persona * buscarInfraccionPersona(int numero){
	struct persona *h = p; 
	struct vehiculo *v;
	struct infraccion *f;
	while(h){                      //Mientras todabia hayan personas en el sistema
		v = h->datosVehiculo;
		while (v){                 //Mientras la persona del apuntador tenga vehiculos registrados
			f = v->datosInfraccion;
			while(f){              //Se comparara la lista de infracciones de cada vehiculo
				if (f->numero == numero) return h;
				f = f->infraccionProx;
			}
			v = v->vehiculoProx;
		}
		h = h->personaProx;
	}return NULL;
}

struct vehiculo * buscarInfraccionVehiculo(int numero){
	struct persona *h = p; 
	struct vehiculo *v;
	struct infraccion *f;
	while(h){                      //Mientras todabia hayan personas en el sistema
		v = h->datosVehiculo;
		while (v){                 //Mientras la persona del apuntador tenga vehiculos registrados
			f = v->datosInfraccion;
			while(f){              //Se comparara la lista de infracciones de cada vehiculo
				if (f->numero == numero) return v;
				f = f->infraccionProx;
			}
			v = v->vehiculoProx;
		}
		h = h->personaProx;
	}return NULL;
}

struct infraccion * buscarInfraccion(int numero){
	struct persona *h = p; 
	struct vehiculo *v;
	struct infraccion *f;
	while(h){                      //Mientras todabia hayan personas en el sistema
		v = h->datosVehiculo;
		while (v){                 //Mientras la persona del apuntador tenga vehiculos registrados
			f = v->datosInfraccion;
			while(f){              //Se comparara la lista de infracciones de cada vehiculo
				if (f->numero == numero) return f;
				f = f->infraccionProx;
			}
			v = v->vehiculoProx;
		}
		h = h->personaProx;
	}return NULL;
}

void consultarInfraccion(struct persona *f){
	system("cls");
	freeBuffer();
	int numero;
	if(!f){
		printf("\n\n\t\tLa base de datos esta vacia. Agregue una persona al sistema primero\n\n");
		system("pause");
		return;
	}	
	struct infraccion *aux = NULL;
	while(!aux){
		system("cls");
		printf("\n\n\t\t\tIngrese el numero de infraccion que desea buscar");
		printf("\n\n\t\t\t(0) Para salir \n\n\t\t\t\t\t");
		scanf("%i",&numero);
		if (numero==0) return;
		aux = buscarInfraccion(numero);
		if(!aux){
			system("cls");
			printf("\n\n\t\t\t   LA INFRACCION NO ESTA REGISTRADA EN EL SISTEMA\n\n");
			system("pause");
		}
	}
	struct vehiculo *v = buscarInfraccionVehiculo(numero);
	f = buscarInfraccionPersona(numero);
	printf("\n\n\t\t\t\tSE ENCONTRARON LOS SIGUIENTES DATOS\n");
	printf("\n\n\t\t      Datos del propietario:");
	printf("\n\n\t\t\t      - Nombre y apellidos: %s %s",f->nombre, f->apellidos);
	printf("\n\n\t\t\t      - Cedula: %i",f->cedula);
	printf("\n\n\t\t      Datos del vehiculo: ");
	printf("\n\n\t\t\t      - Placa del vehiculo: %s",v->placa);
	printf("\n\n\t\t\t      - Marca: %s",v->marca);
	printf("\n\n\t\t\t      - Modelo: %s",v->modelo);
	printf("\n\n\t\t      Datos de la infraccion: ");
	printf("\n\n\t\t\t      - Numero de infraccion: %i",aux->numero);
	printf("\n\n\t\t\t      - Tipo de infraccion: %s",aux->tipo);
	printf("\n\n\t\t\t      - Fecha de infraccion: %i/%i/%i",aux->fechaInfraccion.dd,aux->fechaInfraccion.mm,aux->fechaInfraccion.yy);
	printf("\n\n\t\t\t      - Monto de infraccion: %i",aux->monto);
	printf("\n\n\t\t\t      - Estado de infraccion PAGADO: %s\n\n",aux->pagado);
	system("pause");
	system("cls");
}

void consultarVehiculoPlaca(struct persona *r){
	system("cls");
	freeBuffer();
	char placa[10];
	if(!r){
		printf("\n\n\t\tLa base de datos esta vacia. Agregue una persona al sistema primero\n\n");
		system("pause");
		return;
	}	
	struct vehiculo *aux = NULL;
	while(!aux){
		system("cls");
		printf("\n\n\t\t\tIngrese la placa del vehiculo que desea buscar");
		printf("\n\n\t\t\t(0) Para salir \n\n\t\t\t\t\t");
		gets(placa);
		if (!strcmp(placa,"0")) return;
		strcpy(placa, strupr(placa));
		aux = buscarPlaca(r, placa);
		if(!aux){
			system("cls");
			printf("\n\n\t\t\t\tLA PLACA NO ESTA REGISTRADA EN EL SISTEMA\n\n");
			system("pause");
		}
	}
	r = buscarTitularVehiculo(r, placa);
	printf("\n\n\t\t\t\tSE ENCONTRARON LOS SIGUIENTES DATOS\n");
	printf("\n\n\t\tDatos del propietario");
	printf("\n\n\t\t\t- Nombre y apellidos: %s %s",r->nombre, r->apellidos);
	printf("\n\n\t\t\t- Cedula: %i",r->cedula);
	printf("\n\n\t\tDatos del vehiculo");
	printf("\n\n\t\t\t- Placa: %s",aux->placa);
	printf("\n\n\t\t\t- Marca: %s",aux->marca);
	printf("\n\n\t\t\t- Modelo: %s",aux->modelo);
	printf("\n\n\t\t\t- A%co: %i",164,aux->annio.yy);
	printf("\n\n\t\t\t- Color: %s\n\n",aux->color);
	system("pause");
	system("cls");
}

void consultarVehiculoCedula(struct persona *r){
	system("cls");
	freeBuffer();
	int cedula;
	if(!r){
		printf("\n\n\t\tLa base de datos esta vacia. Agregue una persona al sistema primero\n\n");
		system("pause");
		return;
	}	
	struct persona *auxPersona = NULL;
	while(!auxPersona){
		system("cls");
		printf("\n\n\t\t\tIngrese la cedula del propietario del vehiculo que desea buscar");
		printf("\n\n\t\t\t(0) Para salir \n\n\t\t\t\t\t");
		scanf("%i",&cedula);
		if (!cedula) return;
		auxPersona = buscarCedula(r, cedula);
		if(!auxPersona){
			system("cls");
			printf("\n\n\t\t\t\tLA CEDULA NO ESTA REGISTRADA EN EL SISTEMA\n\n");
			system("pause");
		}
	}
	struct vehiculo *auxVehiculo = auxPersona->datosVehiculo;
	printf("\n\n\t\t\t\tSE ENCONTRARON LOS SIGUIENTES DATOS\n");
	printf("\n\t\t\t\tPROPIETARIO: %s %s",auxPersona->nombre,auxPersona->apellidos);
	printf("\n\t\t\t\tCEDULA: %i",auxPersona->cedula);
	if(!auxVehiculo){
	printf("\n\n\t\t\t     ESTE USUARIO NO TIENE VEHICULOS AGREGADOS\n\n");
	system("pause");
	}
	for (int cont = 1; auxVehiculo; cont++){
		printf("\n\n\t\t\t\tVehiculo %i",cont);
		printf("\n\n\t\t\t- Placa: %s",auxVehiculo->placa);
		printf("\n\n\t\t\t- Marca: %s",auxVehiculo->marca);
		printf("\n\n\t\t\t- Modelo: %s",auxVehiculo->modelo);
		printf("\n\n\t\t\t- A%co: %i",164,auxVehiculo->annio.yy);
		printf("\n\n\t\t\t- Color: %s\n\n\t\t\t",auxVehiculo->color);
		system("pause");
		auxVehiculo = auxVehiculo->vehiculoProx;
	}
}

void buscarPersonaNombre(struct persona *p, char name[100]){
	char aux[100];
	if (p){
		strcpy(aux,p->nombre);
		strcat(aux, " ");
		strcat(aux,p->apellidos);
		if(!strcmp(name, p->nombre)||!strcmp(name, p->apellidos)||!strcmp(name, aux)){
			printf("\n\n\t\t\t- Nombre: %s",p->nombre);
			printf("\n\n\t\t\t- Apellidos: %s",p->apellidos);
			printf("\n\n\t\t\t- Cedula: %i",p->cedula);
			printf("\n\n\t\t\t- Fecha de nacimiento: %i/%i/%i",p->fechaNacimiento.dd,p->fechaNacimiento.mm,p->fechaNacimiento.yy);
			printf("\n\n\t\t\t- Lugar de nacimiento: %s",p->place.ciudad);
			printf("\n\n\t\t\t- Direccion actual de residencia: %s\n\n",p->place.direccion);
			system("pause");
		}
		buscarPersonaNombre(p->personaProx, name);
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
	printf("\n\n\t\t\tIngrese el nombre, apellido o nombre completo de la persona que desea buscar");
	printf("\n\t\t\tDebe ser el mismo que se ingreso en el sistema (No importan las mayusculas)\n\n\t\t\t\t\t");
	gets(nombre);
	strcpy(nombre,strupr(nombre));
	printf("\n\n\t\t\t\tSE ENCONTRARON LOS SIGUIENTES DATOS\n");
	buscarPersonaNombre(p, nombre);
	printf("\n\n\t\t\t\t    NO SE ENCONTRARON MAS DATOS\n\n");
	system("pause");
	system("cls");
	printf("termino");
}

void consultarPersonaCedula(int cedula){
	system("cls");
	freeBuffer();
	if(!p){
		printf("\n\n\t\tLa base de datos esta vacia. Agregue una persona al sistema primero\n\n");
		system("pause");
		return;
	}	
	struct persona *aux = buscarCedula(p,cedula);
	while(!aux){
		system("cls");
		printf("\n\n\t\t\tIngrese la cedula de la persona que desea buscar");
		printf("\n\n\t\t\t(0) Para salir \n\n\t\t\t\t\t");
		scanf("%i",&cedula);
		if (cedula==0) return;
		aux = buscarCedula(p, cedula);
		if(!aux){
			system("cls");
			printf("\n\n\t\t\t\tLA CEDULA NO ESTA REGISTRADA EN EL SISTEMA\n\n");
			system("pause");
		}
	}
	printf("\n\tDatos del titular:");
	printf("\n\n\t\t\t- Nombre: %s",aux->nombre);
	printf("\n\n\t\t\t- Apellidos: %s",aux->apellidos);
	printf("\n\n\t\t\t- Cedula: %i",aux->cedula);
	printf("\n\n\t\t\t- Fecha de nacimiento: %i/%i/%i",aux->fechaNacimiento.dd,aux->fechaNacimiento.mm,aux->fechaNacimiento.yy);
	printf("\n\n\t\t\t- Lugar de nacimiento: %s",aux->place.ciudad);
	printf("\n\n\t\t\t- Direccion actual de residencia: %s\n",aux->place.direccion);
}

////////////////////////////////////////////////////////FUNCIONES CONSULTA/BUSCAR//////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////FUNCIONES VALIDAR///////////////////////////////////////////////////////////////
void validarDia(struct persona **t){
	while((*t)->fechaNacimiento.dd>31||((*t)->fechaNacimiento.dd<=0)){ //**********VALIDACION DE DIA DE NACIMIENTO************************
		system("cls");
		printf("\n\n\t\t\t\tIngrese un valor valido (1-31)\n\n");
		system("pause");
		system("cls");
		printf("\n\t\t\t- Nombre: %s",(*t)->nombre);
		printf("\n\n\t\t\t- Apellidos: %s",(*t)->apellidos);
		printf("\n\n\t\t\t- Cedula: %i \n",(*t)->cedula);	
		printf("\n\n\t\t\tIngrese el dia (dd) de nacimiento: ");
		scanf("%i",&(*t)->fechaNacimiento.dd);
	}
}

void validarMes(struct persona **t){
	while(((*t)->fechaNacimiento.mm>12)||((*t)->fechaNacimiento.mm<=0)){ //**********VALIDACION DEL MES DE NACIMIENTO************************
		system("cls");
		printf("\n\n\t\t\t\tIngrese un valor valido (1-12)\n\n");
		system("pause");
		system("cls");
		printf("\n\t\t\t- Nombre: %s",(*t)->nombre);
		printf("\n\n\t\t\t- Apellidos: %s",(*t)->apellidos);
		printf("\n\n\t\t\t- Cedula: %i",(*t)->cedula);	
		printf("\n\n\t\t\t- Dia (dd) de nacimiento: %i \n",(*t)->fechaNacimiento.dd);
		printf("\n\n\t\t\tIngrese el mes (mm) de nacimiento: ");
		scanf("%i",&(*t)->fechaNacimiento.mm);
	}
}

void validarAnnio(struct persona **t){
	while(((*t)->fechaNacimiento.yy>2020)||((*t)->fechaNacimiento.yy<1)){ //**********VALIDACION DEL AÃ‘O DE NACIMIENTO************************
		system("cls");
		printf("\n\n\t\t\t\tIngrese un valor valido (desde 1 hasta 2020)\n\n");
		system("pause");
		system("cls");
		printf("\n\t\t\t- Nombre: %s",(*t)->nombre);
		printf("\n\n\t\t\t- Apellidos: %s",(*t)->apellidos);
		printf("\n\n\t\t\t- Cedula: %li",(*t)->cedula);	
		printf("\n\n\t\t\t- Dia (dd) de nacimiento: %i",(*t)->fechaNacimiento.dd);
		printf("\n\n\t\t\t- Mes (mm) de nacimiento: %i \n",(*t)->fechaNacimiento.mm);
		printf("\n\n\t\t\tIngrese el a%co (yyyy) de nacimiento: ",164);
		scanf("%i",&(*t)->fechaNacimiento.yy);
	}
}

void validarAnnioV(struct vehiculo **x){                             //**********VALIDACION DEL AÃ‘O DEL MODELO VEHICULO************************
	while(((*x)->annio.yy>2020)||((*x)->annio.yy<1)){               
		system("cls");
		printf("\n\n\t\t\t\tIngrese un valor valido (desde 1 hasta 2020)\n\n");
		system("pause");
		system("cls");
		printf("\n\n\t\t\t- Placa: %s",(*x)->placa);
		printf("\n\n\t\t\t- Marca del vehiculo: %s",(*x)->marca);
		printf("\n\n\t\t\t- Modelo del vehiculo: %s \n",(*x)->modelo);
		printf("\n\t\t\tIngrese el a%co (yyyy): ",164); 
		scanf("%i",&(*x)->annio.yy);
	}
}

///////////////////////////////////////////////////////////FUNCIONES VALIDAR///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////FUNCIONES ELIMINAR///////////////////////////////////////////////////////////////

void eliminarInfraccion(struct vehiculo **v, struct infraccion **f, int numeroInfraccion){  //FUNCION PARA ELIMINAR UNA INFRACCION DEL VEHICULO
	struct infraccion *aux = *f;                  
	struct infraccion *auxAn= *f;
	while(aux){                                    //Mientras la lista de infracciones exista
	
		if(aux->numero == numeroInfraccion){       //Si encuentro la infraccion con ese numero 
			if(aux == auxAn){                      //Si los dos apuntadores estan al principio de la lista
				*f=(*f)->infraccionProx;           //Muevo el apuntador cabeza
				(*v)->datosInfraccion = *f;        //Enlazo el vehiculo con el resto de las infracciones
	
			} else auxAn->infraccionProx=aux->infraccionProx;
				
			free(aux);                              //Libero memoria
			return;                                 //Me salgo de la funcion
		}
		auxAn=aux;
		aux = aux->infraccionProx;
	}
}

void eliminarVehiculo(struct persona **p, struct vehiculo **v, char placa[8]){ //FUNCION PARA ELIMINAR UN VEHICULO DE LA PERSONA
	struct vehiculo *aux = *v;
	struct vehiculo *auxAn= *v;
	while(aux){                                 //Mientras la lista de vehiculos exista
		if(!strcmp(aux->placa, placa)){         //Si conseguimos el vehiculo con la placa
			if(aux == auxAn){                   //si los dos apuntadores apuntan a la cabeza de la lista de vehiculos
			
				*v=(*v)->vehiculoProx;          //Muevo el apuntador cabeza al proximo
				(*p)->datosVehiculo = *v;       //Hago el enlazamiento de la lista de persona al nuevo puntero cabeza
				
			} else auxAn->vehiculoProx=aux->vehiculoProx; //Si no estan al comienzo, enlazo el anterior con el proximo de aux
			
//Le paso el apuntador vehiculo, la lista de infracciones y el numero de infraccion que se quiere borrar, siempre sera el primero en este caso
			while(aux->datosInfraccion) eliminarInfraccion(&aux, &aux->datosInfraccion, aux->datosInfraccion->numero); //Elimino todas las infracciones

			free(aux);  //Libero memoria
			return;
		}
		auxAn=aux;
		aux = aux->vehiculoProx;
	}
}

void eliminarPersona(struct persona **p, int cedula){  //FUNCION PARA ELIMINAR A UNA PERSONA DEL SISTEMA
	struct persona *aux = *p;
	struct persona *auxAn= *p;
	while(aux){                                 //Mientras la lista de personas exista
		if(aux->cedula == cedula){         //Si la persona con esa cedula
			if(aux == auxAn){                   //si los dos apuntadores apuntan a la cabeza de la lista de personas
			
				*p=(*p)->personaProx;          //Muevo el apuntador cabeza al proximo
				
			} else auxAn->personaProx=aux->personaProx; //Si no estan al comienzo, enlazo el anterior con el proximo de aux
			
//Le paso el apuntador persona, la lista de vehiculos y la placa que se quiere borrar, siempre sera el primero en este caso
			while(aux->datosVehiculo) eliminarVehiculo(&aux, &aux->datosVehiculo, aux->datosVehiculo->placa); //Elimino todos los vehiculos

			free(aux); //Libero memoria
			return;
		}
		auxAn=aux;
		aux = aux->personaProx;
	}
}

void llamadaEliminarPersona(){ //FUNCION PARA VERIFICAR ANTES DE ELIMINAR A UNA PERSONA DEL SISTEMA
	system("cls");
	freeBuffer();
	char resp[2];
	int cedula,respuesta=0;
	if(!p){
		printf("\n\n\t\tLa base de datos esta vacia. Agregue una persona al sistema primero\n\n");
		system("pause");
		return;
	}	
	struct persona *aux = NULL;
	while((!aux)||(respuesta==0)){
		system("cls");
		printf("\n\n\t\t\tIngrese la cedula de la persona que desea eliminar");
		printf("\n\n\t\t\t(0) Para salir \n\n\t\t\t\t\t");
		scanf("%i",&cedula);
		if (cedula==0) return;
		aux = buscarCedula(p, cedula);
		if(!aux){
			system("cls");
			printf("\n\n\t\t\t\tLA CEDULA NO ESTA REGISTRADA EN EL SISTEMA\n\n");
			system("pause");
		}else{
			printf("\n\n\t\t\tDesea eliminar los datos de esta persona? (SI-NO): \n\t\t\t");
			printf("\n\n\t\t\t- Nombre: %s   Apellido: %s",aux->nombre,aux->apellidos);
			printf("\n\t\t\t- Cedula: %i\n\n\t\t\t\t\t\t",cedula);
			scanf("%s",&resp);
			strcpy(resp,strupr(resp));
			while ((strcmp(resp,"SI")!=0)&&(strcmp(resp,"NO")!=0)){   //******************VALIDACION SI O NO********************
				printf("\n\n\t\t\t\tLa respuesta introducida no es valida\n\n");
				printf("\n\n\t\t\t\tSolo se permiten las siguientes respuestas: 'SI' o 'NO'\n\n");
				system("pause");
				system("cls");
				printf("\n\n\t\t\tDesea eliminar los datos de la persona? (SI-NO): "); 
				scanf("%s",&resp);
				strcpy(resp,strupr(resp));
			}
			if (strcmp(resp,"SI")==0) respuesta=1;
			if (strcmp(resp,"NO")==0) respuesta=2;
		}
	}
	if (respuesta=1){
		eliminarPersona(&p, cedula);
		guardarData(p);
		printf("\n\n\t\t\t\t\tSe ha eliminado con exito\n\n");
	}
	system("pause");
}

void llamadaEliminarVehiculo(){ //FUNCION PARA VERIFICAR ANTES DE ELIMINAR UN VEHICULO
	system("cls");
	freeBuffer();
	int respuesta=0;
	char placa[8], resp[2];
	if(!p){
		printf("\n\n\t\tLa base de datos esta vacia. Agregue una persona al sistema primero\n\n");
		system("pause");
		return;
	}	
	struct persona *persona = NULL;
	struct vehiculo *vehiculo = NULL;
	while((!vehiculo)||(respuesta==0)){
		system("cls");
		printf("\n\n\t\t\tIngrese la placa de la persona que desea eliminar");
		printf("\n\n\t\t\t(0) Para salir \n\n\t\t\t\t\t");
		gets(placa);
		strcpy(placa,strupr(placa));
		if (!strcmp(placa,"0")) return;
		vehiculo = buscarPlaca(p, placa);
		if(!vehiculo){
			system("cls");
			printf("\n\n\t\t\t\tLA PLACA NO ESTA REGISTRADA EN EL SISTEMA\n\n");
			system("pause");
		}else{
			persona = buscarTitularVehiculo(p, placa);
			printf("\n\n\t\t\tDesea eliminar este vehiculo del sistema?\n\t\t\tIngrese 1 si desea hacerlo");
			printf("\n\n\t\t\tDatos del propietario");
			printf("\n\n\t\t\t - Nombre y apellidos: %s %s",persona->nombre,persona->apellidos);
			printf("\n\n\t\t\t - Cedula: %i",persona->cedula);
			printf("\n\n\t\t\tDatos del vehiculo");
			printf("\n\n\t\t\t  - Placa: %s",vehiculo->placa);
			printf("\n\n\t\t\t  - Marca: %s",vehiculo->marca);
			printf("\n\n\t\t\t  - Modelo: %s",vehiculo->modelo);
			printf("\n\n\t\t\t  - Color: %s",vehiculo->color);
			printf("\n\n\t\t\t  - A%co: %i\n\n\t\t\t\t\t\t",164,vehiculo->annio.yy);
			scanf("%s",&resp);
			strcpy(resp,strupr(resp));
			while ((strcmp(resp,"SI")!=0)&&(strcmp(resp,"NO")!=0)){   //******************VALIDACION SI O NO********************
				printf("\n\n\t\t\t\tLa respuesta introducida no es valida\n\n");
				printf("\n\n\t\t\t\tSolo se permiten las siguientes respuestas: 'SI' o 'NO'\n\n");
				system("pause");
				system("cls");
				printf("\n\n\t\t\tDesea eliminar el vehiculo del sistema? (SI-NO): "); 
				scanf("%s",&resp);
				strcpy(resp,strupr(resp));
			}
			if (strcmp(resp,"SI")==0) respuesta=1;
			if (strcmp(resp,"NO")==0) respuesta=2;
		}
	}
	if (respuesta=1){
		eliminarVehiculo(&persona, &persona->datosVehiculo,vehiculo->placa);
		guardarData(p);
		printf("\n\n\t\t\t\t\tSe ha eliminado con exito\n\n");
	}
	system("pause");
}

void llamadaEliminarInfraccion(){ //FUNCION PARA VERIFICAR ANTES DE ELIMINAR UNA INFRACCION A UN VEHICULO
	system("cls");
	freeBuffer();
	char resp[2];
	int numero,respuesta=0;
	if(!p){
		printf("\n\n\t\tLa base de datos esta vacia. Agregue una persona al sistema primero\n\n");
		system("pause");
		return;
	}	
	struct persona *persona = NULL;
	struct vehiculo *vehiculo = NULL;
	struct infraccion * infraccion = NULL;
	while((!infraccion)||(respuesta==0)){
		system("cls");
		printf("\n\n\t\t\tIngrese el numero de infraccion que desea eliminar");
		printf("\n\n\t\t\t(0) Para salir \n\n\t\t\t\t\t");
		scanf("%i",&numero);
		if (numero == 0) return;
		infraccion = buscarInfraccion(numero);
		if(!infraccion){
			system("cls");
			printf("\n\n\t\t\t\tLA PLACA NO ESTA REGISTRADA EN EL SISTEMA\n\n");
			system("pause");
		}else{
			persona = buscarInfraccionPersona(numero);
			vehiculo = buscarInfraccionVehiculo(numero);
			printf("\n\n\t\t\tDesea eliminar esta infraccion del sistema?\n\t\t\tIngrese 1 si desea hacerlo");
			printf("\n\n\t\t\tDatos del propietario");
			printf("\n\n\t\t\t - Nombre y apellidos: %s %s",persona->nombre,persona->apellidos);
			printf("\n\n\t\t\t - Cedula: %i Placa del vehiculo: %s",persona->cedula,vehiculo->placa);
			printf("\n\n\t\t\tDatos del vehiculo");
			printf("\n\n\t\t\t - Marca: %s Modelo: %s",vehiculo->marca,vehiculo->modelo);
			printf("\n\n\t\t\tDatos de la infraccion");
			printf("\n\n\t\t\t - Numero Infraccion: %i",infraccion->numero);
			printf("\n\n\t\t\t - Tipo de infraccion: %s",infraccion->tipo);
			printf("\n\n\t\t\t - Fecha de infraccion: %i/%i/%i",infraccion->fechaInfraccion.dd,infraccion->fechaInfraccion.mm,infraccion->fechaInfraccion.yy);
			printf("\n\n\t\t\t - Pagado: %s\n\n\t\t\t\t\t",infraccion->pagado);
			scanf("%s",&resp);
			strcpy(resp,strupr(resp));
			while ((strcmp(resp,"SI")!=0)&&(strcmp(resp,"NO")!=0)){   //******************VALIDACION SI O NO********************
				printf("\n\n\t\t\t\tLa respuesta introducida no es valida\n\n");
				printf("\n\n\t\t\t\tSolo se permiten las siguientes respuestas: 'SI' o 'NO'\n\n");
				system("pause");
				system("cls");
				printf("\n\n\t\t\tDesea eliminar el vehiculo del sistema? (SI-NO): "); 
				scanf("%s",&resp);
				strcpy(resp,strupr(resp));
			}
			if (strcmp(resp,"SI")==0) respuesta=1;
			if (strcmp(resp,"NO")==0) respuesta=2;
		}
	}
	if (respuesta=1){
		eliminarInfraccion(&vehiculo, &vehiculo->datosInfraccion,numero);
		guardarData(p);
		printf("\n\n\t\t\t\t\tSe ha eliminado con exito\n\n");
	}
	system("pause");
}
///////////////////////////////////////////////////////////FUNCIONES ELIMINAR///////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////CONSULTAS DE ENUNCIADOS/////////////////////////////////////////////////////////////

void funcionDosDosUno (struct persona *p){                                 //FUNCION PARA LA OPCION 2.2.1 DEL MENU
	int j=0,i=1,cedula, deuda=0;
	struct persona *persona=NULL;
	if (!p){
		printf("\n\n\t\tLa base de datos esta vacia. Agregue una persona al sistema primero\n\n");
		system("pause");
		return;
	}	
	while (!persona){
		printf("\n\n\t\t\tIngrese el numero de cedula que desea buscar");
		printf("\n\n\t\t\t(0) Salir\n\n\t\t\t\t");
		scanf("%i",&cedula);
		if(!cedula)return;
		persona=buscarCedula(p,cedula);
		if (!persona){
			system("cls");
			printf("\n\n\t\t\t\tLA CEDULA NO ESTA REGISTRADA EN EL SISTEMA\n\n");
			system("pause");
		}
	}
	consultarPersonaCedula(cedula);
	struct vehiculo *vehiculos=persona->datosVehiculo;
	struct infraccion *infraccion;
	printf("\n\t   Vehiculos:\n");
	for (i=1; vehiculos; i++){
		printf("\n\t\tVehiculo %i\n",i);
		printf("\n\t\tPlaca: %s",vehiculos->placa);
		printf("\n\t\tMarca: %s",vehiculos->marca);
		printf("\n\t\tModelo: %s",vehiculos->modelo);
		printf("\n\t\tA%co: %i\n",164,vehiculos->annio.yy);
		infraccion=vehiculos->datosInfraccion;
		while(infraccion){
			if (!strcmp(infraccion->pagado,"NO")){
				deuda+=infraccion->monto;
				j++;
			}
			infraccion = infraccion->infraccionProx;
		} vehiculos=vehiculos->vehiculoProx;
	}
	i--;
	if (!i) printf("\n\n\t\t\t\tNO POSEE VEHICULOS");
	else printf("\n\n\t\tPosee un total de %i vehiculos",i);
	
	if (deuda) printf("\n\t\tPosee una deuda de %i Bs con %i infracciones sin pagar",deuda,j);
	else printf("\n\n\t\t\t\tNo posee deuda (sin infraccion sin pagar)");
	printf("\n");
	system("pause");
}

void funcionDosDosDos(struct persona *p){                                 //FUNCION PARA LA OPCION 2.2.2 DEL MENU
	int i,cedula, deuda=0, pagado=0;
	struct persona *persona=NULL;
	struct vehiculo *vehiculos;
	struct infraccion *infracciones;
	if (!p){
		printf("\n\n\t\tLa base de datos esta vacia. Agregue una persona al sistema primero\n\n");
		system("pause");
		return;
	}	
	while (!persona){
		printf("\n\n\t\t\tIngrese el numero de cedula que desea buscar");
		printf("\n\n\t\t\t(0) Salir\n\n\t\t\t\t");
		scanf("%i",&cedula);
		if (!cedula)return;
		persona=buscarCedula(p,cedula);
		if (!persona){
			system("cls");
			printf("\n\n\t\t\t\tLA CEDULA NO ESTA REGISTRADA EN EL SISTEMA\n\n");
			system("pause");
		}
	}
	printf("\n\tTitular:");
	printf("\n\n\t\t\t- Nombre: %s",persona->nombre);
	printf("\n\n\t\t\t- Apellidos: %s",persona->apellidos);
	printf("\n\n\t\t\t- Cedula: %i",persona->cedula);
	
	vehiculos=persona->datosVehiculo;
	printf("\n\t   Vehiculos:\n");
	for (i=1; vehiculos; i++){
		printf("\n\t\tVehiculo %i\n",i);
		printf("\n\t\tPlaca: %s",vehiculos->placa);
		printf("\n\t\tMarca: %s",vehiculos->marca);
		printf("\n\t\tModelo: %s",vehiculos->modelo);
		printf("\n\t\tA%co: %i",164,vehiculos->annio.yy);
		deuda=0; pagado=0;
		infracciones = vehiculos->datosInfraccion;
		while(infracciones){
			if (!strcmp(infracciones->pagado,"NO")) deuda+=infracciones->monto;
			else pagado+=infracciones->monto;
			infracciones= infracciones->infraccionProx;
		}
		printf("\n\n\t\t -Debe: %i",deuda);
		printf("\n\t\t -Pagado: %i\n",pagado); 
		vehiculos=vehiculos->vehiculoProx;
	}
	system("pause");
}

void funcionDosDosTres(struct persona *p){                                 //FUNCION PARA LA OPCION 2.2.3 DEL MENU
	int cedula, deuda=0;
	struct persona *persona=NULL;
	struct infraccion *infraccion;
	struct vehiculo *vehiculos;
	if (!p){
		printf("\n\n\t\tLa base de datos esta vacia. Agregue una persona al sistema primero\n\n");
		system("pause");
		return;
	}	
	while (!persona){
		printf("\n\n\t\t\tIngrese el numero de cedula que desea buscar");
		printf("\n\n\t\t\t(0) Salir\n\n\t\t\t\t");
		scanf("%i",&cedula);
		if(!cedula)return;
		persona=buscarCedula(p,cedula);
		if (!persona){
			system("cls");
			printf("\n\n\t\t\t\tLA CEDULA NO ESTA REGISTRADA EN EL SISTEMA\n\n");
			system("pause");
		}
	}
	printf("\n\t\tTitular: %s %s",persona->nombre, persona->apellidos);
	
	vehiculos = persona->datosVehiculo;
	ordenarBurbujaPlaca(&vehiculos);
	printf("\n\n\t\tMultas sin pagar:");
	while (vehiculos){
		printf("\n\n\n\t\tVehiculo %s",vehiculos->placa);
		
		infraccion = vehiculos->datosInfraccion;
		for(int i=1; infraccion ; i++){
			
			if (!strcmp(infraccion->pagado,"NO")) {
				printf("\n\n\t\t   Infraccion %i\n",i);
				printf("\n\t\t   Fecha: %i/%i/%i",infraccion->fechaInfraccion.dd,infraccion->fechaInfraccion.mm,infraccion->fechaInfraccion.yy);
				printf("\n\t\t   Numero: %i",infraccion->numero);
				printf("\n\t\t   Tipo: %s",infraccion->tipo);
				printf("\n\t\t   Monto: %i",infraccion->monto);
				printf("\n\t\t   Pagada: %s",infraccion->pagado);
				deuda+=vehiculos->datosInfraccion->monto;
			}
			
			infraccion = infraccion->infraccionProx;
		}
		
		vehiculos=vehiculos->vehiculoProx;
	}	
		printf("\n\n\n\t\tEl propietario %s debe un total de: %i Bs\n",persona->nombre,deuda);
		system("pause");
}

void funcionDosDosCuatro(struct persona *p){ //FUNCION DE LA OPCION 2.2.4 DEL MENU
	int cedula;
	char placa[8];
	struct persona *persona=NULL;
	struct infraccion *infraccion;
	struct vehiculo *vehiculo=NULL;
	freeBuffer();
	if (!p){
		printf("\n\n\t\tLa base de datos esta vacia. Agregue una persona al sistema primero\n\n");
		system("pause");
		return;
	}	
	while (!persona){
		printf("\n\n\t\t\tIngrese el numero de cedula que desea buscar");
		printf("\n\n\t\t\t(0) Salir\n\n\t\t\t\t");
		scanf("%i",&cedula);
		if(!cedula)return;
		persona=buscarCedula(p,cedula);
		if (!persona){
			system("cls");
			printf("\n\n\t\t\t\tLA CEDULA NO ESTA REGISTRADA EN EL SISTEMA\n\n");
			system("pause");
		}
	}
	
	freeBuffer();
	while (!vehiculo){
		system("cls");
		printf("\n\t\t\t\t\t   Titular: %s %s\n\n",persona->nombre, persona->apellidos);
		printf("\n\n\t\t\tIngrese la placa que desea buscar");
		printf("\n\n\t\t\t(0) Salir\n\n\t\t\t\t");
		gets(placa);
		strcpy(placa,strupr(placa));
		if (!strcmp(placa,"0")) return;
		vehiculo=buscarPlaca2(persona, placa);
		if (!vehiculo){
			system("cls");
			printf("\n\n\t\t\t\tLA PLACA NO ESTA REGISTRADA EN EL SISTEMA\n\n");
			system("pause");
		}
	}
	system("cls");
	infraccion = vehiculo->datosInfraccion;
	printf("\n\t\t\t\t\t  Titular: %s %s\n\n",persona->nombre, persona->apellidos);
	printf("\n\n\t\t\t\t\t     Vehiculo %s\n\n",placa);
	if(!infraccion)printf("\n\n\t\tNO POSEE INFRACCIONES\n\n");
	else{
		if(infraccion) ordenarBurbujaIFecha(&infraccion);//ordenar por fecha de infraccion
		printf("\n\n\t\t\t\t\t     MULTAS NO PAGADAS");
		for (int i = 1; infraccion; i++) {
			if(!strcmp(infraccion->pagado,"NO")){
				printf("\n\n\t\t\t\t Infraccion %i",i);
				printf("\n\n\t\tNumero: %i",infraccion->numero);
				printf("\n\t\tTipo: %s",infraccion->tipo);
				printf("\n\t\tFecha: %i/%i/%i",infraccion->fechaInfraccion.dd,infraccion->fechaInfraccion.mm,infraccion->fechaInfraccion.yy);
				printf("\n\t\tMonto: %i",infraccion->monto);
				printf("\n\t\tPagado: %s",infraccion->pagado);
			}
			infraccion = infraccion->infraccionProx;
		}
		
		infraccion = vehiculo->datosInfraccion;
		if(infraccion) ordenarBurbujaIFecha(&infraccion);//ordenar por fecha de infraccion
		printf("\n\n\t\t\t\t\t      MULTAS PAGADAS");
		for (int i = 1; infraccion; i++) {
			if(!strcmp(infraccion->pagado,"SI")){
				printf("\n\n\t\t\t\t Infraccion %i",i);
				printf("\n\n\t\tNumero: %i",infraccion->numero);
				printf("\n\t\tTipo: %s",infraccion->tipo);
				printf("\n\t\tFecha: %i/%i/%i",infraccion->fechaInfraccion.dd,infraccion->fechaInfraccion.mm,infraccion->fechaInfraccion.yy);
				printf("\n\t\tMonto: %i",infraccion->monto);
				printf("\n\t\tPagado: %s",infraccion->pagado);
			}
			infraccion = infraccion->infraccionProx;
		}
	}
	printf("\n\n");
	system("pause");	
}

void funcionDosDosCinco(struct persona *p){ //FUNCION OPCION 2.2.5 DEL MENU
	int cedula;
	char tipo[40];
	struct persona *persona=NULL;
	struct infraccion *infraccion;
	struct vehiculo *vehiculo;
	freeBuffer();
	if (!p){
		printf("\n\n\t\tLa base de datos esta vacia. Agregue una persona al sistema primero\n\n");
		system("pause");
		return;
	}	
	while (!persona){
		printf("\n\n\t\t\tIngrese el numero de cedula que desea buscar");
		printf("\n\n\t\t\t(0) Salir\n\n\t\t\t\t");
		scanf("%i",&cedula);
		if(!cedula)return;
		persona=buscarCedula(p,cedula);
		if (!persona){
			system("cls");
			printf("\n\n\t\t\t\tLA CEDULA NO ESTA REGISTRADA EN EL SISTEMA\n\n");
			system("pause");
			system("cls");
		}
	}
	printf("\n\n\t\t\tTitular: %s %s\n\n",persona->nombre, persona->apellidos);
	freeBuffer();
	printf("\n\n\t\t\tIngrese el tipo de infraccion que desea buscar");
	printf("\n\n\t\t\t(0) Salir\n\n\t\t\t\t");
	gets(tipo);
	strcpy(tipo,strupr(tipo));
	if(!strcmp(tipo, "0")) return;
	vehiculo = persona->datosVehiculo;
	if(!vehiculo) {
		printf("\n\n\n\t\t\tEste usuario no posee vehiculos\n\n");
		system("pause");
		return;
	} cedula = 0; 
		while(vehiculo){
			infraccion=vehiculo->datosInfraccion;
			if(infraccion && infraccion->infraccionProx) ordenarBurbujaIFecha(&infraccion);//ordenar por fecha de infraccion
			while (infraccion){
				if ((strcmp(tipo,infraccion->tipo))==0) {
					cedula++;
					printf("\n\n\t\t\tDatos del vehiculo");
					printf("\n\n\t\t\t  - Placa: %s",vehiculo->placa);
					printf("\n\n\t\t\t  - Marca: %s",vehiculo->marca);
					printf("\n\n\t\t\t  - Modelo: %s",vehiculo->modelo);
					printf("\n\n\t\t\t  - Color: %s",vehiculo->color);
					printf("\n\n\t\t\t  - A%co: %i\n\n\t\t\t\t\t\t",164,vehiculo->annio.yy);
					printf("\n\n\t\t\tDatos de la infraccion");
					printf("\n\n\t\t\t - Numero Infraccion: %i",infraccion->numero);
					printf("\n\n\t\t\t - Tipo de infraccion: %s",infraccion->tipo);
					printf("\n\n\t\t\t - Fecha de infraccion: %i/%i/%i",infraccion->fechaInfraccion.dd,infraccion->fechaInfraccion.mm,infraccion->fechaInfraccion.yy);
					printf("\n\n\t\t\t - Pagado: %s\n\n\t\t\t\t\t",infraccion->pagado);
				}	
				infraccion=infraccion->infraccionProx;
			}
			vehiculo=vehiculo->vehiculoProx;
		}
		if(!cedula) printf("\n\n\t\tEste usuario no posee ninguna infraccion de este tipo en alguno de sus vehiculos\n\n");
	system("pause");
}

void funcionDosTres(struct persona *p){                                  //FUNCION PARA LA OPCION 2.3 DEL MENU
	int pagadas=0, impagadas=0;
	char placa[8];
	struct infraccion *infraccion;
	struct vehiculo *vehiculo=NULL;
	freeBuffer();
	if (!p){
		printf("\n\n\t\tLa base de datos esta vacia. Agregue una persona al sistema primero\n\n");
		system("pause");
		return;
	}	
	while (!vehiculo){
		system("cls");
		printf("\n\tIngrese la placa del vehiculo (Ya debe estar registrado en el sistema)");
		printf("\n\n\t\t\t(0) Salir\n\n\t\t\t\t");
		gets(placa);
		strcpy(placa,strupr(placa));
		if (!strcmp(placa,"0")) return;
		vehiculo=buscarPlaca(p, placa);
		if (!vehiculo){
			system("cls");
			printf("\n\n\t\t\t\tLA PLACA NO ESTA REGISTRADA EN EL SISTEMA\n\n");
			system("pause");
		}
	}
	system("cls");
	infraccion = vehiculo->datosInfraccion;
	printf("\n\n\t\tVehiculo %s\n",placa);
	if(!infraccion){
		printf("\n\n\t\tNO POSEE INFRACCIONES\n\n");
		system("pause");
		system("cls");
		return;
	}
	ordenarBurbujaNumeroMulta(&infraccion);
	for (int i = 1; infraccion; i++) {
		printf("\n\n\t\t\t\t Infraccion %i",i);
		printf("\n\n\t\tNumero: %i",infraccion->numero);
		printf("\n\t\tTipo: %s",infraccion->tipo);
		printf("\n\t\tFecha: %i/%i/%i",infraccion->fechaInfraccion.dd,infraccion->fechaInfraccion.mm,infraccion->fechaInfraccion.yy);
		printf("\n\t\tMonto: %i",infraccion->monto);
		printf("\n\t\tPagado: %s",infraccion->pagado);
		if (!strcmp(infraccion->pagado,"SI"))pagadas++;
		else impagadas++;
		infraccion = infraccion->infraccionProx;
	}
		printf("\n\n\t\tEl propietario tiene un total de %i infracciones pagadas",pagadas);
		printf("\n\n\t\tEl propietario tiene un total de %i infracciones sin pagar\n\n",impagadas);
		system("pause");
}

void funcionesDosCuatro(struct persona *q, int num){                                  //FUNCION PARA LAS OPCIONES 2.4.1 Y 2.4.2 DEL MENU
	int year1 = 0, year2 = 0, cont =0, monto=0;
	char tipo[25],pagado[2];
	struct persona *persona=q;
	struct infraccion *infraccion;
	struct vehiculo *vehiculos;
	if (!p){
		printf("\n\n\t\tLa base de datos esta vacia. Agregue una persona al sistema primero\n\n");
		system("pause");
		return;
	}
			
	printf("\n\n\t\tIngrese un primer a%co: ",164,year1);
	printf("\n\n\t\t\t(0) Salir\n\n\t\t\t\t");
	scanf("%i",&year1);	
	if(!year1) return;
	printf("\n\n\t\tIngrese un segundo a%co: ",164,year1);
	printf("\n\n\t\t\t(0) Salir\n\n\t\t\t\t");
	scanf("%i",&year2);
	if(!year1) return;
	freeBuffer();
	printf("\n\n\t\tIngrese el tipo de infraccion: ");
	printf("\n\n\t\t\t(0) Salir\n\n\t\t\t\t");
	gets(tipo);
	strcpy(tipo,strupr(tipo));
	if (!strcmp(tipo,"0"))return;
	ordenarPersonaCedula(&p, num);
	if (num)strcpy(pagado,"SI"); //Funcion 2.4.2
	else strcpy(pagado,"NO");    //Funcion 2.4.1
	system("cls");
	
	while(persona){
		vehiculos = persona->datosVehiculo;
		while(vehiculos){
			infraccion=vehiculos->datosInfraccion;
			//printf("\tPersona: %s\n",persona->nombre);
			while (infraccion){
				//printf("\t\tComparo:\n\t\t-%s-\n\t\t-%s-\n\n",infraccion->tipo,tipo);
				if(!strcmp(infraccion->tipo,tipo)&&!strcmp(infraccion->pagado,pagado)&&infraccion->fechaInfraccion.yy>=year1&&infraccion->fechaInfraccion.yy<=year2){
					cont++;
					printf("\n\n\t\tInfraccion %i",cont);
					printf("\n\n\t\tNombre y Apellido del propietario: %s %s",persona->nombre,persona->apellidos);
					printf("\n\t\tCedula del propietario: %i",persona->cedula);
					printf("\n\t\tPlaca del vehiculo: %s",vehiculos->placa);
					printf("\n\t\tMarca del vehiculo: %s",vehiculos->marca);
					printf("\n\t\tA%co del vehiculo: %i",164,vehiculos->annio.yy);
					printf("\n\t\tFecha de multa: %i/%i/%i",infraccion->fechaInfraccion.dd,infraccion->fechaInfraccion.mm,infraccion->fechaInfraccion.yy);
					printf("\n\t\tMonto: %i\n",infraccion->monto);
					monto+=infraccion->monto;
				}
				infraccion = infraccion->infraccionProx;
			}
			vehiculos= vehiculos->vehiculoProx;	
		}
		persona = persona->personaProx;
	}	
		if (!cont) printf("\n\n\t\tNo se encontraron infracciones con esos datos\n\n");
		if (num) strcpy(tipo,"un total de ingresos");
		else strcpy(tipo,"una deuda total");
		printf("\n\n\t\tEl sistema posee %s de %i Bs por este tipo de multa\n\n",tipo,monto);
		system("pause");
}

////////////////////////////////////////////////////////CONSULTAS DE ENUNCIADOS/////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////FUNCIONES MOSTRAR////////////////////////////////////////////////////////////////

void mostrarPersona(struct persona *persona){ //FUNCION PARA MOSTRAR A UNA PERSONA
	consultarPersonaCedula(persona->cedula);
	struct vehiculo *vehiculos=persona->datosVehiculo;
	mostrarVehiculos(&*vehiculos);
}

void mostrarVehiculos(struct vehiculo *vehiculos){  //FUNCION PARA MOSTRAR LOS VEHICULOS DE UNA PERSONA
	int i;
	if (!vehiculos) printf("\n\n\t\t\tEste propietario no posee vehiculos");
	while (vehiculos){
		for (i=1; vehiculos; i++){
			printf("\n\t Datos del vehiculo %i",i);
			printf("\n\n\t\t\t- Placa: %s",vehiculos->placa);
			printf("\n\n\t\t\t- Marca: %s",vehiculos->marca);
			printf("\n\n\t\t\t- Modelo: %s",vehiculos->modelo);
			printf("\n\n\t\t\t- A%co: %i\n",164,vehiculos->annio.yy);
			if (vehiculos->datosInfraccion) mostrarInfracciones(vehiculos->datosInfraccion);
			else printf("\n\n\t\t\tEste vehiculo no posee infracciones");
			vehiculos=vehiculos->vehiculoProx;
		}
	}
}

void mostrarInfracciones(struct infraccion *datosInfraccion){ //FUNCION PARA MOSTRAR LAS INFRACCIONES DE UN VEHICULO
	int i;
	for (i=1; datosInfraccion; i++){
		printf("\n\n\t\t\tDatos de la infraccion %i",i);
		printf("\n\n\t\t\t - Numero Infraccion: %i",datosInfraccion->numero);
		printf("\n\n\t\t\t - Tipo de infraccion: %s",datosInfraccion->tipo);
		printf("\n\n\t\t\t - Monto: %i",datosInfraccion->monto);
		printf("\n\n\t\t\t - Fecha de infraccion: %i/%i/%i",datosInfraccion->fechaInfraccion.dd,datosInfraccion->fechaInfraccion.mm,datosInfraccion->fechaInfraccion.yy);
		printf("\n\n\t\t\t - Pagado: %s\n\n\t\t\t\t\t",datosInfraccion->pagado);
		datosInfraccion=datosInfraccion->infraccionProx;
	}
}

///////////////////////////////////////////////////////////FUNCIONES MOSTRAR////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////FUNCIONES ORDENAR////////////////////////////////////////////////////////////////
void swapStr( char A[],char B[]){           //INTERCAMBIAR CARACTERES
	
	char temp[9];
	strcpy(temp,B);
	strcpy(B,A);
	strcpy(A,temp);
}

void swapLongInt(long int *A, long int *B){ //INTERCAMBIAR LONGITUD DE ENTEROS
	long int pote;
	pote = *A;
	*A = *B;
	*B = pote;
}

void swapInt(int *A, int *B){               //INTERCAMBIAR ENTEROS 
	int pote;
	pote = *A;
	*A = *B;
	*B = pote;
}

void swapApunVe(struct vehiculo **A, struct vehiculo **B){ //INTERCAMBIAR PUNTEROS DE VEHICULOS
	struct vehiculo *pote;
	pote =*A;
	*A = *B;
	*B = pote;
}

void swapApunInf(struct infraccion **A, struct infraccion **B){ //INTERCAMBIAR PUNTEROS DE INFRACCIONES
	struct infraccion *pote;
	pote =*A;
	*A = *B;
	*B = pote;
}

void ordenarBurbujaPlaca(struct vehiculo **v){ //ORDENAR POR EL METODO BURBUJA LOS VEHICULOS POR PLACA
	struct vehiculo *aux;
	int cambio = 1;
	while (cambio){
		cambio = 0;
		aux = *v;
		while(aux->vehiculoProx){
			if(strcmp(aux->placa,aux->vehiculoProx->placa)==1 ){
				cambio++;
				swapStr(aux->placa,aux->vehiculoProx->placa); //intercambio placa
				swapStr(aux->modelo,aux->vehiculoProx->modelo); //
				swapStr(aux->marca,aux->vehiculoProx->marca);
				swapStr(aux->color,aux->vehiculoProx->color);
				swapInt(&aux->annio.yy,&aux->vehiculoProx->annio.yy);
				swapApunInf(&aux->datosInfraccion, &aux->vehiculoProx->datosInfraccion);
			}
			aux=aux->vehiculoProx;
		}
	}
}

void ordenarBurbujaNumeroMulta(struct infraccion **f){   //ORDENAR POR EL METODO DE BURBUJA INFRACCIONES POR NUMERO DE MULTA
	struct infraccion *aux;
	int cambio = 1;
	while (cambio){
		cambio = 0;
		aux = *f;
		while(aux->infraccionProx){
			if(aux->numero > aux->infraccionProx->numero){
				cambio++;
				swapStr(aux->tipo,aux->infraccionProx->tipo); //intercambio placa
				swapStr(aux->pagado,aux->infraccionProx->pagado); //
				swapInt(&aux->numero,&aux->infraccionProx->numero);
				swapInt(&aux->monto,&aux->infraccionProx->monto);
				swapInt(&aux->fechaInfraccion.dd,&aux->infraccionProx->fechaInfraccion.dd);
				swapInt(&aux->fechaInfraccion.mm,&aux->infraccionProx->fechaInfraccion.mm);
				swapInt(&aux->fechaInfraccion.yy,&aux->infraccionProx->fechaInfraccion.yy);
			}
			aux=aux->infraccionProx;
		}
	}
}

void ordenarPersonaCedula(struct persona **p, int btn){ //Es cero si se quiere descendente. Es 1 si se quiere ascendente
	struct persona *aux;
	int cambio = 1;
	while (cambio){
		cambio = 0;
		aux = *p;
		while(aux->personaProx){
			if (btn){
				if(aux->cedula > aux->personaProx->cedula){
					cambio++;
					swapStr(aux->nombre,aux->personaProx->nombre); //intercambio placa
					swapStr(aux->apellidos,aux->personaProx->apellidos); //
					swapStr(aux->place.ciudad,aux->personaProx->place.ciudad);
					swapStr(aux->place.direccion,aux->personaProx->place.direccion);
					swapLongInt(&aux->cedula,&aux->personaProx->cedula);
					swapInt(&aux->fechaNacimiento.dd,&aux->personaProx->fechaNacimiento.dd);
					swapInt(&aux->fechaNacimiento.mm,&aux->personaProx->fechaNacimiento.mm);
					swapInt(&aux->fechaNacimiento.yy,&aux->personaProx->fechaNacimiento.yy);
				}	
			}else{
				if(aux->cedula < aux->personaProx->cedula){
					cambio++;
					swapStr(aux->nombre,aux->personaProx->nombre); //intercambio placa
					swapStr(aux->apellidos,aux->personaProx->apellidos); //
					swapStr(aux->place.ciudad,aux->personaProx->place.ciudad);
					swapStr(aux->place.direccion,aux->personaProx->place.direccion);
					swapLongInt(&aux->cedula,&aux->personaProx->cedula);
					swapInt(&aux->fechaNacimiento.dd,&aux->personaProx->fechaNacimiento.dd);
					swapInt(&aux->fechaNacimiento.mm,&aux->personaProx->fechaNacimiento.mm);
					swapInt(&aux->fechaNacimiento.yy,&aux->personaProx->fechaNacimiento.yy);
					swapApunVe(&aux->datosVehiculo,&aux->personaProx->datosVehiculo);
				}
			}
			
			aux=aux->personaProx;
		}
	}
}

void ordenarBurbujaIFecha(struct infraccion **i){    //FUNCION PARA ORDENAR LAS INFRACCIONES POR FECHA
	struct infraccion *aux;
	int fecha,fecha2,cambio = 1;
	while (cambio){
		cambio = 0;
		aux = *i;
		if(!aux->infraccionProx) return; //Si solo tiene una infraccion
		fecha=(((((aux->fechaInfraccion.yy)*100)+(aux->fechaInfraccion.mm))*100)+(aux->fechaInfraccion.dd));
		fecha2=(((((aux->infraccionProx->fechaInfraccion.yy)*100)+(aux->infraccionProx->fechaInfraccion.mm))*100)+(aux->infraccionProx->fechaInfraccion.dd));
		
		while(aux->infraccionProx){
			if (fecha > fecha2){
				cambio++;
				swapStr(aux->tipo,aux->infraccionProx->tipo); 
				swapStr(aux->pagado,aux->infraccionProx->pagado); 
				swapInt(&aux->numero,&aux->infraccionProx->numero);
				swapInt(&aux->monto,&aux->infraccionProx->monto);
				swapInt(&aux->fechaInfraccion.dd,&aux->infraccionProx->fechaInfraccion.dd);
				swapInt(&aux->fechaInfraccion.mm,&aux->infraccionProx->fechaInfraccion.mm);
				swapInt(&aux->fechaInfraccion.yy,&aux->infraccionProx->fechaInfraccion.yy);
			}
			aux=aux->infraccionProx;
		}
	}
}
///////////////////////////////////////////////////////////FUNCIONES ORDENAR////////////////////////////////////////////////////////////////

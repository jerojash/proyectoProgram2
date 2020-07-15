proyectoProgram2
marico el que lo lea


Su grupo de trabajo a sido seleccionado para realizar un sistema de control de multas a vehículos de la alcaldía de un municipio de Caracas. El sistema debe trabajar con listas dinámicas para evitar limitar la capacidad del sistema. Igualmente debe almacenar y recuperar en archivos secuenciales la información del sistema (al menos) cada vez que salga y entre al mismo. Sin el sistema de archivos no hay proyecto.

 

DATOS ALMACENADOS

 

Para realizar sus funciones el sistema debe almacenar la siguiente información:

 

PERSONAS

 

Cédula ( un entero muy largo ), Nombres y Apellidos ( máx. 20 caracteres ), Fecha de nacimiento ( yyyy mm dd  ), ciudad de nacimiento, dirección ( máx. 40 caracteres )
 

Un apuntador a su lista de vehículos
 

VEHICULOS

 

Placa ( hasta 8 caracteres ), Marca, Modelo, Año, color.
 

Un apuntador a sus infracciones
 

INFRACCIONES

 

Número de infracción (entero), Fecha de infracción, Tipo de Infracción, Multa(monto), Pagado (si/no)
 

 

MENÚ PRINCIPAL

 

El sistema de se compone de un menú principal que contiene dos entradas básicas.

 

MANTENIMIENTO
 

Que tiene DOS entradas básicas:

 

1 Personas: que permite agregar, modificar, consultar (por cédula o por nombre) y borrar a una persona del sistema
 

2 Vehículos: que permite agregar, modificar, consultar (por placa o por cédula del titular) y eliminar vehículos del sistema
 

 

OPERACIONES Y CONSULTAS
 

1 OPERACIONES con multas: Agregar, pagar, consultar( por número de multa ) , mover o eliminar
 

2 CONSULTAS
 

2.1 Dado el nombre de una persona, buscar todos los sinónimos que hay en el sistema y mostrar cédula, apellidos y nombres, fecha nacimiento, dirección y ciudad de nacimiento (para tratar de ubicar la cédula de la persona que nos interesa)
 

2.2 Dada una cédula de identidad
 

2.2.1 Mostrar los datos completos del titular y sus vehículos (placa, marca, modelo, año y color) con el total de vehículos que posee y el total de multas que adeuda el titular en total.
 

2.2.2 Apellidos y nombre del titular, su cédula. La placa de cada vehículo, marca, modelo, año y el total de multas pagadas y no pagadas del cada uno
 

2.2.3 Detalles completos de las multas no pagadas de todos sus vehículos ordenadas por número de placa (ascendente) y el total adeudado.
 

2.2.3 Y dada una placa mostrar todas las multas completas que ha tenido ordenadas por fecha ascendente. Primero las que no han sido pagadas y luego las ya canceladas.
 

2.2.4 Y un tipo de infracción mostrar todas las multas completas que ha tenido agrupadas por vehículo (placa, marca, año) ordenadas por fecha de infracción (ascendente).
 

2.3 Dada (sólo) una placa mostrar todas las multas de ese vehículo ordenadas por número de multa (ascendente) y el total de multas pagadas y el de las no pagadas
 

2.4 Dado un tipo de infracción y dos años (puede ser el mismo)
 

2.4.1) Todas las multas no pagadas ( cedula, apellidos y nombre, placa, marca, año, fecha de multa, monto. Ordenado por numero de cedula de los infractores (descendente). Total de ingreso pendiente por multas no pagadas.
 

2.4.2) Todas las multas pagadas ( cedula, apellidos y nombre, placa, marca, año, fecha de multa, monto. Ordenado por numero de cedula de los infractores (ascendiente). Total de ingreso por multas ya pagadas
 

 

Para que el sistema funcione coherentemente es necesario realizar las siguientes:

 

VALIDACIONES

 

            Personas:

                       - La cédula de identidad es un identificador ÚNICO.

                       - Una persona puede tener varios vehículos.

                        - Al eliminar una persona del sistema, deben borrarse primero las multas de sus vehículos, luego sus vehículos y finalmente la persona.

                        - Se puede modificar cualquier dato de una persona excepto su cédula

 

            Vehículos

                        -La placa es un identificador ÚNICO.

                        -La cédula asociada a un vehículo debe existir en el sistema.

                        -Un vehículo debe estar asociado sólo a UNA cédula de identidad.

                        -Al eliminar un vehículo deben borrarse primeramente sus infracciones y luego el vehículo.

                        - Se puede modificar cualquier dato de una persona excepto su placa

 

FECHA Y CONDICIONES DE ENTREGA

 

El proyecto debe entregarse vía módulo 7 ( en una tarea creada para tal fin ) a más tardar el viernes de la penúltima semana de clases al mediodía (12 m)
 

Deben entregarse todos los fuentes compilables en DevC así como anexar los archivos necesarios para que funcione (asegúrese de que el programa los busca en la misma carpeta donde se esté ejecutando el proyecto). Si el proyecto no compila o no guarda y lee los archivos cada vez favor ni siquiera entregar.
 

Los equipos estarán conformado por un máximo de cuatro (04) participantes. Sólo un miembro del equipo debe hacer el envío colocando los nombres de los demás miembros en el texto de entrega ( y en el encabezado del programa fuente )
 

Los archivos anexos deben contener los datos de prueba que serán publicados a la brevedad. De modo que al ejecutarse todos tengamos los mismos datos de entrada.

Diseño y modelado de Base de Datos "MONITOREO DE ESTACIONAMIENTO"

Diagrama Modelo entidad-relación, representación gráfica de entidades y relaciones-

Enlace para acceder: https://docs.google.com/drawings/d/1KJT9a-nzTtnFJ4r4bcypoxsDLpGtO2C5BTjq__JXz_M/edit?usp=sharing

Diseño de Base de datos, tablas, tipos de datos, claves principales.

Enlace para acceder: https://docs.google.com/document/d/17u2BmgZhg6UvPbcw8SgajFYzk6zwlPFy87-8bot8obM/edit?usp=sharing

Creación de Base de Datos en Máquina Virtual:

Base de Datos:
CONTROL_ESTACIONAMIENTO

Tablas de la base de Datos y tipos de datos:


• egresos
id_egreso: Type (int), Null(NO), Default (NULL), AUTO_INCREMENT, KEY(PRI).

fecha_hora_e: Type (timestamp), Null(YES), Default (CURRENT_TIMESTAMP, DEFAULT_GENERATE.

id_sucursal: Type(int), Null(NO), Default(NULL).



• ingresos:

id_ingreso: Type(int), Null(NO), Default(NULL), AUTO_INCREMENT, KEY(PRI).

fecha_hora_i: Type (timestamp), Null(YES), Default (CURRENT_TIMESTAMP, DEFAULT_GENERATE.

id_sucursal: Type(int), Null(NO), Default(NULL).



• sucursales

id_sucursal: Type(int), Null(NO), Default(NULL), KEY(PRI);

sucursales: Varchar(100), Null(YES), Default (NULL).



Usuario que no es root:

claudia@claudiaserver:~$ mysql -u iotsuc -p

Password: Sucu123@



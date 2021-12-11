# Contador de ingresos y egresos IOT

Como proyecto final de la **DIPLOMATURA EN PROGRAMACIÓN APLICADA AL INTERNET DE LAS COSAS (IOT)** decidimos implementar un sistema de monitoreo de ingresos y egresos al estacionamiento en distintas sucursales.
## Integrantes
* Claudia Monte
* Esteban Fernandez
* Leonardo Mestritua
* Sebastian Negri
* Hebe Paola Temi

> Somos un equipo de trabajo con diferentes conocimientos y formaciones variadas. Aprovecharemos esta oportunidad para poner a prueba nuestros conocimientos y aptitudes principalmente en el desarrollo en equipo y la colaboración continua.


## Tareas a realizar

:heavy_check_mark: Inizialización de proyecto.<br />
:heavy_check_mark: Adhesión de colaboradores.<br />
:heavy_check_mark: Creación de proyecto en PlatformIO.<br />
:heavy_check_mark: Creación de commit inicial.<br />
:heavy_check_mark: Definición y realización de tareas.<br />


# Tareas

A medida que avanzemos iremos añadiendo, borrando o modificando las tareas según el avance del proyecto.
- Crear Funciones o tareas:<br />
:heavy_check_mark: Actuador de ultrasonido.<br />
:heavy_check_mark: Medidor de distancia.<br />
:heavy_check_mark: Detector de ingreso.<br />
:heavy_check_mark: Detector de egreso.<br />
:heavy_check_mark: Contador de evento (ingreso o egreso).<br />
:heavy_check_mark: Actuador de alarmas o señales vigia (cupo completo o incompleto).<br />
:heavy_check_mark: Conexión MQTT.<br />
:heavy_check_mark: Conexión WiFi modo Station.<br />
:heavy_check_mark: Ingreso de credenciales MQTT via WEB.<br />
:heavy_check_mark: Envio de datos a Broker MQTT.<br />
:heavy_check_mark: Recepción de datos desde Broker MQTT.<br />

- Node Red:<br />
:heavy_check_mark: Inicialización del Broker MQTT.<br />
:heavy_check_mark: Inicialización de conexion a Base de Datos MySQL.<br />
:heavy_check_mark: Función de recepcion de datos.<br />
:heavy_check_mark: Formateo de datos.<br />
:heavy_check_mark: Envio de datos a MySQL.<br />
:x: Envio de datos a Dashboard.<br />
:x: Recepción de datos de Dashboard.<br />
:heavy_check_mark: Función de envio de datos a los Nodos.<br />
:heavy_check_mark: Función de formateo de datos para los Nodos.<br />

- Base de datos MySQL:<br />
:heavy_check_mark: Creacion e implementacion en servidor.<br />
:heavy_check_mark: Creación de usuario de escritura.<br />
:x: Creación de usuario de lectura.<br />
:heavy_check_mark: Creación de tabla.<br />
:heavy_check_mark: Definición de modelos o entidades de datos.<br />

- Graphana:<br />
:heavy_check_mark: Modificacion de usuario admin.<br />
:heavy_check_mark: Creación de usuario publico.<br />
:heavy_check_mark: Creación panel de graficos.<br />
:heavy_check_mark: Creación de query para graficos.<br />

> Coordinaremos las tareas a realizar por medio de los diferentes medios de comunicación disponibles.
Se realizará cada tarea en un branch diferente o al menos en el bramch especifico de quien la realiza y, una vez finalizada, se informará marcandola aquí mismo.
Cabe aclarar que cada tarea tendrá su comentario especifico en el commit y los comentarios pertinentes en los archivos correspondientes.

## Commits y mergs

Como se mencionó anteriormente, habrá **un commit por cada tarea realizada** y se hará, solo cuando haya suficiente código disponible para testear, **un merge a nivel general por seccion** para finalmente realizar **un ultimo merge de todos los branchs concluyendo el código**.


## Estructura del proyecto

Para mayor orden y una mejor colaboración, se respetará la siguiente estructura de directorios y ordenamiento de archivos:

> **Nota:** Esta estructura podrá ser modificada según necesidades del equipo o proyecto.



|Directorio|Archivos|
|-|-|
|src|`Configuración y funcionalidad del ESP32.`|
|node-red|`Flow's para el servidor de node red.`|
|mysql|`Configuraciónes, credenciales y otros datos pertinetnes.`|

# Contador de ingresos y egresos IOT

Como proyecto final de la **DIPLOMATURA EN PROGRAMACIÓN APLICADA AL INTERNET DE LAS COSAS (IOT)** decidimos implementar un sistema de monitoreo de ingresos y egresos a un recinto con el fin de cuantificar, informar y controlar los volumenes de personas en dicho recinto en base a una cantidad limitada por protocolos COVID u otros. 

## Integrantes
* Claudia Monte
* Esteban Fernandez
* Leonardo Mestritua
* Sebastian Negri

> Somos un equipo de trabajo con diferentes conocimientos y formaciones variadas. Aprovecharemos esta oportunidad para poner a prueba nuestros conocimientos y aptitudes principalmente en el desarrollo en equipo y la colaboración continua.


## Tareas a realizar

- [x] Inizialización de proyecto.
- [x] Adeción de colaboradores.
- [x] Creación de proyecto en PlatformIO.
- [x] Creación de commit inicial.
- [ ] Definición y realización de tareas.


# Tareas

A medida que avanzemos iremos añadiendo, borrando o modificando las tareas según el avance del proyecto.
- Crear Funciones o tareas:
- [ ] Actuador de ultrasonido.
- [ ] Medidor de distancia.
- [ ] Detector de ingreso.
- [ ] Detector de egreso.
- [ ] Contador de evento (ingreso o egreso).
- [ ] Actuador de alarmas o señales vigia (cupo completo o incompleto).
- [ ] Conexión MQTT.
- [ ] Conexión WiFi modo Station.
- [ ] Ingreso de credenciales MQTT via WEB.
- [ ] Envio de datos a Broker MQTT.
- [ ] Recepción de datos desde Broker MQTT.

- Node Red:
- [ ] Inicialización del Broker MQTT.
- [ ] Inicialización de conexion a Base de Datos MySQL.
- [ ] Función de recepcion de datos.
- [ ] Formateo de datos.
- [ ] Envio de datos a MySQL.
- [ ] Envio de datos a Dashboard.
- [ ] Recepción de datos de Dashboard.
- [ ] Función de envio de datos a los Nodos.
- [ ] Función de formateo de datos para los Nodos.

- Base de datos MySQL:
- [ ] Creacion e implementacion en servidor.
- [ ] Creación de usuario de escritura.
- [ ] Creación de usuario de lectura.
- [ ] Creación de tabla.
- [ ] Definición de modelos o entidades de datos.

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

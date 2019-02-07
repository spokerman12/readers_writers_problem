
# Simulacion del problema de lectores/escritores
  
  
Ultima modificacion: 12.04.2018

Propuesto en el Stallings - Operating Systems. Capitulo 5.6

"Hay un area de datos compartida entre diversos procesos.
Puede ser un archivo, un bloque o un banco de registros.
Hay un numero X de procesos que solo leen los datos lectores)
y un numero Y de solo escriben escritores).

Las condiciones son las siguientes

1. Cualquier numero de lectores puede leer el archivo simultaneamente
2. Solo un escritor puede escribir al archivo a la vez
3. Si el escritor esta escribiendo, ningun lector puede leer.


Primera solucion: Los lectores tienen prioridad

Los gatitos de Schroudinger

Los lectores abren una caja archivo compartido) y 
confirman el numero de gatitos en la caja.
Los escritores cambian el numero de gatitos en la caja.
Un lector jamas deberia obtener informacion falsa.

/* 
 * Universidad Simon Bolivar
 * Departamento de Computación y Tecnologı́a de la Información
 * Sistemas de Operacion I - CI3825
 * Trimestre Enero-Marzo 2018
 *
 * Simulacion del problema de lectores/escritores
 * 
 * 
 * Ultima modificacion: 12.04.2018
 *
 * @Autor: Daniel Francis. 12-10863
 *
 *
 * Propuesto en el Stallings - Operating Systems. Capitulo 5.6
 *
 * "Hay un area de datos compartida entre diversos procesos.
 *	Puede ser un archivo, un bloque o un banco de registros.
 *	Hay un numero X de procesos que solo leen los datos (lectores)
 *	y un numero Y de solo escriben (escritores).
 *
 *	Las condiciones son las siguientes
 *
 *	1. Cualquier numero de lectores puede leer el archivo simultaneamente
 *	2. Solo un escritor puede escribir al archivo a la vez
 *	3. Si el escritor esta escribiendo, ningun lector puede leer.
 *
 */

/*
 *	Primera solucion: Los lectores tienen prioridad
 *	
 *	Los gatitos de Schroudinger
 *
 *	Los lectores abren una caja (archivo compartido) y 
 *	confirman el numero de gatitos en la caja.
 *	Los escritores cambian el numero de gatitos en la caja.
 *	Un lector jamas deberia obtener informacion falsa.
 *	
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h> 
#include <sys/wait.h> 
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>


sem_t mutex;
sem_t db;
int numLectores = 0;

void * lector();
void * escritor();



void * lector(void * temp)
{
	int num = 0;

	sem_wait(&mutex);
	numLectores++;
	if(numLectores == 1)
	{
		sem_wait(&db);
	}
	sem_post(&mutex);



	// Lectura
	
	sleep(2);

	char buffer[10];
	FILE * datos = fopen("micaja","r");
	fscanf(datos,"%d",&num);
	printf("Hay %d gatitos\n", num);
	fclose(datos);
	

	
	sem_wait(&mutex);

	numLectores--;

	if(numLectores == 0)
	{
		sem_post(&db);
	}
	sem_post(&mutex);


}

void * escritor(void * temp)
{
	int k = rand() % 30;

	sem_wait(&db);


	// Escritura
	sleep(2);

	FILE * datos = fopen("micaja","w");
	if(datos)
	{
		printf("(ahora son %d...) \n",k );
		fprintf(datos, "%d",k);
		fclose(datos);
	}


	sem_post(&db);

}

int main()
{
	pthread_t thread;

	sem_init(&mutex,0,1);
	sem_init(&db,0,1);

	// Inicialmente hay 3 gatitos

	FILE * datos = fopen("micaja","w");

	fprintf(datos, "3");
	fclose(datos);

	for (int id=0; id<10; id++)
	{
		pthread_create(&thread, NULL,lector,NULL);
		pthread_create(&thread, NULL,escritor,NULL);
		sleep(5);

	}


    remove("micaja");

}



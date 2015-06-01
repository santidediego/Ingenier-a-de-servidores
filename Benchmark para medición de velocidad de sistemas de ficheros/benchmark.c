/*
    AUTOR: Santiago de Diego
    Este es un programa en c para hacer una prueba de la velocidad de un sistema de ficheros.
    EJECUCIÓN: El ejecutable se llama FS_Benchmark. No hacen falta argumentos, el programa crea un fichero de 1.2 GB y hace varias replicaciones de él
    REQUERIMIENTOS: Mínimo se necesitan 6 GB de espacio de disco para poder realizar la prueba.

*/


#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void copiarFichero(FILE *fich1, FILE *fich2)
{
  char aux;
  //Situamos el cursor al inicio para empezar a copiar
  fseek(fich1,SEEK_SET,0);
  while (!feof(fich1))
  {
    aux=getc(fich1);
    putc(aux ,fich2);
  }
}

int main(int args, char* argv[])
{

  printf("Bienvenido al benchmark para probar la eficiencia del sistema de ficheros\n");
  printf("El programa durará aproximadamente 15 minutos en realizar la prueba completa...\n");
  FILE * fich1;
  FILE * fich2;
  FILE * fich3;
  FILE * fich4;
  FILE * resultados;
  char nombre[20]="destino.txt";
//  char aux;
  clock_t t_inicial, t_final;
  double seg;
  int i=0;
  int ronda=0;
  //Creamos un fichero de 600 mb
  fich1=fopen("origen.txt","w+");
  resultados=fopen("Resultado.csv","a");
  printf("\nCreando un fichero de 1.2 GB para realizar la prueba\n");
  while(i<1200000000)
  {
    putc('a',fich1);
    i++;
  }
  printf("\nFichero grande creado\n");
  printf("\nVa a comenzar la prueba de rendimiento del sistema de ficheros, esto puede durar un poco, espere....\n");

  while (ronda<15)
  {
    fich2=fopen("destino.txt","w");
    fich3=fopen("destino2.txt","w");
    fich4=fopen("destino3.txt","w");
    printf("\nRonda %d\n",ronda);
    t_inicial=clock();
    //Copiamos el primer fichero
    copiarFichero(fich1,fich2);
    //Copiamos el segundo fichero
    copiarFichero(fich1,fich3);
    //Copiamos el tercer fichero
    copiarFichero(fich1,fich3);

    //Ahora borramos todos los ficheros
    remove ("destino.txt");
    remove("destino1.txt");
    remove("destino2.txt");
    remove("destino3.txt");
    t_final=clock();
    seg = (double)(t_final - t_inicial) / CLOCKS_PER_SEC;
    printf("%.16g milisegundos\n", seg * 1000.0);
    //Exportamos los resultados
    fprintf(resultados,"%.16f\n", seg * 1000.0);
    ronda++;
  }
  remove("origen.txt");
  fclose(fich1);
  fclose(fich2);
  fclose(fich3);
  fclose(fich4);
  fclose(resultados);
  return 0;
}

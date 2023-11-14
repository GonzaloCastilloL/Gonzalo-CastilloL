/************************************************************************
* Autor: J. Corredor
* Fecha: Octubre 2023
* Computación de Alto Rendimiento
* Maestría en Inteligencia Artificial
* Tema: Programa de Multiplicación de Matrices usando hilos OpenMP
* -Algorimo Clásico filasXcolumnas
************************************************************************
* Modifica: Gonzalo Castillo López
* Fecha: Noviembre 2023
* Ajuste: Modificaciones al programa para realizar calculo de matrices con
*         el producto FILAS * FILAS
*************************************************************************/

# include <stdlib.h>
# include <stdio.h>
# include <omp.h>
# include "sample.h"

# ifndef MIN
# define MIN(x,y) ((x)<(y)?(x):(y))
# endif

# define DATA_SZ (1024*1024*64*3)
/* static - permite que el valor de la variable persista entre llamadas
   double - tipo de dato Decimal doble, requiere 8 bytes de memoria
   el valor de DATA_SZ equivale a 201 MB */

static double  MEM_CHUNK[DATA_SZ];

/* función que inicializa matriz y no retorna valor al declararse como void*/
void Matrix_Init_col(int SZ, double *a, double *b, double *c){
    int j,k;
    for (j=0; j<SZ; j++) {
        a[j+k*SZ] = 2.0*(j+k);  
        b[j+k*SZ] = 3.2*(j-k);   
        c[j+k*SZ] = 1.0;
    }
}

/*Validación de la consistencia de los argumentos recibidos en la ejecución del programa */
int main (int argc, char **argv){
    int  N;

    if (argc < 2) {
        printf("MM1c MatrixSize [Sample arguments ...]\n"); 
        return -1;
    }

    N  = (int) atof(argv[1]); argc--; argv++;

    if (N > 1024*10) {
        printf("Unvalid MatrixSize\n");
        return -1;
    }

Sample_Init(argc, argv);

#pragma omp parallel
/*parametrización para la ejecución del proceso utilizando open MP en paralelo */

{
    int     NTHR, THR, SZ;
    int     i, j, k;
    double  *a, *b, *c;

    SZ    = N; 
    THR  = Sample_PAR_install();
    NTHR = omp_get_num_threads();
  
    a = MEM_CHUNK;
    b = a + SZ*SZ;
    c = b + SZ*SZ;

#pragma omp master
    Matrix_Init_col(SZ, a, b, c); 

    Sample_Start(THR);

#pragma omp for
/*Se modifico para permitir calcular el producto de las dos matrices FILA * FILA */
    for (i=0; i<SZ; i++)
		{    
            double *pA;
            pA = a+(i*SZ);
			for (j=0; j<SZ; j++)
			{ 
			  double *pB, S;
			  pB = b+(j*SZ);
              for (k=0; k<SZ; k++, pB++) 
				c[i*SZ+k] += (*pA * *pB);
              pA++;
			}
        }

    Sample_Stop(THR);
}
  
    Sample_End();
}

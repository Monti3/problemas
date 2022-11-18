#include <stdio.h>
#include <math.h>
// declaro los prototipos de las funciones 
int buscaprimos(int p);                              
int sacar_cantidad_de_divisores(int p);
// funcion principal: 
int main()
{
int x;
printf("Ingrese un numero: ");

//pido al usuario que ingrese un numero 
buscaprimos(x);                         // ingreso ese nunmero a la funcion de buscaprimos
}

// declaro la funcion bucaprimos
int buscaprimos(int p)
{
  int cdivisores = sacar_cantidad_de_divisores(p); // declaro esta variable como la cantidad de divisores de el numero
  printf("%i es la cantidad de divisores", cdivisores); // muestro la cantidad de divisores del numero 

  if (cdivisores == 2)
    {
      printf("\n%i es primo", p);          //a un numero se lo llama primo si la cantidad de divisores que tiene es exactamente 2
      return 0;
    }
  else
  {
    printf("\n%i no es primo", p);
    return 0;
  } 
  
}

int sacar_cantidad_de_divisores(int p)
{
  int cdivisores = 0;
  {                                    
  for (int x =1; x<=p; x++)            // busco los denominadores los cuales tengan resto 0 con numero indicado como numerador en la division 
      {                                 
        if (p%x == 0)            
        {
          cdivisores++;             
        }
      }                                   //primero, se tiene que ejecutar todo el bucle antes de devolver el valor.
    }

  return cdivisores; 
}

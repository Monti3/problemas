
#include <stdio.h>
#include <stdlib.h>


/* Una acaudalada anciana tiene gran cantidad de lingotes de oro de tres tipos: 
por valor de $56, de $106, y de $127. 
¿Cuál es la menor cantidad de lingotes que puede usar 
para depositar exactamente $5409 en una caja de seguridad de un banco?
*/
int main()
{
    long monto = 5409;
    long x, y, z,d = 0, g;
    long c[25]; c[0] = 1000;
    long menor = c[0];
for (x = 0; x< monto/127; x++)

    {
        for (y= 0; y<monto/106; y++ )
        {
            
                for (z = 0; z<monto/56; z++ )      // Se evaluan las combinaciones de lingotes 
                {   
                   
                    
                    long r= (long)127*x + (long)106*y + (long)56*z;   
                       
                      

                        if (r == monto)                        // Si la suma es igual al monto requrido, las cantidades se almacenan en un Array 
                    {   
                        int a= x+y+z;
                        printf ("\nlingotes de 127: %ld", x);
                        printf ("\nLingotes de 106: %ld", y);
                        printf ("\nLingotes de 56: %ld ", z);
                        printf ("\nCantidad de lingotes: %ld\n", a);

                         d= d+1;
                         c[d] = a;
                       
                        
                        
                    }
                }
            
        }
    }


for (int i= 1; i <= d; i++)  // Busco el menor numero dentro de un Array 
    {
        int x = c[i];
        if (x < menor)
            {
                menor=c[i];
               
               
            }

    }
printf("\nLa menor cantidad de lingotes para depositar exactamente %ld", monto); printf (" es: %ld", menor);

     return 0;
}

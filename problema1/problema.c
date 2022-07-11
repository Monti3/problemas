
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
#include <stdio.h>
#include "pico/stdlib.h"

/* Estructura para el LCD */
typedef struct {
  uint8_t rs;		/* GPIO de RS */
  uint8_t en;		/* GPIO de EN */
  uint8_t d4;		/* GPIO de D4 */
  uint8_t d5;		/* GPIO de D5 */
  uint8_t d6;		/* GPIO de D6 */
  uint8_t d7;		/* GPIO de D7 */
} lcd_t;

/* Inline functions */

/* Genera una estructura por defecto para el LCD */
static inline lcd_t lcd_get_default_config(void) {
  lcd_t lcd = { 0, 1, 2, 3, 4, 5 };
  return lcd;
}

/* Obtiene la mascara de pines de datos */
static inline uint32_t lcd_get_data_mask(lcd_t lcd) {
  return 1 << lcd.d4 | 1 << lcd.d5 | 1 << lcd.d6 | 1 << lcd.d7;
}

/* Obtiene la mascara de pines conectadas al LCD */
static inline uint32_t lcd_get_mask(lcd_t lcd) {
  return 1 << lcd.rs | 1 << lcd.en | lcd_get_data_mask(lcd);
}

/* Function prototypes */
void lcd_init(lcd_t lcd);
void lcd_put_nibble(lcd_t lcd, uint8_t nibble);
void lcd_put_command(lcd_t lcd, uint8_t cmd);
void lcd_putc(lcd_t lcd, char c);
void lcd_puts(lcd_t lcd, const char* str);
void lcd_clear(lcd_t lcd);
void lcd_go_to_xy(lcd_t lcd, uint8_t x,  uint8_t y);

/* Programa principal */

int main() {
	/* Inicializo el USB */
  stdio_init_all();

	gpio_set_dir(7,0);
	gpio_set_dir(8,0);
  gpio_set_dir(9,0);
	gpio_set_dir(10,0);

	/* Obtengo una variable para elegir los pines del LCD */
  lcd_t lcd = lcd_get_default_config();
	/* Por defecto, los pines son:
	 	- GP0 (RS)
		- GP1 (EN) 
		- GP2 (D4)
		- GP3 (D5)
		- GP4 (D6)
		- GP5 (D7)
		
		Si quieren cambiar alguno pueden hacerlo como lcd.d5 = 6 por ejemplo */
  
	/* Inicializo el LCD */
	lcd_init(lcd);

  while (true) {
		/* Limpio el LCD. Por defecto, va al 0;0 */
		bool b1 = gpio_get(7);
		bool b2 = gpio_get(8);
		bool b3 = gpio_get(9);
		bool b4 = gpio_get(10);

		bool estados[4] = b1,b2,b3,b4;


    lcd_clear(lcd);
		/* Escribo en la pantalla */
		lcd_puts(lcd, "Abiertos:");
		for(int x =0; x<5;x++)
		{
			int i = estados[x];
			if(i = 0)
			{

				lcd_puts(lcd, )

			}
		}
	
		
		/* Voy a la columna 6, fila 1 */
		lcd_go_to_xy(lcd, 0, 1);
		/* Imprime un mensaje en la pantalla */
    lcd_puts(lcd, "Cerrados:");
    /* Espero medio segundo */
		sleep_ms(500);
  }
}

/* Ignoren todo lo de abajo. Son las funciones que pueden usar */

/*
 * 	@brief	Initialize LCD with default configuration
 * 	@param	lcd: struct to an LCD
 */
void lcd_init(lcd_t lcd) {
  /* Get pin mask */
  uint32_t mask = lcd_get_mask(lcd);
  /* Initialize GPIO pins */
  gpio_init_mask(mask);
  /* Set pins direction as output */
  gpio_set_dir_out_masked(mask);
	/* Function set: 8 bits interface length */
	lcd_put_command(lcd, 0x03);
	/* Wait for 4.1 ms */
	sleep_ms(5);
	/* Function set: 8 bits interface length */
	lcd_put_command(lcd, 0x03);
	/* Wait for 100 us */
	sleep_us(100);
	/* Function set: 8 bits interface length */
	lcd_put_command(lcd, 0x03);
	/* Now the other instructions can be send */

	/* Function set: set interface to 4 bits length */
	lcd_put_command(lcd, 0x02);
	/* Function set: interface is 4 bits length */
	lcd_put_command(lcd, 0x02);
  /* Function set: two row display and 5x7 font */
  lcd_put_command(lcd, 0x08 | (false << 2));
  /* Display on, cursor off, blink off */
  lcd_put_command(lcd, 0x00);
  lcd_put_command(lcd, (3 << 2) | (false) | false);
  /* Input set command: increment cursor */
  lcd_put_command(lcd, 0x00);
  lcd_put_command(lcd, 0x06);
}

/*
 * 	@brief	Write a new nibble in data pins
 * 	@param	lcd: LCD pin struct
 * 	@param	nibble: four bit data
 */
void lcd_put(lcd_t lcd, uint8_t nibble) {
  /* Get data pins mask */
  uint32_t mask = lcd_get_data_mask(lcd);
	/* Get value from nibble */
	uint32_t value = 	((nibble & 0x8)? true : false) << lcd.d7 | 
										((nibble & 0x4)? true : false) << lcd.d6 |
										((nibble & 0x2)? true : false) << lcd.d5 | 
										((nibble & 0x1)? true : false) << lcd.d4;
  /* Send nibble */
  gpio_put_masked(mask, value);
	/* Set enable pin */
	gpio_put(lcd.en, true);
	/* Wait for 40 us */
	sleep_us(40);
	/* Clear enable pin */
	gpio_put(lcd.en, false);
}

/*
 * 	@brief	Write a new command in data pins
 * 	@param	lcd: LCD pin struct
 * 	@param	cmd: four bit command
 */
void lcd_put_command(lcd_t lcd, uint8_t cmd) {
	/* Clear rs pin */
	gpio_put(lcd.rs, false);
	/* Put command in data pins */
	lcd_put(lcd, cmd);
}

/*
 * 	@brief	Write a new character in data pins
 * 	@param	lcd: LCD pin struct
 * 	@param	c: char to be sent
 */
void lcd_putc(lcd_t lcd, char c) {
	/* Set rs pin */
	gpio_put(lcd.rs, true);
	/* Repeat twice */
	for(uint8_t nibble = 0; nibble < 2; nibble++) {
		/* Send lower nibble if it's the first time. Send higher nibble if second */
		uint8_t n = (nibble)? c & 0x0f : c >> 4;
		/* Write nibble */
		lcd_put(lcd, n);
	}
}

/*
 * 	@brief	Write a new string in LCD
 * 	@param	lcd: LCD pin struct
 * 	@param	str: string to be sent
 */
void lcd_puts(lcd_t lcd, const char* str) {
	/* Loop intul null character */
	while(*str) {
		/* Write the char */
		lcd_putc(lcd, *str);
		/* Increment pointer */
		str++;
	}
}

/*
 * 	@brief	Clear screen screen
 * 	@param	lcd: LCD pin struct
 */
void lcd_clear(lcd_t lcd) {
	/* Send clear command:  first nibble */
	lcd_put_command(lcd, 0x00);
	/* Send clear command: second nibble */
	lcd_put_command(lcd, 0x01);
	/* Wait for 4ms */
	sleep_ms(4);
}

/*
 * 	@brief	Go to starting coordinate
 * 	@param	lcd: LCD pin struct
 * 	@param	x: column number (starting in 0)
 * 	@param	y: row number (starting in 0)
 */
void lcd_go_to_xy(lcd_t lcd, uint8_t x, uint8_t y) {
	/* Auxiliary variable */
	uint8_t aux;
	/* Check if the first row (0) is required */
	if(y == 0) {
		/* Set direction */
		aux = 0x40 + x;
		/* Send first nibble */
		lcd_put_command(lcd, aux >> 4);
		/* Send seconds byte */
		lcd_put_command(lcd, aux & 0x0F);
	}
	/* Check if the second row (2) is required  */
	else if (y == 1) {
		/* Set direction */
		aux = 0xC0 + x;;
		/* Send first nibble */
		lcd_put_command(lcd, aux >> 4);
		/* Eend second nibble */
		lcd_put_command(lcd, aux & 0x0F);
	}
}

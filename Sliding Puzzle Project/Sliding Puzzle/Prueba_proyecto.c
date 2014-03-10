/**
 * @file   Prueba_proyecto.c
 * @brief  Aqui se escribe el codigo necesario para el juego.
 * 
 */ 

#define F_CPU 16000000UL
#define True 1
#define False 0
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>
#include "glcd.h"
#include "FuncType.h"

/**Variables de control relacionadas con el juego */
juego variablesJuego;

int main(void)
{
	
	/*Se inicializan los puertos.	*/
	DDRB=0x00;
	DDRA= 0xFF;
	DDRC=0xff;
	
	/*Se inicializan los puertos que generan las interupciones externas */
	DDRD= 0x00;
	DDRE=0x00;
	
	DATADDR = 0xff;	
	//Se inicializan las interrupciones
	
	EICRA= 0xFF;
	EICRB= 0xFF;
	
	/**Se habilitan las interrupciones */	
	sei();	
	
	//*puntresetPushed=&variablesJuego.resetPushed;
	//Se inicializan las variables necesarias para jugar
	ReiniciarJuego(&variablesJuego);
	
	//Inicializar GLCD
	glcd_on();	
	glcd_clear();	
	loadingBar();	
			
    while(1)
    {	sei();
		//Se habilita que solo se puedan usar los botones de arriba, abajo y seleccionar
	    EIMSK= 0x07;
		
		//Despliega el menu de seleccion de los niveles
	    menu(&variablesJuego.posCursor,&variablesJuego.seleccionScreen);				
		//Se habilita que se puedan usar todos los botones		
		EIMSK= 0xFF;		
		
		rellenarCasillas(variablesJuego.tablero1,variablesJuego.posCursor,&variablesJuego);
		
		variablesJuego.inGame=True;
		DrawScore();
					
		while (endGame(variablesJuego.tablero1)==1 && variablesJuego.puntuacion>0 && variablesJuego.resetPushed==False)
		{
			glcd_putchar(42,variablesJuego.cursorPantalla.y,variablesJuego.cursorPantalla.x,0,2);
			_delay_ms(500);		
			glcd_putchar(variablesJuego.valorCasilla,variablesJuego.cursorPantalla.y,variablesJuego.cursorPantalla.x,0,2);		
			_delay_ms(500);
		}		
		cli ();
		
		if (variablesJuego.puntuacion==0 && endGame(variablesJuego.tablero1)==1) 
		{
			glcd_clear();
			_delay_ms(500);
			glcd_puts("You Have Lost",5,3,0,1,0);
			_delay_ms(500);
			glcd_puts("Puntuacion 0",5,5,0,1,0);
			_delay_ms(500);
		}	
		if 	(endGame(variablesJuego.tablero1)==0 ||(endGame(variablesJuego.tablero1)==0 && variablesJuego.puntuacion==0))
		{
			glcd_clear();
			_delay_ms(500);
			glcd_puts("You have Won",5,3,0,1,0);
			_delay_ms(500);
			glcd_puts("Puntuacion",5,5,0,1,0);
			_delay_ms(500);
			glcd_puts(itoa (variablesJuego.puntuacion,variablesJuego.puntuacion_pantalla,10),25,6,0,1,0);
			_delay_ms(700);
		}
		if(variablesJuego.resetPushed==True)
		{
			glcd_clear();
			_delay_ms(500);
			glcd_puts("You have Won",5,3,0,1,0);
			_delay_ms(500);
			glcd_puts("Puntuacion",5,5,0,1,0);
			_delay_ms(500);
			glcd_puts(itoa (variablesJuego.puntuacion,variablesJuego.puntuacion_pantalla,10),25,6,0,1,0);
			_delay_ms(1000);			
			
		}
						
		//Se reinicializan las variables
		ReiniciarJuego(&variablesJuego);
        //TODO:: Please write your application code 
		}    
}	




				

/**
 * @file IsrImp.c
 * @brief Se implementan las ISR de las diferentes interrupciones externas
*/
#define F_CPU 16000000UL
#define True 1
#define False 0
#include "FuncType.h"
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>

extern juego variablesJuego;
extern int *puntresetPushed;
//Interrupciones

/**
  *@brief Codigo relacionado con el evento de presionar el boton de arriba 
  */
ISR(INT1_vect)
{
	_delay_ms(500);
	variablesJuego.control++;
	
	if (variablesJuego.seleccionScreen==True && variablesJuego.control>=2)
	{		
		if (variablesJuego.posCursor==2)
		{
			variablesJuego.posCursor=0;
		} 
		else
		{
			variablesJuego.posCursor++;
		}
		variablesJuego.control=0;
	}
	else if(variablesJuego.inGame==True)
	{
			
		glcd_putchar(variablesJuego.valorCasilla,variablesJuego.cursorPantalla.y,variablesJuego.cursorPantalla.x,0,2);
		// Verificar si el lugar a donde se desea mover, esta permitido
		if (checkLimit(1,&variablesJuego.cursorPantalla)==1 && variablesJuego.control>=2 )
		{
			variablesJuego.cursorPantalla.x-=2;		
			variablesJuego.indiceArreglo.y-=1;
			variablesJuego.valorCasilla =  variablesJuego.tablero1[variablesJuego.indiceArreglo.x][variablesJuego.indiceArreglo.y].letra;
			variablesJuego.control=0;
		}
	}	 
	
}

/**
  *@brief Codigo relacionado con el evento de presionar el boton de abajo 
 */
ISR(INT2_vect)
{	
	_delay_ms(500);
	variablesJuego.control++;
	if (variablesJuego.seleccionScreen==True && variablesJuego.control>=2)
	{	
		
		if (variablesJuego.posCursor==0)
		{
			variablesJuego.posCursor=2;
		}
		else
		{
			variablesJuego.posCursor--;
		}
		variablesJuego.control=0;
	}
	else if(variablesJuego.inGame==True)
	{
		
		
		glcd_putchar(variablesJuego.valorCasilla,variablesJuego.cursorPantalla.y,variablesJuego.cursorPantalla.x,0,2);
		// Verificar si el lugar a donde se desea mover, esta permitido
		if (checkLimit(2,&variablesJuego.cursorPantalla)==1 && variablesJuego.control>=2)
		{
			variablesJuego.indiceArreglo.y+=1;
			variablesJuego.cursorPantalla.x+=2;
			variablesJuego.valorCasilla =  variablesJuego.tablero1[variablesJuego.indiceArreglo.x][variablesJuego.indiceArreglo.y].letra;	
			variablesJuego.control=0;
		}	
	}		
}
/** 
  *@brief Codigo relacionado con el evento de presionar el boton de moverse a la derecha 
  */
ISR(INT3_vect)
{  
	_delay_ms(500);
	variablesJuego.control++;
	glcd_putchar(variablesJuego.valorCasilla,variablesJuego.cursorPantalla.y,variablesJuego.cursorPantalla.x,0,2);

	// Verificar si el lugar a donde se desea mover, esta permitido	
	if (checkLimit(3,&variablesJuego.cursorPantalla)==1 && variablesJuego.control>=2)
	{
		variablesJuego.indiceArreglo.x+=1;
		variablesJuego.cursorPantalla.y+=16;
		variablesJuego.valorCasilla =  variablesJuego.tablero1[variablesJuego.indiceArreglo.x][variablesJuego.indiceArreglo.y].letra;	
		variablesJuego.control=0;
	}
				
}
/**
    @brief  Codigo relacionado con el evento de presionar el boton hacia la izquierda 
*/
ISR(INT4_vect)
{	
	_delay_ms(500);
	variablesJuego.control++;
	glcd_putchar(variablesJuego.valorCasilla,variablesJuego.cursorPantalla.y,variablesJuego.cursorPantalla.x,0,2);    			// Verificar si el lugar a donde se desea mover, esta permitido	
	if (checkLimit(4,&variablesJuego.cursorPantalla)==1 && variablesJuego.control>=2)
	{
		variablesJuego.indiceArreglo.x-=1;
		variablesJuego.cursorPantalla.y-=16;
		variablesJuego.valorCasilla =  variablesJuego.tablero1[variablesJuego.indiceArreglo.x][variablesJuego.indiceArreglo.y].letra;
		variablesJuego.control=0;
	}
	
}
/**
 * @brief Rutina que se ejecuta cuando se presiona el boton de Mover.
*/
ISR(INT0_vect)
{	
	if (variablesJuego.seleccionScreen==True)
	{
		variablesJuego.seleccionScreen=False;
	}
	else if(variablesJuego.inGame==True)
	{	
		_delay_ms(500);
		variablesJuego.control++;
		glcd_putchar(variablesJuego.valorCasilla,variablesJuego.cursorPantalla.y,variablesJuego.cursorPantalla.x,0,2);
		if ( canMove(&variablesJuego.casillaVacia, &variablesJuego.indiceArreglo) ==1 && variablesJuego.control>=2 &&variablesJuego.puntuacion>0)
			{
	
   				glcd_putchar(variablesJuego.valorCasilla,variablesJuego.cursorPantalla.y,variablesJuego.cursorPantalla.x,0,2);
				variablesJuego.Contenido_seleccion = variablesJuego.tablero1[variablesJuego.indiceArreglo.x][variablesJuego.indiceArreglo.y].letra;
				variablesJuego.id_a_Mover= variablesJuego.tablero1[variablesJuego.indiceArreglo.x][variablesJuego.indiceArreglo.y].id;
				variablesJuego.Seleccion_On=1; //Indica que se ha seleccionado algo
				variablesJuego.mover_x= variablesJuego.indiceArreglo.x;
				variablesJuego.mover_y= variablesJuego.indiceArreglo.y;

				//Almacenar la posicion de la casilla vacia en pantalla
				variablesJuego.casillaVacia_Pantalla.x= variablesJuego.mover_Pantalla_x;
				variablesJuego.casillaVacia_Pantalla.y= variablesJuego.mover_Pantalla_y;

				//Almacenar la posicion en pantalla de la pieza a mover
				variablesJuego.mover_Pantalla_y= variablesJuego.cursorPantalla.y;
				variablesJuego.mover_Pantalla_x= variablesJuego.cursorPantalla.x;
				variablesJuego.mover= ' ';

				//Para ponerlo en la pantalla
				variablesJuego.valorCasilla = variablesJuego.Contenido_seleccion;
				variablesJuego.cursorPantalla.x= variablesJuego.casillaVacia_Pantalla.x;
				variablesJuego.cursorPantalla.y= variablesJuego.casillaVacia_Pantalla.y;

				/* Se guarda el id destino*/
				variablesJuego.idDestino= variablesJuego.tablero1[variablesJuego.casillaVacia.x][variablesJuego.casillaVacia.y].id;

				/* Se coloca el id de la casilla destino, en el  id de la casilla que se quiere mover */
				variablesJuego.tablero1[variablesJuego.mover_x][variablesJuego.mover_y].id= variablesJuego.idDestino;

				/* Se coloca el id de la casilla que se guardo en el id destino*/
				variablesJuego.tablero1[variablesJuego.casillaVacia.x][variablesJuego.casillaVacia.y].id=variablesJuego.id_a_Mover;

				//Poner en nueva posicion del arreglo la pieza a mover
				variablesJuego.tablero1[variablesJuego.mover_x][variablesJuego.mover_y].letra= variablesJuego.mover;

				//poner en nueva posicion del arreglo lo que se habia seleccionado
				variablesJuego.tablero1[variablesJuego.casillaVacia.x][variablesJuego.casillaVacia.y].letra = variablesJuego.Contenido_seleccion;

				variablesJuego.indiceArreglo.x=variablesJuego.casillaVacia.x;
				variablesJuego.indiceArreglo.y=variablesJuego.casillaVacia.y;
				variablesJuego.casillaVacia.x= variablesJuego.mover_x;
				variablesJuego.casillaVacia.y= variablesJuego.mover_y;
				variablesJuego.casillaVacia_Pantalla.x=variablesJuego.mover_Pantalla_x;
				variablesJuego.casillaVacia_Pantalla.y=variablesJuego.mover_Pantalla_y;
	
				//Poner la pieza "mover" donde estaba lo seleccionado
				glcd_putchar(variablesJuego.mover,variablesJuego.mover_Pantalla_y,variablesJuego.mover_Pantalla_x,0,2);
				variablesJuego.Seleccion_On=0;
				variablesJuego.puntuacion-=10;
				glcd_puts("    ",80,3,0,1,0);
				glcd_puts(itoa (variablesJuego.puntuacion,variablesJuego.puntuacion_pantalla,10),80,3,0,1,0);
				_delay_ms(500);
	
		}
		//Mostrar msj de que la seleccion no es valida
		else if (canMove(&variablesJuego.casillaVacia, &variablesJuego.indiceArreglo) !=1 && variablesJuego.inGame==True)
		{
			glcd_puts("Invalid", 70,5,0,1,0); 
			glcd_puts("Move", 80,6,0,1,0);
			_delay_ms(2000);
			glcd_puts("       ", 70,5,0,1,0);
			glcd_puts("    ", 80,6,0,1,0);
			_delay_ms(500);
		}
	}  
}
		

ISR(INT5_vect)
{	
	_delay_ms(500);
	variablesJuego.control++;
	if (variablesJuego.control>=2)
	{
		variablesJuego.resetPushed=True;
				
		variablesJuego.inGame=False;
		
		//Se habilitan las interrupciones
		glcd_clear();
		
		variablesJuego.control=0;
	}
	
}
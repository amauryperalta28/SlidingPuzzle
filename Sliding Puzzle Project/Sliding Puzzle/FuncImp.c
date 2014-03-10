/**
 * @file  FuncImp.c
 * @brief Implementacion de las funciones 
*/

#include "FuncType.h"
#define F_CPU 16000000UL
#define True 1
#define False 0
#include <util/delay.h>

/*
  * @brief Rellena un arreglo de casillas con letras aleatorias entre a y o 
  *
  * Ademas de rellenar el arreglo de casilla, imprime en la pantalla 
  * los valores de cada casilla en la pantalla
  *
  * @param[in]  t1			        Arreglo de casillas que se rellenara
  * @param[in]  nivel               Variable que especifica el nivel de complejidad del juego
  * @param[in]  juego1				Puntero a la estructura con las variables necesarias para el juego
  *
  * @return							No retorna nada
  */
void rellenarCasillas(tablero t1,unsigned int nivel, juego *juego1)
{
  /* Este es un arreglo de arreglos de letras con su id, para los diferentes niveles 
     de complejidad*/
  Letras niveles[3]=
  {	  {{'h',7},{'b',1},{'j',9},{'k',10},{'c',2},{'i',8},{'o',14},{'d',3},{'n',13},{'f',5},{'m',12},{'e',4},{' ',15},{'l',11},{'g',6},{'a',0}},
	  
	 {{'l',11},{'g',6},{'c',2},{' ',15},{'a',0},{'n',13},{'d',3},{'k',10},{'f',5},{'i',8},{'b',1},{'h',7},{'e',4},{'j',9},{'m',12},{'o',14}},
		  
	  {{'a',0},{'b',1},{'c',2},{'d',3},{'e',4},{'f',5},{'g',6},{'h',7},{'i',8},{'j',9},{'o',14},{'k',10},{'m',12},{'n',13},{'l',11},{' ',15} }	  
  };
unsigned int i;
unsigned int j;
unsigned int indeX=0;

//Se rellena el arreglo
	for (i=0; i< 4; i++)
	{	for (j=0; j<4; j++)
		{  //Se inserta la letra de la posicion actual en el arreglo de casillas
			t1[j][i].letra= niveles[nivel][indeX].letra;
			t1[j][i].id= niveles[nivel][indeX].id;
			
			indeX++;
		}
	}
/*Se inicializan las variables relacionadas a la posicion del cursor de la pantalla
  y el indice del arreglo */
switch (nivel)
{
case 2 :
		juego1->casillaVacia.x=3;  
		juego1->casillaVacia.y=3;
		juego1->indiceArreglo.x=3;
		juego1->indiceArreglo.y=3;
		juego1->casillaVacia_Pantalla.x=6;
		juego1->casillaVacia_Pantalla.y= 48;
		juego1->cursorPantalla.x=6;
		juego1->cursorPantalla.y=48;
	
		juego1->mover_x=3;
		juego1->mover_y=3;
		juego1->mover_Pantalla_y=48;
		juego1->mover_Pantalla_x=6;
	
	break;
	case 0 :
		juego1->casillaVacia.x=0;
		juego1->casillaVacia.y=3;
		juego1->indiceArreglo.x=0;
		juego1->indiceArreglo.y=3;
		juego1->casillaVacia_Pantalla.x=6;
		juego1->casillaVacia_Pantalla.y= 0;
		juego1->cursorPantalla.x=6;
		juego1->cursorPantalla.y=0;
		
		juego1->mover_x=0;
		juego1->mover_y=3;
		juego1->mover_Pantalla_y=0;
		juego1->mover_Pantalla_x=6;
		break;
	case 1:
		juego1->casillaVacia.x=3;
		juego1->casillaVacia.y=0;
		juego1->indiceArreglo.x=3;
		juego1->indiceArreglo.y=0;
		juego1->casillaVacia_Pantalla.x=0;
		juego1->casillaVacia_Pantalla.y= 48;
		juego1->cursorPantalla.x=0;
		juego1->cursorPantalla.y=48;
		
		juego1->mover_x=3;
		juego1->mover_y=0;
		juego1->mover_Pantalla_y=48;
		juego1->mover_Pantalla_x=0;
	break;

}
indeX=0;
//Se escribe en la pantalla

	for (i=0; i<= 6; i=i+2)
	{		for (j=0; j<64; j=j+16)
		{
			glcd_putchar(niveles[nivel][indeX].letra, j,i,0,2);
			indeX++;		
		}
	}
}

/*
 * @brief Verifica si se puede mover el cursor dependiendo el tipo de movimiento
 *
 * @param[in]  tipoMov       Este es el tipo de movimiento si es up,down,left o right
 * @param[in]  Pos_actual    Esta es la posicion actual del cursor
 *
 * @return				     1 si se puede mover, o si no se puede
 */
unsigned int checkLimit(unsigned int tipoMov, posicion *Pos_actual)
{
	switch (tipoMov)
	{
	case 1:	
		if (Pos_actual->x==0)
		return 0;
		else
		return 1;
		
		break;
	case 2:
		if (Pos_actual->x==6)
		return 0;
		else
		return 1;
		
		break;
	case 3:
		if (Pos_actual->y==48)
		return 0;
		else
		return 1;
	
		break;
	case 4:
		if (Pos_actual->y==0)
		return 0;
		else
		return 1;
	
	break;
	}
	return -1;
}

/* 
 * @brief Determina si se puede colocar una letra en una casilla especificada
 *
 * @param[in] posBlanco      Este es un puntero a la posicion de la casilla vacia
 * @param[in] posIndiceArray Este es un puntero a la posicion del indice del arreglo
 *
 * @return					 1 si se puede colocar la letra en casilla, 0 si no se puede.	
 */
unsigned int canMove(posicion *posBlanco, posicion *posIndiceArray)
{
	posicion posPermitidas[4];
	unsigned int IndexValidmove=0;
	unsigned int i;
	
	//Para arriba
	if(limite(posBlanco->x,posBlanco->y-1)==1)
	{
		posPermitidas[IndexValidmove].x= posBlanco->x;
		posPermitidas[IndexValidmove].y= posBlanco->y-1;
		IndexValidmove++;
	}
	//Para abajo
	if (limite(posBlanco->x,posBlanco->y+1)==1)
	{
		posPermitidas[IndexValidmove].x= posBlanco->x;
		posPermitidas[IndexValidmove].y= posBlanco->y+1;
		IndexValidmove++;
	}
	//para la derecha
	if (limite(posBlanco->x+1,posBlanco->y)==1)
	{
		posPermitidas[IndexValidmove].x= posBlanco->x+1;
		posPermitidas[IndexValidmove].y= posBlanco->y;
		IndexValidmove++;
	}
	//para la izquierda
	if (limite(posBlanco->x-1,posBlanco->y)==1)
	{
		posPermitidas[IndexValidmove].x= posBlanco->x-1;
		posPermitidas[IndexValidmove].y= posBlanco->y;
		IndexValidmove++;
	}
	
	for (i=0; i<IndexValidmove+1;i++ )
	{
		if (posIndiceArray->x== posPermitidas[i].x && posIndiceArray->y== posPermitidas[i].y )
		{
			return 1;
		}
	}
		
	return 0;
	
}
/*
 * @brief Determina si la posicion esta en los limites permitidos
 *
 * @param[in] posX	        Es la posicion en x a evaluar
 * @param[in] posY          Es la posicion en y a evaluar
 *
 * @return					1 si esta en los limites, 0 si no lo esta.
 */
unsigned int limite(unsigned int posX, unsigned int posY)
{
	
	return ( ( (posX >=0) && (posX <=3) ) && ( (posY >=0) && (posY <=3) )? 1:0 );
}
/*
 * @brief Determina si el juego termino
 *
 * @param[in] t1                              Este es el arreglo de casillas a verificar
 *
 * @return				                      0 si termino, 1 si no ha terminado
 */
unsigned int endGame(tablero t1)
{ 	
	unsigned int i;
	unsigned int j;
	unsigned int z=0;
	unsigned int arreglo[16];
	
	// Se rellena un arreglo unidimensional con los valores de las casillas del tablero
	for (i=0; i<4; i++)
	{
		for (j=0; j<4; j++)
		{
			arreglo[z]= t1[j][i].id;
			
			z++;
		}
	}
	
	// Se verifica si termino el juego
	for (i=0; i< 15; i++)
	{
		// Si el arreglo no esta organizado ascendentemente retorna 1
		if (arreglo[i+1]< arreglo[i])
		{
			return 1;
		}
	}
	
	return 0;
}

/*
  * @brief       Despliega el menu de seleccion de dificultad del juego
  * @param[in]   posCursor         Este es un puntero a la posicion de la flecha
  * @param[in]   selectionScreen   Esta es un puntero al estado del juego
  *
  * @return      0 si se selecciono un nivel
  */
void menu ( unsigned int *posCursor, unsigned int *selectionScreen)
{
	unsigned int lastPosCursor=3;
	while(*selectionScreen== True)
	{
		_delay_ms(500);
		
		if(*posCursor==0 && *posCursor!= lastPosCursor)
		{   glcd_clear();
			lastPosCursor=*posCursor;
			glcd_puts("Level", 0,0,0,2,0);
			glcd_puts("Easy", 0,2,0,2,0);
			glcd_puts("Medium", 0,4,0,2,0);
			glcd_puts("-Hard", 0,6,0,2,0);
		}
		else if (*posCursor==1 && *posCursor!= lastPosCursor)
		{   glcd_clear();
			lastPosCursor=*posCursor;
			glcd_puts("Level", 0,0,0,2,0);
			glcd_puts("Easy", 0,2,0,2,0);
			glcd_puts("-Medium", 0,4,0,2,0);
			glcd_puts("Hard", 0,6,0,2,0);
		}
		else if(*posCursor==2 && *posCursor!= lastPosCursor)
		{   glcd_clear();
			lastPosCursor=*posCursor;
			glcd_puts("Level", 0,0,0,2,0);
			glcd_puts("-Easy", 0,2,0,2,0);
			glcd_puts("Medium", 0,4,0,2,0);
			glcd_puts("Hard", 0,6,0,2,0);

		}

	}
glcd_clear();

}

/*
  * @brief       Dibuja en la pantalla lo referente a puntuacion y otros elementos
  *
  * @return      no retorna nada
  */
void DrawScore(void)
{
	//Mostrar puntuacion en Pantalla
	glcd_puts("Puntos",72,1,0,1,0);
	glcd_puts("1000",80,3,0,1,0);
	
	//Separar ambos lados de la pantalla (uno de control, otro de juego)
	unsigned int i;
	for (i=0;i<=8;i++)
	glcd_putchar(124,64,i,0,1);
	
}
/*
	 * @brief Reinicia el juego
	 *                Reinicializa las variables necesarias para poder empezar el juego nuevamente
	 * 
	 * @return        no retorna nada
	*/
void ReiniciarJuego(juego *variablesJuego)
{
		variablesJuego->mover= ' ';
	    variablesJuego->valorCasilla= ' ';
		/*Esta variable sirve para evitar el rebote en los push buttons a la hora de 
		   generar las interrupciones*/
		variablesJuego->control = 0;
		/*Variable que indica si hay casilla seleccionada */
		variablesJuego->Seleccion_On=0;
		/*Posicion en x en el arreglo de la casilla que se quiere mover */
		variablesJuego->mover_x=3;
		/*Posicion en y en el arreglo de la casilla que se quiere mover */
		variablesJuego->mover_y=3;
		variablesJuego->mover_y=48;
		/*Posicion en y en la pantalla de la casilla que se quiere mover */
		variablesJuego->mover_x=6;

		/*Variable que guarda la puntuacion */
		variablesJuego->puntuacion=1000;
		/*Variable que indica si el juego esta en el menu de seleccion */
		variablesJuego->seleccionScreen=True;
		/*Variable que indica si se esta jugando */
		variablesJuego->inGame=False;
		/*Variable que indica si se presiono el boton de reset */
		variablesJuego->resetPushed=False;
		/*Variable que guarda la posicion del cursor en el menu de seleccion */
		variablesJuego->posCursor=2;
		//Inicializamos la posicion del cursor de la pantalla
		variablesJuego->cursorPantalla.x=6;
		variablesJuego->cursorPantalla.y=48;	
		//Inicializamos la posicion del indice del arreglo
		variablesJuego->indiceArreglo.x=3;
		variablesJuego->indiceArreglo.y=3;	
		//Inicializamos la posicion de la casilla Vacia en el arreglo y en pantalla
		variablesJuego->casillaVacia.x=3;
		variablesJuego->casillaVacia.y=3;
		variablesJuego->casillaVacia_Pantalla.x= 6;
		variablesJuego->casillaVacia_Pantalla.y= 48;				
}
/*
  * @brief Dibuja en la pantalla una barra de cargando
  *
  * @return    no retorna nada
  *
  */
void loadingBar(void)
{
  int i;
  int j;
  glcd_puts("Slide",0,0,0,2,0);
  glcd_puts("Puzzle",0,2,0,2,0);
  _delay_ms(2000);
  
  for(i=0; i<3; i++)
  {
	  glcd_puts("Slide",0,0,0,2,0);
	  glcd_puts("Puzzle",0,2,0,2,0);
	  glcd_puts("Loading",32,5,0,1,0);
	  
	  for(j=16; j<=96; j=j+16)
	  {
		  glcd_putchar(35,j,6,0,1);
		  _delay_ms(600);
	  }
	  
	  glcd_clear();
  }  
  glcd_clear();
}
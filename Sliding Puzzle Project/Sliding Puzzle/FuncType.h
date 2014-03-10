/**
  * @file FuncType.h
  * @brief Tipos y prototipos de las funciones
*/

typedef struct posicion
{
	 unsigned int x;
	 unsigned int y;
}posicion;

/**Tipos relacionados con las casillas */
 typedef struct casilla
 {
	 char letra;
	 unsigned int id;
	 
 }casilla;
 
 /** Este es el tablero*/
 typedef casilla tablero [4][4];
 
 /** Tipos y estructuras relacionadas con el rellenado de las casillas */
 typedef const  struct letras
 {  
	 char letra;
	 unsigned int id;	 
 }letras;
 
 /** Tipo necesario para guardar el rellenado del tablero segun el tipo*/
 typedef letras Letras[16];
 
 /** Estructura relacionada con las variables de control del juego */
 typedef struct juego
 {
	 /* En esta variable se guarda la posicion del cursor de la pantalla*/
	posicion cursorPantalla;
	/* En esta variable se guarda la posicion en donde parado el indice del arreglo*/
	posicion indiceArreglo;
	/*Esta es la posicion de la casilla vacia en el arreglo */
	posicion casillaVacia;
	/*Esta es la posicion de la casilla vacia en la pantalla */
	posicion casillaVacia_Pantalla;
	/*Este es el arreglo en donde se desarrolla el juego */
	tablero tablero1;
	/*Esta variable guarda la letra correspondiente al indice en el cual se esta parado 
	   en el arreglo para hacer el efecto blink*/
	char valorCasilla;
	/*Esta variable guarda lo que se selecciono */
	volatile char Contenido_seleccion ;
	/*Esta variable guarda la letra correspondiente a la posicion actual */
	volatile char mover;
	/*Esta variable sirve para evitar el rebote en los push buttons a la hora de 
	   generar las interrupciones*/
	volatile unsigned int  control;
	/*Variable que indica si hay casilla seleccionada */
	volatile unsigned int Seleccion_On;
	/*Posicion en x en el arreglo de la casilla que se quiere mover */
	volatile unsigned int mover_x;
	/*Posicion en y en el arreglo de la casilla que se quiere mover */
	volatile unsigned int mover_y;
	/*Posicion en x en la pantalla de la casilla que se quiere mover */
	volatile int mover_Pantalla_y;
	/*Posicion en y en la pantalla de la casilla que se quiere mover */
	volatile int mover_Pantalla_x;
	/* Variables en donde se guardaran los id de las letras que se intercambiaran*/
	volatile unsigned int id_a_Mover;
	/*Variable en la que se guarda el id de la casilla destino */
	volatile unsigned int idDestino;
	/*Variable que guarda la puntuacion */
	volatile unsigned int  puntuacion;
	/*Variable que sirve para la conversion de la puntuacion en una cadena de caracteres */
	char puntuacion_pantalla[5];
	/*Variable que indica si el juego esta en el menu de seleccion */
	unsigned int seleccionScreen;
	/*Variable que indica si se esta jugando */
	unsigned int inGame;
	/*Variable que indica si se presiono el boton de reset */
	unsigned int resetPushed;
	/*Variable que guarda la posicion del cursor en el menu de seleccion */
	unsigned int posCursor;
	 
 }juego;
 
 /** Prototipos de las funciones*/
 
/**
  * @brief	Rellena un arreglo de casillas dependiendo del nivel seleccionado 
  * Rellena la pantalla segun el modo seleccionado
  *
  * @param[in]  t1			        Arreglo de casillas que se rellenara
  * @param[in]  nivel               Variable que especifica el nivel de complejidad del juego
  * @param[in]  juego1				Puntero a la estructura con las variables necesarias para el juego
  *
  * @return							No retorna nada
  */
void rellenarCasillas(tablero t1,unsigned int nivel, juego *juego1);

/** 
 * @brief Verifica si se puede mover el cursor dependiendo el tipo de movimiento
 *
 * @param[in]  tipoMov       Este es el tipo de movimiento si es up,down,left o right
 * @param[in]  Pos_actual    Esta es la posicion actual del cursor
 *
 * @return				     1 si se puede mover, o si no se puede
 */
unsigned int checkLimit(unsigned int tipoMov, posicion *Pos_actual);


/** 
 * @brief Determina si se puede colocar una letra en una casilla especificada
 *
 * @param[in] posBlanco      Este es un puntero a la posicion de la casilla vacia
 * @param[in] posIndiceArray Este es un puntero a la posicion del indice del arreglo
 *
 * @return					 1 si se puede colocar la letra en casilla, 0 si no se puede.	
 */
unsigned int canMove(posicion *posBlanco, posicion *posIndiceArray);

/**
 * @brief Determina si la posicion esta en los limites permitidos
 *
 * @param[in] posX	        Es la posicion en x a evaluar
 * @param[in] posY          Es la posicion en y a evaluar
 *
 * @return					1 si esta en los limites, 0 si no lo esta.
 */
unsigned int limite(unsigned int posX, unsigned int posY);

/**
 * @brief Determina si el juego termino
 *
 * @param[in] t1                             Este es el arreglo de casillas a verificar
 *
 * @return				                      0 si termino, 1 si no ha terminado
 */
unsigned int endGame(tablero t1);

/**
  * @brief       Despliega el menu de seleccion de dificultad del juego
  * @param[in]   posCursor         Este es un puntero a la posicion de la flecha
  * @param[in]   selectionScreen   Esta es un puntero al estado del juego
  *
  * @return      no retorna nada
  */
void menu ( unsigned int *posCursor, unsigned int *selectionScreen);

/**
  * @brief       Dibuja en la pantalla lo referente a puntuacion y otros elementos
  *
  * @return      no retorna nada
  */
void DrawScore(void);

/**
  * @brief     Reinicializa las variables necesarias para poder empezar el juego nuevamente
  *
  * @param[in] variablesJuego         Estructura con las variables que se necesitan para jugar
  * 
  */
void ReiniciarJuego(juego *variablesJuego);
/**
  * @brief        Dibuja en la pantalla una barra de cargando
  *
  * @return       no retorna nada.
  */
void loadingBar(void);
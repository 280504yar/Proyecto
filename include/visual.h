#ifndef VISUAL_H
#define VISUAL_H

//Biblioteca a utilizar
#include "raylib.h"

//Structs para facilitar la información
typedef enum {
	SIM_X,
	SIM_CIRCULO,
	SIM_TRIANGULO,
	SIM_CUADRADO
} Simbolo;

typedef struct {
	Color color;
	Simbolo simbolo;
	int victorias;
} Jugador;

//------------------------------HEADER DE FUNCIONES A UTILIZAR------------------------------------
void ejecutar_ventana(int ancho, int alto);                                // Abre la ventana en el ordenador
void cerrar_ventana();                                                     // Cierra el juego
void tablero();                                                            // Dibuja el tablero en la ventana
void dibujar_simbolo(int fila, int columna, Simbolo simbolo, Color color); // Dibuja un simbolo en una casilla
int temporizador();                                                 // Inicia el temporizador, retorna 0 si ya pasaron 20 segundos
void reiniciar_temp();                                                     // Reinicio simple del temporizador
void victorias(const Jugador jugadores[], int cantidad_jugadores);         // Cuenta y dibuja las victorias de cada jugador
void dibujar_reset(Rectangle *area);                                       // Dibuja el botón de reinicio en un área
int reset_check(Rectangle *area);                                          // Retorna 1 si se presionó reniciar, 0 si no
									   
#endif


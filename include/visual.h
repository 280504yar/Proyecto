#ifndef VISUAL_H
#define VISUAL_H
#include "raylib.h"

// Constantes compartidas
#define TAM_CELDA 80
#define POS_X 560
#define POS_Y 0
#define ANCHO 1280
#define ALTO 720
#define FPS 60
#define DURACION_TURNO 20.0f


// Declaración de la variable global
extern float tiempo_restante;

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
int reset_check(Rectangle boton);                                          // Retorna 1 si se presionó reniciar, 0 si no
									   
#endif


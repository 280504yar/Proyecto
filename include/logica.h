// logica.h
#ifndef LOGICA_H
#define LOGICA_H
#include "visual.h"

// Tamaño del tablero
#define BOARD_SIZE 9
#define NUM_PLAYERS 4

// Estructura para el estado del juego
typedef struct {
    Simbolo tablero[BOARD_SIZE][BOARD_SIZE]; // Estado del tablero
    Jugador jugadores[NUM_PLAYERS];           // Información de jugadores
    int jugador_actual;                       // Índice del jugador actual
    bool juego_terminado;                     // Estado del juego
    int ganador;                              // Índice del jugador ganador
} EstadoJuego;

// Logica principal del juego
void inicializar_juego(EstadoJuego *estado);
void procesar_clic(EstadoJuego *estado, int fila, int columna);
bool verificar_victoria(EstadoJuego *estado, int fila, int columna);
bool verificar_empate(EstadoJuego *estado);
void cambiar_jugador(EstadoJuego *estado);

#endif

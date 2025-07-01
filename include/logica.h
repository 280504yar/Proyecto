// logica.h
#ifndef LOGICA_H
#define LOGICA_H
#include "visual.h"

// Tamaño del tablero
#define BOARD_SIZE 9
#define NUM_PLAYERS 4

// Representación de jugadores
typedef enum {
    VACIO = -1,
    JUGADOR_X,
    JUGADOR_O,
    JUGADOR_TRIANGULO,
    JUGADOR_CUADRADO
} SimboloJugador;

// Estructura para el estado del juego
typedef struct {
    SimboloJugador tablero[BOARD_SIZE][BOARD_SIZE]; // Estado del tablero
    int jugador_actual;                       // Índice del jugador actual
    bool juego_terminado;                     // Estado del juego
    int ganador;                              // Índice del jugador ganador
} EstadoJuego;

// Logica principal del juego
void iniciar_juego(EstadoJuego *estado);
void manejar_jugada(EstadoJuego *estado, int fila, int columna);
bool hay_ganador(const EstadoJuego *estado, int fila, int columna);
bool hay_empate(const EstadoJuego *estado);
void siguiente_jugador(EstadoJuego *estado);
void obtener_info_jugadores(const EstadoJuego *estado, Jugador jugadores[NUM_PLAYERS]);

// Constantes compartidas
extern const Simbolo simbolos_visual[];
extern const Color colores_jugadores[];

#endif

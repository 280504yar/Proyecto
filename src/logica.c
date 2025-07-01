#include "logica.h"
#include "visual.h"
#include <stdbool.h>

// Mapeo entre SimboloJugador y Simbolo
const Simbolo simbolos_visual[NUM_PLAYERS] = {
    SIM_X,       // JUGADOR_X
    SIM_CIRCULO, // JUGADOR_O
    SIM_TRIANGULO, // JUGADOR_TRIANGULO
    SIM_CUADRADO   // JUGADOR_CUADRADO
};

// Colores para cada jugador
const Color colores_jugadores[NUM_PLAYERS] = {
    RED,    // JUGADOR_X
    BLUE,   // JUGADOR_O
    GREEN,  // JUGADOR_TRIANGULO
    YELLOW  // JUGADOR_CUADRADO
};

// Iniciando el juego
void iniciar_juego(EstadoJuego *estado) {
    // Limpiar tablero
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            estado->tablero[i][j] = VACIO;
        }
    }
    
    estado->jugador_actual = 0;
    estado->juego_terminado = false;
    estado->ganador = -1;

// Inicializar contadores de victoria (solo en el primer inicio)
    static bool primera_vez = true;
    if (primera_vez) {
        for (int i = 0; i < NUM_PLAYERS; i++) {
            estado->victorias[i] = 0;
        }
        primera_vez = false;
    }
}

// Maneja una jugada en la posición (fila, columna)
void manejar_jugada(EstadoJuego *estado, int fila, int columna) {
    // Validar posición
    if (fila < 0 || fila >= BOARD_SIZE || columna < 0 || columna >= BOARD_SIZE) return;
    
    // Reglas para validar jugada (si el espacio esta vacio y el juego no esta terminado)
    if (estado->tablero[fila][columna] == VACIO && !estado->juego_terminado) {
        // Registrar jugada
        estado->tablero[fila][columna] = estado->jugador_actual;
        
        // Verificar victoria
        if (hay_ganador(estado, fila, columna)) {
	    estado->juego_terminado = true;
            estado->ganador = estado->jugador_actual;
            estado->victorias[estado->ganador]++; // Incrementar victorias del ganador
        } 
        // Verificar empate
        else if (hay_empate(estado)) {
            estado->juego_terminado = true;
        }
        // Continuar juego
        else {
            siguiente_jugador(estado);
        }
    }
}

// Verifica si hay un ganador a partir de la última jugada
bool hay_ganador(const EstadoJuego *estado, int fila, int columna) {
    const SimboloJugador actual = estado->tablero[fila][columna];
    int contador;
    
    // Direcciones: horizontal, vertical, diagonal (izquierda a derecha), diagonal (derecha a izquierda)
    int direcciones[4][2] = {{0,1}, {1,0}, {1,1}, {1,-1}};
    
    for (int d = 0; d < 4; d++) {
        contador = 1; // La celda actual ya cuenta
        
        // Buscar en dirección positiva
        for (int i = 1; i < 3; i++) {
            int r = fila + i * direcciones[d][0];
            int c = columna + i * direcciones[d][1];
            
            if (r >= 0 && r < BOARD_SIZE && c >= 0 && c < BOARD_SIZE && 
                estado->tablero[r][c] == actual) {
                contador++;
            } else break;
        }
        
        // Buscar en dirección negativa
        for (int i = 1; i < 3; i++) {
            int r = fila - i * direcciones[d][0];
            int c = columna - i * direcciones[d][1];
            
            if (r >= 0 && r < BOARD_SIZE && c >= 0 && c < BOARD_SIZE && 
                estado->tablero[r][c] == actual) {
                contador++;
            } else break;
        }
        
        // Condicion para verificar el ganador
        if (contador >= 3) return true;
    }
    
    return false;
}

// Verifica si el juego terminó en empate
bool hay_empate(const EstadoJuego *estado) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (estado->tablero[i][j] == VACIO) {
                return false;
            }
        }
    }
    return true;
}

// Cambia al siguiente jugador
void siguiente_jugador(EstadoJuego *estado) {
    estado->jugador_actual = (estado->jugador_actual + 1) % NUM_PLAYERS;
}
//Nueva ronda
void preparar_nueva_ronda(EstadoJuego *estado) {
    // Limpiar el tablero
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            estado->tablero[i][j] = VACIO;
        }
    }
    
    // Mantener el contador de victorias (ya está en la estructura Jugador)
    estado->juego_terminado = false;
    estado->ganador = -1;
}

// Función de compatibilidad 
void obtener_info_jugadores(const EstadoJuego *estado, Jugador jugadores[NUM_PLAYERS]) {
    for (int i = 0; i < NUM_PLAYERS; i++) {
        jugadores[i].simbolo = simbolos_visual[i];
        jugadores[i].color = colores_jugadores[i];
        jugadores[i].victorias = estado->victorias[i];
    }
}

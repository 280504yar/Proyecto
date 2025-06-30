#include "logica.h"
#include "visual.h" // Para Simbolo y Color
#include <stdbool.h>

// Mapeo entre SimboloJugador y Simbolo (visual.h)
static const Simbolo simbolos_visual[JUGADORES] = {
    SIM_X,       // JUGADOR_X
    SIM_CIRCULO, // JUGADOR_O
    SIM_TRIANGULO, // JUGADOR_TRIANGULO
    SIM_CUADRADO   // JUGADOR_CUADRADO
};

// Colores para cada jugador (compatibilidad con visual.c)
static const Color colores_jugadores[JUGADORES] = {
    RED,    // JUGADOR_X
    BLUE,   // JUGADOR_O
    GREEN,  // JUGADOR_TRIANGULO
    YELLOW  // JUGADOR_CUADRADO
};

// Inicializa el estado del juego
void iniciar_juego(EstadoJuego *estado) {
    // Limpiar tablero
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            estado->tablero[i][j] = VACIO;
        }
    }
    
    estado->jugador_actual = 0;
    estado->juego_terminado = false;
    estado->ganador = -1;
}

// Maneja una jugada en la posición (fila, columna)
void manejar_jugada(EstadoJuego *estado, int fila, int columna) {
    // Validar posición
    if (fila < 0 || fila >= FILAS || columna < 0 || columna >= COLUMNAS) return;
    
    // Solo permitir jugada si la celda está vacía y el juego no ha terminado
    if (estado->tablero[fila][columna] == VACIO && !estado->juego_terminado) {
        // Registrar jugada
        estado->tablero[fila][columna] = estado->jugador_actual;
        
        // Verificar victoria
        if (hay_ganador(estado, fila, columna)) {
            estado->juego_terminado = true;
            estado->ganador = estado->jugador_actual;
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
    
    // Direcciones: horizontal, vertical, diagonal \, diagonal /
    int direcciones[4][2] = {{0,1}, {1,0}, {1,1}, {1,-1}};
    
    for (int d = 0; d < 4; d++) {
        contador = 1; // La celda actual ya cuenta
        
        // Buscar en dirección positiva
        for (int i = 1; i < 3; i++) {
            int r = fila + i * direcciones[d][0];
            int c = columna + i * direcciones[d][1];
            
            if (r >= 0 && r < FILAS && c >= 0 && c < COLUMNAS && 
                estado->tablero[r][c] == actual) {
                contador++;
            } else break;
        }
        
        // Buscar en dirección negativa
        for (int i = 1; i < 3; i++) {
            int r = fila - i * direcciones[d][0];
            int c = columna - i * direcciones[d][1];
            
            if (r >= 0 && r < FILAS && c >= 0 && c < COLUMNAS && 
                estado->tablero[r][c] == actual) {
                contador++;
            } else break;
        }
        
        // Si encontramos 3 en línea
        if (contador >= 3) return true;
    }
    
    return false;
}

// Verifica si el juego terminó en empate
bool hay_empate(const EstadoJuego *estado) {
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            if (estado->tablero[i][j] == VACIO) {
                return false;
            }
        }
    }
    return true;
}

// Cambia al siguiente jugador
void siguiente_jugador(EstadoJuego *estado) {
    estado->jugador_actual = (estado->jugador_actual + 1) % JUGADORES;
}

// Función de compatibilidad para visual.c (convierte EstadoJuego a Jugador[])
void obtener_info_jugadores(const EstadoJuego *estado, Jugador jugadores[JUGADORES]) {
    for (int i = 0; i < JUGADORES; i++) {
        jugadores[i].simbolo = simbolos_visual[i];
        jugadores[i].color = colores_jugadores[i];
        jugadores[i].victorias = (estado->ganador == i) ? 1 : 0;
    }
}

#include "visual.h"
#include "logica.h"
#include <stdio.h>
#include <stdbool.h>

int main(void) {
    // Inicializar estado del juego
    EstadoJuego juego;
    iniciar_juego(&juego);
    
    // Inicializar ventana gráfica
    ejecutar_ventana(ANCHO, ALTO);
    
    // Área del botón de reinicio
    dibujar_reset();
    
    // Bucle principal del juego
    while (!WindowShouldClose()) {
        // Procesar evento de reinicio o de salida
        if (reset_check() == 1) {
            iniciar_juego(&juego);
            reiniciar_temp();
        }
        if (reset_check() == 0) {
	    cerrar_ventana();
	}

        // Solo procesar jugadas si el juego está activo
        if (!juego.juego_terminado) {
            // Manejar temporizador
            if (!temporizador()) {
                siguiente_jugador(&juego);
                reiniciar_temp();
            }
            
            // Procesar clic del mouse
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                Vector2 mousePos = GetMousePosition();
                int fila = (mousePos.y - POS_Y) / TAM_CELDA;
                int columna = (mousePos.x - POS_X) / TAM_CELDA;
                
                if (fila >= 0 && fila < BOARD_SIZE && columna >= 0 && columna < BOARD_SIZE) {
                    manejar_jugada(&juego, fila, columna);
                    reiniciar_temp(); // Resetear tiempo con jugada válida
                }
            }
        }
        
        // --- RENDERIZADO ---
        BeginDrawing();
            ClearBackground((Color){216, 209, 148, 255}); // Fondo amarillo pálido
            
            // Dibujar elementos visuales
            tablero();
            
            // Convertir estado para visualización
            Jugador jugadores_visual[NUM_PLAYERS];
            obtener_info_jugadores(&juego, jugadores_visual);
            victorias(jugadores_visual, NUM_PLAYERS);
            
            dibujar_reset();
            
            // Dibujar símbolos en el tablero
            for (int i = 0; i < BOARD_SIZE; i++) {
                for (int j = 0; j < BOARD_SIZE; j++) {
                    if (juego.tablero[i][j] != VACIO) {
                        Simbolo simbolo = simbolos_visual[juego.tablero[i][j]];
                        Color color = colores_jugadores[juego.tablero[i][j]];
                        dibujar_simbolo(i, j, simbolo, color);
                    }
                }
            }
            
            // Mostrar mensajes de estado
            if (juego.juego_terminado) {
                const char* mensaje;
                Color color;
                
                if (juego.ganador != -1) {
                    mensaje = TextFormat("¡Jugador %d gana!", juego.ganador + 1);
                    color = colores_jugadores[juego.ganador];
                } else {
                    mensaje = "¡Empate!";
                    color = DARKGRAY;
                }
                
                int fontSize = 40;
                int textWidth = MeasureText(mensaje, fontSize);
                DrawText(mensaje, (ANCHO - textWidth)/2, ALTO/2 - 50, fontSize, color);
            }
            
            // Mostrar información de turno
            DrawText(TextFormat("Turno: Jugador %d", juego.jugador_actual + 1), 
                    20, 20, 30, colores_jugadores[juego.jugador_actual]);
            
            DrawText(TextFormat("Tiempo: %.1f", tiempo_restante), 20, 50, 30, DARKGRAY);
        EndDrawing();
    }
    
    // Cerrar ventana al salir
    cerrar_ventana();
    return 0;
}

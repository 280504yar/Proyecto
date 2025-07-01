#include "visual.h"
#include "logica.h"
#include <stdio.h>
#include <stdbool.h>

int main(void) {
    // Inicializar estado del juego
    EstadoJuego juego;
    iniciar_juego(&juego);
    ejecutar_ventana(ANCHO, ALTO);
    dibujar_reset();
    reiniciar_temp();
    
    // Bucle principal del juego
    while (!WindowShouldClose()) {
        // Procesar evento de reinicio o de salida
	int reset_status = reset_check();
	if (reset_status == 1) {
            iniciar_juego(&juego);
            reiniciar_temp();
        } else if (reset_status == 0) {
		break; // Salir del bucle para cerrar la ventana
	}

        // Solo procesar jugadas si el juego está activo
        if (!juego.juego_terminado) {
		// Manejar clics del ratón en el tablero
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                Vector2 mousePos = GetMousePosition();
                // Convertir posición del ratón a coordenadas del tablero
                int columna = (mousePos.x - POS_X) / TAM_CELDA;
                int fila = (mousePos.y - POS_Y) / TAM_CELDA;
                
                // Verificar que el clic fue dentro del tablero
                if (fila >= 0 && fila < BOARD_SIZE && columna >= 0 && columna < BOARD_SIZE) {
                    manejar_jugada(&juego, fila, columna);
                }
            }
            
            // Actualizar temporizador
            if (temporizador() == 0) {
                siguiente_jugador(&juego);
                reiniciar_temp();
            }
        } else {
            // Mostrar mensaje de fin de juego
            const char* mensaje = juego.ganador != -1 ?
                TextFormat("¡Jugador %d gana!", juego.ganador + 1) : "¡Empate!";
            Color color = juego.ganador != -1 ? colores_jugadores[juego.ganador] : DARKGRAY;

            DrawText(mensaje, (ANCHO - MeasureText(mensaje, 40))/2, ALTO/2 - 50, 40, color);
            DrawText("Click para continuar", (ANCHO - MeasureText("Click para continuar", 20))/2, ALTO/2 + 20, 20, color);
  
            // Procesar clic para reiniciar
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                iniciar_juego(&juego);
                reiniciar_temp();
            }
        }

        // --- RENDERIZADO ---
        BeginDrawing();
            ClearBackground((Color){216, 209, 148, 255}); // Fondo amarillo pálido
            
            // Dibujar elementos visuales
            tablero();
	    dibujar_reset();
            
            // Convertir estado para visualización
            Jugador jugadores_visual[NUM_PLAYERS];
            obtener_info_jugadores(&juego, jugadores_visual);
            victorias(jugadores_visual, NUM_PLAYERS);
            
            
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

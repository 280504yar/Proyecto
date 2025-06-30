#include "visual.h"
#include <stdio.h>
#include <time.h>

//Constantes de posición, tamaño y tiempo del programa
#define TAM_CELDA 80
#define POS_X 560
#define POS_Y 0
#define ANCHO 1280
#define ALTO 720
#define FPS 60
#define DURACION_TURNO 20.0f
static float tiempo_restante = DURACION_TURNO;

//------------------------------------------------------------Ejecutar Ventana----------------------------------------------------
void ejecutar_ventana(int ancho, int alto) {
	InitWindow(ancho, alto, "Gato 9x9");
	SetTargetFPS(FPS);
	Color background = {216, 209, 148, 255}; //Color escogido para mejor visualización del juego (Amarillo Pálido)
}
//------------------------------------------------------------Cerrar Ventana-----------------------------------------------------
void cerrar_ventana() {
	CloseWindow();
}
//-----------------------------------------------------------Dibujar Tablero----------------------------------------------------
void tablero() {
	Color lineas = BLACK;
	// Líneas horizontales
	for (int i = 0; i <= 9; i++) {
		DrawLine(
			POS_X,
			POS_Y + i * TAM_CELDA,
			POS_X + 9 * TAM_CELDA,
			POS_Y + i * TAM_CELDA,
			lineas
		);
	}
	// Líneas verticales
	for (int j = 0; j <= 9; j++) {
		DrawLine(
			POS_X + i * TAM_CELDA,
			POS_Y,
			POS_X + i * TAM_CELDA,
			POS_Y + 9 * TAM_CELDA,
			lineas
		);
	}
}
//-----------------------------------------------------------Dibujar Símbolos----------------------------------------------------
void dibujar_simbolo(int fila, int columna, Simbolo simbolo, Color color) {
	// Cálculo de las coordenadas donde se va a dibujar 
	int x = POS_X + columna * TAM_CELDA;  //Lateral izquierda de la celda
	int y = POS_Y + fila * TAM_CELDA;     //Superior de la celda
	int cen_x = x + TAM_CELDA / 2;
	int cen_y = y + TAM_CELDA / 2;
	int borde = TAM_CELDA / 4;           //Este define el tamaño de la figura
	
	// Dibujar el símbolo en la coordenada indicada
	switch (simbolo) {
		case SIM_X: {
			const char *texto = "X";
			int size = 40;
			int ancho_letra = MeasureText(texto, size);
			int alto_letra = size;
			
			// Centro de la celda donde se va a dibujar
			int ubica_x = x + (TAM_CELDA - ancho_letra) / 2;
			int ubica_y = y + (TAM_CELDA - alto_letra) / 2;

			DrawText(texto, ubica_x, ubica_y, size, color);
			break;
		}
		case SIM_CUADRADO: {
			DrawRectangleLines(x + borde, y + borde, TAM_CELDA - 2 * margen, TAM_CELDA - 2 * margen, color);
			break;
		}
		case SIM_CIRCULO: {
			DrawCircleLines(cen_x, cen_y, TAM_CELDA - 2 -margen, color);
			break;
		}
		case SIM_TRIANGULO; {
			// Vértices que forman el triángulo
			Vector2 v1 = {cen_x, y + borde};
			Vector2 v2 = {x + borde, y + TAM_CELDA - borde};
			Vector2 v3 = {x + TAM_CELDA - borde, y + TAM_CELDA - borde};
			DrawTriangleLines(v1, v2, v3, color);
			break;
		}
		default:
			break;
	}	
}
//------------------------------------------------------------Temporizador------------------------------------------------------
int temporizador() {

	if (tiempo_restante > 0.0f) {
		tiempo_reestante -= GetFrameTime();
		if (tiempo_restante < 0.0f) {
			tiempo_restante = 0.0f;
		}
	}
	DrawText(TextFormat("Tiempo: %d", (int)tiempo_restante), 20, 20, 30, DARKGRAY);
	return (tiempo_restante > 0.0f);
}

void reiniciar_temp() {
	tiempo_restante = DURACION_TURNO;
}
//------------------------------------------------------Contador de Victorias--------------------------------------------------	
void victorias(const Jugador jugadores[], int cantidad_jugadores) {
	// Dimensiones del contador (espacio entre cada contador)
	int base_x = 20;
	int base_y = 60;
	int espacio_y = 60;

	for (int i = 0; i < cantidad_jugadores; i++) {
		int posicion_y = base_y + i * espacio_y;

		switch (jugadores[i].simbolo) {
			case SIM_X: {
				DrawText("X", base_x, posicion_y, 30, jugadores[i].color);
				break;
			 }
			case SIM_CUADRADO: {
				DrawRectangleLines(base_x, posicion_y, 30, 30, jugadores[i].color);
			}
			case SIM_CIRCULO: {
				DrawCircleLines(base_x + 15, posicion_y + 15, 15, jugadores[i].color);
			}
			case SIM_TRIANGULO {
				Vector2 v1 = {base_x + 15, posicion_y};
				Vector2 v2 = {base_x, posicion_y + 30};
				Vector2 v3 = {base_x + 30, posicion_y + 30};
				DrawTriangleLines(v1, v2, v3, jugadores[i].color);
				break;
			}

			default:
				break;
		}
		DrawText(TextFormat("Victorias: %d", jugadores[i].victorias), base_x + 50, posicion_y + 5, 20, DARKGRAY);
	}
}
//------------------------------------------------------Dibujar Botón de Reinicio---------------------------------------------------
#define LIGHTGREEN (Color){202, 230, 137, 255}

void dibujar_reset(Rectangle *area) {
	const int ancho = 130;
	const int alto = 40;
	const int margen = 20;

	area->x = margen;
	area->y = 720 - alto - margen;
	area->width = ancho;
	area->height = alto;

	DrawRectangleRec(*area, LIGHTGREEN);
	DrawRectangleLinesEx(*area, 2, DARKGREEN);

	const char *texto = "Reiniciar";
	int textWidth = MeasureText(texto, 20);
	int texto_x = area->x + (ancho - textWidth) / 2;
	int texto_y = area->y + (alto - 20) / 2;

	DrawText(texto, texto_x, texto_y, 20, BLACK);
}	
//-----------------------------------------------------------Presionar reset-------------------------------------------------------
int reset_check(Rectangle boton) {
	Vector2 pos_mouse = GetMousePosition();

	if (CheckCollisionPointRec(pos_mouse, boton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
		return 1;
	}
	return 0;
}


#ifndef LOGICA_JUEGO_H
#define LOGICA_JUEGO_H

bool* detectar_combinaciones(const unsigned char* tablero, int filas, int cols, bool& hay_combinacion);
int eliminar_fichas_marcadas(unsigned char* tablero, const bool* marcas, int filas, int cols);
void aplicar_gravedad(unsigned char* tablero, int filas, int cols);
void rellenar_espacios_superiores(unsigned char* tablero, int filas, int cols);


void procesar_cascadas(unsigned char* tablero, int filas, int cols, int& total_fichas_eliminadas, int& combinaciones_detectadas, int& cascadas_jugada_actual, int& puntuacion);

void eliminar_ficha_usuario(unsigned char* tablero, int fila, int col, int cols,int& elim_usuario, int& total_fichas_eliminadas, int& puntuacion);
void pausa_visual();

#endif
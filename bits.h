#ifndef BITS_H
#define BITS_H

const unsigned char CODIGOS_FICHAS[6] = {1, 2, 3, 4, 5, 6};

int calcular_bytes_necesarios(int filas, int cols);
void guardar_ficha_en_bits(unsigned char* tablero, int fila, int col, int num_cols, unsigned char valor_ficha);
unsigned char obtener_ficha(const unsigned char* tablero, int fila, int col, int num_cols);
void generar_tablero_aleatorio(unsigned char* tablero, int filas, int cols);

#endif
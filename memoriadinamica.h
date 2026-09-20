#ifndef MEMORIADINAMICA_H
#define MEMORIADINAMICA_H

unsigned char* reasignar_agregar_fila(unsigned char* tablero, int& filas, int cols, int pos_f);
unsigned char* reasignar_eliminar_fila(unsigned char* tablero, int& filas, int cols, int pos_f);
unsigned char* reasignar_agregar_columna(unsigned char* tablero, int filas, int& cols, int pos_c);
unsigned char* reasignar_eliminar_columna(unsigned char* tablero, int filas, int& cols, int pos_c);

#endif
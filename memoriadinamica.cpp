#include "memoriadinamica.h"
#include <cstdlib>
#include "bits.h"

unsigned char* reasignar_agregar_fila(unsigned char* tablero, int& filas, int cols, int pos_f) {
    if (pos_f < 0 || pos_f > filas) return tablero;

    int nuevas_filas = filas + 1;
    int nuevos_bytes = calcular_bytes_necesarios(nuevas_filas, cols);
    unsigned char* tablero_nuevo = new unsigned char[nuevos_bytes]();

    for (int f = 0; f < nuevas_filas; ++f) {
        for (int c = 0; c < cols; ++c) {
            if (f < pos_f) {
                unsigned char val = obtener_ficha(tablero, f, c, cols);
                guardar_ficha_en_bits(tablero_nuevo, f, c, cols, val);
            } else if (f == pos_f) {
                unsigned char nueva_val = CODIGOS_FICHAS[rand() % 6];
                guardar_ficha_en_bits(tablero_nuevo, f, c, cols, nueva_val);
            } else {
                unsigned char val = obtener_ficha(tablero, f - 1, c, cols);
                guardar_ficha_en_bits(tablero_nuevo, f, c, cols, val);
            }
        }
    }

    delete[] tablero;
    filas = nuevas_filas;
    return tablero_nuevo;
}

unsigned char* reasignar_eliminar_fila(unsigned char* tablero, int& filas, int cols, int pos_f) {
    if (filas <= 1 || pos_f < 0 || pos_f >= filas) return tablero;

    int nuevas_filas = filas - 1;
    int bytes_actuales = calcular_bytes_necesarios(filas, cols);
    int bits_utilizados_nuevos = nuevas_filas * cols * 3;
    int bits_capacidad_actual = bytes_actuales * 8;

    bool reasignar = ((float)bits_utilizados_nuevos / bits_capacidad_actual) < 0.65f;
    int nuevos_bytes = reasignar ? calcular_bytes_necesarios(nuevas_filas, cols) : bytes_actuales;

    unsigned char* tablero_nuevo = new unsigned char[nuevos_bytes]();

    for (int f = 0; f < filas; ++f) {
        if (f == pos_f) continue;
        int f_destino = (f < pos_f) ? f : f - 1;
        for (int c = 0; c < cols; ++c) {
            unsigned char val = obtener_ficha(tablero, f, c, cols);
            guardar_ficha_en_bits(tablero_nuevo, f_destino, c, cols, val);
        }
    }

    delete[] tablero;
    filas = nuevas_filas;
    return tablero_nuevo;
}

unsigned char* reasignar_agregar_columna(unsigned char* tablero, int filas, int& cols, int pos_c) {
    if (pos_c < 0 || pos_c > cols) return tablero;

    int nuevas_cols = cols + 1;
    int nuevos_bytes = calcular_bytes_necesarios(filas, nuevas_cols);
    unsigned char* tablero_nuevo = new unsigned char[nuevos_bytes]();

    for (int f = 0; f < filas; ++f) {
        for (int c = 0; c < nuevas_cols; ++c) {
            if (c < pos_c) {
                unsigned char val = obtener_ficha(tablero, f, c, cols);
                guardar_ficha_en_bits(tablero_nuevo, f, c, nuevas_cols, val);
            } else if (c == pos_c) {
                unsigned char nueva_val = CODIGOS_FICHAS[rand() % 6];
                guardar_ficha_en_bits(tablero_nuevo, f, c, nuevas_cols, nueva_val);
            } else {
                unsigned char val = obtener_ficha(tablero, f, c - 1, cols);
                guardar_ficha_en_bits(tablero_nuevo, f, c, nuevas_cols, val);
            }
        }
    }

    delete[] tablero;
    cols = nuevas_cols;
    return tablero_nuevo;
}

unsigned char* reasignar_eliminar_columna(unsigned char* tablero, int filas, int& cols, int pos_c) {
    if (cols <= 1 || pos_c < 0 || pos_c >= cols) return tablero;

    int nuevas_cols = cols - 1;
    int bytes_actuales = calcular_bytes_necesarios(filas, cols);
    int bits_utilizados_nuevos = filas * nuevas_cols * 3;
    int bits_capacidad_actual = bytes_actuales * 8;

    bool reasignar = ((float)bits_utilizados_nuevos / bits_capacidad_actual) < 0.65f;
    int nuevos_bytes = reasignar ? calcular_bytes_necesarios(filas, nuevas_cols) : bytes_actuales;

    unsigned char* tablero_nuevo = new unsigned char[nuevos_bytes]();

    for (int f = 0; f < filas; ++f) {
        for (int c = 0; c < cols; ++c) {
            if (c == pos_c) continue;
            int c_destino = (c < pos_c) ? c : c - 1;
            unsigned char val = obtener_ficha(tablero, f, c, cols);
            guardar_ficha_en_bits(tablero_nuevo, f, c_destino, nuevas_cols, val);
        }
    }

    delete[] tablero;
    cols = nuevas_cols;
    return tablero_nuevo;
}
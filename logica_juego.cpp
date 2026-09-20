#include <iostream>
#include <cstdlib>
#include "logica_juego.h"
#include "bits.h"
#include "interfaz.h"

using namespace std;

void pausa_visual()
{
    cout << "\nPresione ENTER para continuar..." << flush;

    cin.ignore(1000, '\n');
    cin.get();
}

bool* detectar_combinaciones(const unsigned char* tablero, int filas, int cols, bool& hay_combinacion) {
    int total = filas * cols;
    bool* marcas = new bool[total]();
    hay_combinacion = false;

    //Horizontal
    if (cols >= 3) {
        for (int f = 0; f < filas; ++f) {
            for (int c = 0; c <= cols - 3; ++c) {
                unsigned char f1 = obtener_ficha(tablero, f, c, cols);
                unsigned char f2 = obtener_ficha(tablero, f, c + 1, cols);
                unsigned char f3 = obtener_ficha(tablero, f, c + 2, cols);

                if (f1 != 0 && f1 == f2 && f2 == f3) {
                    marcas[f * cols + c] = true;
                    marcas[f * cols + (c + 1)] = true;
                    marcas[f * cols + (c + 2)] = true;
                    hay_combinacion = true;
                }
            }
        }
    }

    //Vertical
    if (filas >= 3) {
        for (int f = 0; f <= filas - 3; ++f) {
            for (int c = 0; c < cols; ++c) {
                unsigned char f1 = obtener_ficha(tablero, f, c, cols);
                unsigned char f2 = obtener_ficha(tablero, f + 1, c, cols);
                unsigned char f3 = obtener_ficha(tablero, f + 2, c, cols);

                if (f1 != 0 && f1 == f2 && f2 == f3) {
                    marcas[f * cols + c] = true;
                    marcas[(f + 1) * cols + c] = true;
                    marcas[(f + 2) * cols + c] = true;
                    hay_combinacion = true;
                }
            }
        }
    }

    return marcas;
}

int eliminar_fichas_marcadas(unsigned char* tablero, const bool* marcas, int filas, int cols) {
    int eliminadas = 0;
    for (int f = 0; f < filas; ++f) {
        for (int c = 0; c < cols; ++c) {
            if (marcas[f * cols + c]) {
                guardar_ficha_en_bits(tablero, f, c, cols, 0);
                eliminadas++;
            }
        }
    }
    return eliminadas;
}

void aplicar_gravedad(unsigned char* tablero, int filas, int cols) {
    for (int c = 0; c < cols; ++c) {
        for (int f = filas - 1; f >= 0; --f) {
            if (obtener_ficha(tablero, f, c, cols) == 0) {
                for (int k = f - 1; k >= 0; --k) {
                    unsigned char arriba = obtener_ficha(tablero, k, c, cols);
                    if (arriba != 0) {
                        guardar_ficha_en_bits(tablero, f, c, cols, arriba);
                        guardar_ficha_en_bits(tablero, k, c, cols, 0);
                        break;
                    }
                }
            }
        }
    }
}

void rellenar_espacios_superiores(unsigned char* tablero, int filas, int cols) {
    for (int f = 0; f < filas; ++f) {
        for (int c = 0; c < cols; ++c) {
            if (obtener_ficha(tablero, f, c, cols) == 0) {
                unsigned char nueva = CODIGOS_FICHAS[rand() % 6];
                guardar_ficha_en_bits(tablero, f, c, cols, nueva);
            }
        }
    }
}

void eliminar_ficha_usuario(unsigned char* tablero, int fila, int col, int cols,
                            int& elim_usuario,
                            int& total_fichas_eliminadas,
                            int& puntuacion) {

    unsigned char ficha_actual = obtener_ficha(tablero, fila, col, cols);

    if (ficha_actual != 0) {
        guardar_ficha_en_bits(tablero, fila, col, cols, 0);
        elim_usuario++;
        total_fichas_eliminadas++;
        puntuacion += 10; // +10 pts seleccion manual
    }
}


void procesar_cascadas(unsigned char* tablero, int filas, int cols,
                       int& total_fichas_eliminadas,
                       int& combinaciones_detectadas,
                       int& cascadas_jugada_actual,
                       int& puntuacion)
{

    bool hay_combinacion = false;


    do
    {


        hay_combinacion = false;


        bool* marcas = detectar_combinaciones(
            tablero,
            filas,
            cols,
            hay_combinacion
            );


        if(hay_combinacion)
        {

            cascadas_jugada_actual++;


            cout << "\n====================================\n";
            cout << ">>> CASCADA "
                 << cascadas_jugada_actual
                 << " GENERADA <<<\n";
            cout << "====================================\n";


            int eliminadas = eliminar_fichas_marcadas(
                tablero,
                marcas,
                filas,
                cols
                );


            cout << "\n--- TABLERO DESPUES DE ELIMINAR ---\n";


            mostrar_tablero_fichas(
                tablero,
                filas,
                cols
                );


            mostrar_trama_binaria(
                tablero,
                filas,
                cols
                );


            cout << "\nFichas eliminadas: "
                 << eliminadas
                 << "\n";


            total_fichas_eliminadas += eliminadas;

            combinaciones_detectadas++;

            puntuacion += eliminadas * 15;


            pausa_visual();



            cout << "\n--- APLICANDO GRAVEDAD ---\n";


            aplicar_gravedad(
                tablero,
                filas,
                cols
                );


            mostrar_tablero_fichas(
                tablero,
                filas,
                cols
                );


            mostrar_trama_binaria(
                tablero,
                filas,
                cols
                );


            pausa_visual();



            cout << "\n--- RELLENANDO ESPACIOS VACIOS ---\n";


            rellenar_espacios_superiores(
                tablero,
                filas,
                cols
                );


            mostrar_tablero_fichas(
                tablero,
                filas,
                cols
                );


            mostrar_trama_binaria(
                tablero,
                filas,
                cols
                );


            pausa_visual();


        }


        delete[] marcas;


    }while(hay_combinacion);

}
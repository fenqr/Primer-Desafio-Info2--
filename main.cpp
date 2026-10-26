#include <iostream>
#include <cstdlib>
#include <ctime>

#include "bits.h"
#include "interfaz.h"
#include "logica_juego.h"
#include "memoriadinamica.h"

using namespace std;

void limpiar_pantalla() {
    cout << "\033[2J\033[1;1H" << flush;
}

void mostrar_estado_juego(int filas, int cols,
                          int elim_usuario,
                          int total_fichas_eliminadas,
                          int combinaciones_detectadas,
                          int cascadas_jugada_actual,
                          int puntuacion) {
    cout << "\n========================================\n";
    cout << "           ESTADO DEL JUEGO             \n";
    cout << "========================================\n";
    cout << "* Dimensiones actuales del tablero: " << filas << "x" << cols << "\n";
    cout << "* Cantidad de eliminaciones del usuario: " << elim_usuario << "\n";
    cout << "* Total de fichas eliminadas: " << total_fichas_eliminadas << "\n";
    cout << "* Combinaciones detectadas: " << combinaciones_detectadas << "\n";
    cout << "* Cascadas producidas en esta jugada: " << cascadas_jugada_actual << "\n";
    cout << "----------------------------------------\n";
    cout << " REGLAS DE PUNTUACION:                   \n";
    cout << "  - Ficha seleccionada (Manual) : +10 pts\n";
    cout << "  - Ficha por Cascada/3+        : +15 pts\n";
    cout << "----------------------------------------\n";
    cout << "* PUNTUACION TOTAL OBTENIDA: " << puntuacion << " pts\n";
    cout << "========================================\n" << flush;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    srand(time(nullptr));

    int filas, cols;

    cout << "BIENVENIDO A SWEET CRUSH\n" << flush;
    cout << "Filas: " << flush;
    cin >> filas;
    cout << "Columnas: " << flush;
    cin >> cols;

    if (filas <= 0 || cols <= 0) return 1;

    int bytes_necesarios = calcular_bytes_necesarios(filas, cols);
    unsigned char* tablero = new unsigned char[bytes_necesarios]();
    generar_tablero_aleatorio(tablero, filas, cols);

    int elim_usuario = 0;
    int total_fichas_eliminadas = 0;
    int combinaciones_detectadas = 0;
    int cascadas_jugada_actual = 0;
    int puntuacion = 0;

    int jugando = 1;
    int movimientos = 0;

    while (jugando)
    {
        limpiar_pantalla();

        cout << "====================\n" << flush;
        mostrar_tablero_fichas(tablero, filas, cols);
        mostrar_trama_binaria(tablero, filas, cols);

        cout << "\nMovimiento numero: " << movimientos << "\n" << flush;

        int fila, columna;
        cout << "\n--- SELECCIONAR FICHA A ELIMINAR ---\n" << flush;
        cout << "Ingrese fila de la ficha: " << flush;
        if (!(cin >> fila)) {
            cin.clear(); cin.ignore(1000, '\n');
            cout << "Entrada invalida\n" << flush;
            continue;
        }
        cout << "Ingrese columna de la ficha: " << flush;
        if (!(cin >> columna)) {
            cin.clear(); cin.ignore(1000, '\n');
            cout << "Entrada invalida\n" << flush;
            continue;
        }

        if (fila < 0 || fila >= filas || columna < 0 || columna >= cols)
        {
            cout << "Posicion invalida\n" << flush;
            continue;
        }

        cascadas_jugada_actual = 0;

        cout << "\nANTES DE ELIMINAR\n";

        eliminar_ficha_usuario(tablero, fila, columna, cols, elim_usuario, total_fichas_eliminadas, puntuacion);

        cout << "\nDESPUES DE ELIMINAR\n";

        cout << "\n--- TABLERO DESPUES DE ELIMINAR FICHA ---\n";

        mostrar_tablero_fichas(tablero, filas, cols);
        mostrar_trama_binaria(tablero, filas, cols);

        pausa_visual();

        cout << "\n--- APLICANDO GRAVEDAD ---\n";

        aplicar_gravedad(tablero, filas, cols);

        mostrar_tablero_fichas(tablero, filas, cols);
        mostrar_trama_binaria(tablero, filas, cols);

        pausa_visual();

        cout << "\n--- RELLENANDO ESPACIOS VACIOS ---\n";

        rellenar_espacios_superiores(tablero, filas, cols);

        mostrar_tablero_fichas(tablero, filas, cols);
        mostrar_trama_binaria(tablero, filas, cols);

        pausa_visual();

        procesar_cascadas(tablero, filas, cols, total_fichas_eliminadas, combinaciones_detectadas, cascadas_jugada_actual, puntuacion);

        cout << "\nFIN DE CASCADAS\n";

        movimientos++;

        int opcion_mod = 0;
        do {
            cout << "\n----------------------------------------\n";
            cout << "MODIFICACION DE DIMENSIONES DEL TABLERO\n";
            cout << "1. Agregar fila\n";
            cout << "2. Eliminar fila\n";
            cout << "3. Agregar columna\n";
            cout << "4. Eliminar columna\n";
            cout << "5. Continuar jugando sin modificar estructura\n";
            cout << "Seleccione una opcion: " << flush;

            if (!(cin >> opcion_mod)) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Entrada invalida. Por favor ingrese un numero del 1 al 5.\n" << flush;
                continue;
            }

            int pos = 0;
            bool modificacion_realizada = false;

            if (opcion_mod == 1) {
                cout << "Ingrese la posicion de la nueva fila (0 a " << filas << "): " << flush;
                if (cin >> pos && pos >= 0 && pos <= filas) {
                    tablero = reasignar_agregar_fila(tablero, filas, cols, pos);
                    modificacion_realizada = true;
                } else {
                    cout << "Posicion fuera de rango o invalida.\n" << flush;
                    cin.clear(); cin.ignore(1000, '\n');
                }
            } else if (opcion_mod == 2) {
                if (filas <= 1) {
                    cout << "No se puede eliminar mas filas. Limite minimo alcanzado.\n" << flush;
                } else {
                    cout << "Ingrese el indice de la fila a eliminar (0 a " << filas - 1 << "): " << flush;
                    if (cin >> pos && pos >= 0 && pos < filas) {
                        tablero = reasignar_eliminar_fila(tablero, filas, cols, pos);
                        modificacion_realizada = true;
                    } else {
                        cout << "Indice fuera de rango o invalido.\n" << flush;
                        cin.clear(); cin.ignore(1000, '\n');
                    }
                }
            } else if (opcion_mod == 3) {
                cout << "Ingrese la posicion de la nueva columna (0 a " << cols << "): " << flush;
                if (cin >> pos && pos >= 0 && pos <= cols) {
                    tablero = reasignar_agregar_columna(tablero, filas, cols, pos);
                    modificacion_realizada = true;
                } else {
                    cout << "Posicion fuera de rango o invalida.\n" << flush;
                    cin.clear(); cin.ignore(1000, '\n');
                }
            } else if (opcion_mod == 4) {
                if (cols <= 1) {
                    cout << "No se puede eliminar mas columnas. Limite minimo alcanzado.\n" << flush;
                } else {
                    cout << "Ingrese el indice de la columna a eliminar (0 a " << cols - 1 << "): " << flush;
                    if (cin >> pos && pos >= 0 && pos < cols) {
                        tablero = reasignar_eliminar_columna(tablero, filas, cols, pos);
                        modificacion_realizada = true;
                    } else {
                        cout << "Indice fuera de rango o invalido.\n" << flush;
                        cin.clear(); cin.ignore(1000, '\n');
                    }
                }
            } else if (opcion_mod != 5) {
                cout << "Opcion invalida.\n" << flush;
            }

            if (modificacion_realizada) {
                cout << "\n--- TABLERO TRAS LA MODIFICACION ESTRUCTURAL ---\n" << flush;
                mostrar_tablero_fichas(tablero, filas, cols);
                mostrar_trama_binaria(tablero, filas, cols);
                cascadas_jugada_actual = 0;

                procesar_cascadas(tablero, filas, cols, total_fichas_eliminadas, combinaciones_detectadas, cascadas_jugada_actual, puntuacion);

                cout << "\n--- TABLERO DESPUES DE RESOLVER CASCADAS ---\n";
                mostrar_tablero_fichas(tablero, filas, cols);
                mostrar_trama_binaria(tablero, filas, cols);
            }

        } while (opcion_mod != 5);

        mostrar_estado_juego(filas, cols, elim_usuario, total_fichas_eliminadas, combinaciones_detectadas, cascadas_jugada_actual, puntuacion);

        do {
            cout << "\n¿Desea continuar jugando? 1-Si 0-No: " << flush;
            if (!(cin >> jugando)) {
                cin.clear(); cin.ignore(1000, '\n');
                jugando = -1;
            }

            if (jugando != 0 && jugando != 1) {
                cout << "Opcion invalida. Por favor ingrese 1 para Si o 0 para No.\n" << flush;
            }
        } while (jugando != 0 && jugando != 1);
    }

    delete[] tablero;
    tablero = nullptr;

    return 0;
}

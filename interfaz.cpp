#include <iostream>
#include "interfaz.h"
#include "bits.h"

using namespace std;

char convertir_codigo_a_caracter(unsigned char codigo) {
    switch (codigo) {
    case 0: return ' ';
    case 1: return 'A';
    case 2: return 'B';
    case 3: return 'C';
    case 4: return 'D';
    case 5: return 'E';
    case 6: return 'F';
    default: return '?';
    }
}

void mostrar_tablero_fichas(const unsigned char* tablero, int filas, int cols) {

    cout << "\n\nTABLERO JUEGO\n\n";

    cout << "    ";
    for(int c=0;c<cols;c++)
        cout << c << "   ";

    cout << "\n";

    for(int f=0;f<filas;f++)
    {
        cout << f << " | ";

        for(int c=0;c<cols;c++)
        {
            unsigned char cod =
                obtener_ficha(tablero,f,c,cols);

            cout
                << convertir_codigo_a_caracter(cod)
                << " | ";
        }

        cout << "\n";
    }
}

void mostrar_trama_binaria(
    const unsigned char* tablero,
    int filas,
    int cols)
{

    int total_bytes =
        calcular_bytes_necesarios(filas,cols);


    cout << "\n\nTABLERO BINARIO\n\n";


    cout << "    ";

    for(int c=0;c<cols;c++)
        cout << "    ";


    cout << "\n";


    for(int f=0;f<filas;f++)
    {

        cout << f << " | ";

        for(int c=0;c<cols;c++)
        {

            unsigned char cod =
                obtener_ficha(tablero,f,c,cols);


            cout
                << ((cod>>2)&1)
                << ((cod>>1)&1)
                << (cod&1)
                << "| ";

        }

        cout<<"\n";
    }


    cout<<"\nBytes utilizados: "
         <<total_bytes
         <<"\n";
}
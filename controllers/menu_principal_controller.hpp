#include <iostream>
#include <conio.h>
#include "new_sheet_controller.hpp"
#include "open_sheet_controller.hpp"

using namespace std;

void menu_principal(int menuoption)
{
    int options = 0;
    char opc;

    do
    {
        cout << "\nMenu principal\n"
                "--------------\n"
                "1. Nueva hoja de calculo\n"
                "2. Abrir hoja de calculo\n"
                "3. Salir\n\n";

        cout << "Ingrese una opcion: ";
        cin >> menuoption;

        // validamos que el usuario ingrese un dato numérico
        if (cin.fail())
        {
            // llamamos a la función que limpia el estado de error y vacia completamente el buffer
            validate_cin();
        }
        else
        {
            switch (menuoption)
            {
            case 1:
                menu_matriz(options); // Llama función que gestiona menú de matriz
                break;
            case 2:
                menu_archivos();
                break;
            case 3:
                cout << "Gracias por utilizar el programa :)";
                break;
            default:
                cout << "\nOpcion invalida. Intente de nuevo.\n\n";
                imprimir_mensaje_confirmacion();
                opc = getche();
                break;
            }
        }
    } while (menuoption != 3);
}
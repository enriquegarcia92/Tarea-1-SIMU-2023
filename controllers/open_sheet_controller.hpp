#include <iostream>
#include <conio.h>
#include <algorithm>
#include <string>
#include "../utils/JSON.hpp"

using namespace std;
using JSON = dnc::JSON;

int index_archivo = 0;

// Prototipos de funciones

void menu_archivos()
{
    do
    {
        // validamos si ya existe alguna hoja de calculo guardada previamente
        if (contar_archivos() > 0)
        {
            // creamos la lista donde se almacenara el nombre de los archivos guardados
            File *file_list = NULL;

            // llenamos la lista con los nombres de los archivos
            recuperar_archivos(file_list);

            // imprimimos en pantalla el nombre de los archivos
            cout << "\n------------------------------------\n";
            cout << "ARCHIVOS GUARDADOS: \n";
            imprimir_nombre_archivos(file_list);
            cout << "0. Regresar\n";
            cout << "------------------------------------\n";

            cout << "\nDigite el numero del archivo que desea abrir: ";
            cin >> index_archivo;

            // validamos que el usuario ingrese un dato numérico
            if (cin.fail())
            {
                // llamamos a la función que limpia el estado de error y vacia completamente el buffer
                validate_cin();
                index_archivo = 1;
            }
            else
            {
                if (index_archivo != 0)
                {
                    string file_name = extraer_nombre_archivo(file_list, index_archivo);

                    if (file_name != "")
                    {
                        JSON obj;

                        obj.parseFromFile("files/" + file_name);

                        string fila;

                        string fila_formateada;

                        int iterador_fila_formateada = 0;

                        // Obtenemos el numero de columnas de cada fila

                        // Obtenemos el primer arreglo del json
                        string objeto_inicial = (obj.begin())->toString();

                        // variable que nos servirá para obtener la cantidad de elementos de cada fila
                        int contador_columnas = 0;

                        for (int i = 0; i < objeto_inicial.length(); i++)
                        {
                            // encontramos la cantidad de "comas" en el arreglo
                            // la cantidad de elementos será cantidad_de_comas + 1
                            if (objeto_inicial[i] == ',')
                                contador_columnas++;
                        }

                        contador_columnas += 1;

                        // obtenemos la cantidad de filas del archivo
                        int contador_filas = 0;

                        for (auto it = obj.begin(); it != obj.end(); ++it)
                        {
                            contador_filas++;
                        }

                        // creamos la hoja de calculo a partir de los datos recuperados
                        MainListNode *mainList = NULL;

                        const int ASCII_CODE_LETTER_A = 65;

                        crear_hoja_calculo(mainList, contador_filas + 1, contador_columnas + 1, ASCII_CODE_LETTER_A);

                        int actual_row = 1;
                        string valores[num_columns];

                        for (auto it = obj.begin(); it != obj.end(); ++it)
                        {
                            // it.key() devuelve la clave del valor actual del iterador.
                            fila = it->toString();

                            for (int i = 0; i < fila.length(); i++)
                            {
                                if (fila[i] == '[' || fila[i] == ']' || fila[i] == 32)
                                {
                                    fila.erase(i, 1);
                                }
                            }

                            for (int j = 0; j <= contador_columnas; j++)
                            {
                                escribir_contenido(mainList, actual_row, j, "hola");
                            }

                            actual_row++;
                        }

                        cout << contador_columnas << endl;
                        menu_matriz_open_sheet(mainList, 0, contador_filas + 1, contador_columnas);
                    }
                    else
                    {
                        cout << "Ocurrio un error al intentar abrir el archivo\n";
                        imprimir_mensaje_confirmacion();
                        opc = getche();
                    }
                }
            }
        }
        else
        {
            cout << "No se encontro ningun archivo\n";
            index_archivo = 0;
            imprimir_mensaje_confirmacion();
            opc = getche();
        }
    } while (index_archivo != 0);
}

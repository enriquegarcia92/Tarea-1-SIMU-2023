#include <iostream>
#include <conio.h>
#include <string>
#include "../services/matrix_service.hpp"
#include "../utils/JSON.hpp"

using namespace std;
using JSON = dnc::JSON;

/* --------------------------------
------------ CONSTANTES -----------
-----------------------------------
*/

// constante que nos servirá para almacenar el código ASCII de la primera letra de los encabezados (en este caso, la letra "A")
const int ASCII_CODE_LETTER_A = 65;

// constante que nos servirá para almacenar el número máximo de filas que puede tener la hoja de cálculo
const int MAX_NUM_ROWS = 16;

// constante que nos servirá para almacenar el número máximo de filas que puede tener la hoja de cálculo
const int MAX_NUM_COLUMNS = 16;

/* --------------------------------
------------- VARIABLES -----------
-----------------------------------
*/

// variable que nos servirá para almacenar el número de filas que tiene la hoja de cálculo
int num_rows = 6;
// variable que nos servirá para almacenar el número de columnas que tiene la hoja de cálculo
int num_columns = 5;
// variable que nos servirá para almacenar el índice de la fila en la que se encuentra el usuario
int index_actual_row = 1;
// variable que nos servirá para almacenar el índice de la columna en la que se encuentra el usuario
int index_actual_col = 1;
// variable que nos servirá para almacenar el texto que un usuario desee copiar/cortar de una celda
string cellcopy = "";
// variable que nos servirá para almacenar la columna a la que se quiere desplazar el usuario
char colLetter = 'A';

// variable de tipo JSON que nos servirá para exportar la hoja de cálculo a un archivo
JSON obj = JSON::Object();
// variable auxiliar que nos servirá para crear el objeto JSON
string cadena = "{";
// variable que almacena el nombre del archivo que se desea exportar
string filename;
// variable auxiliar para realizar una pausa en el programa
char opc;

// Puntero que será la cabeza de la lista principal
MainListNode *mainList = NULL;

// Prototipo de funciones
void insertar_contenido();
void saltar_celda();
void copiar();
void cortar();
void pegar();
void mover_izquierda();
void mover_derecha();
void mover_arriba();
void mover_abajo();
void guardar();
void limpiar_spreadsheet();

void menu_matriz(int options)
{
    // creamos la hoja de cálculo
    crear_hoja_calculo(mainList, num_rows, num_columns, ASCII_CODE_LETTER_A);

    num_rows = contar_filas(mainList);
    num_columns = contar_columnas(mainList->row);

    while (options != 11)
    {
        imprimir_hoja_calculo(mainList, num_rows, num_columns, index_actual_row, index_actual_col);

        cout << "\nOpciones\n"
                "---------------------------\n"
                "1. Ingresar contenido\n"
                "2. Saltar a celda\n"
                "3. Copiar\n"
                "4. Cortar\n"
                "5. Pegar\n"
                "6. Mover a la izquierda\n"
                "7. Mover a la derecha\n"
                "8. Moverse arriba\n"
                "9. Moverse abajo\n"
                "10. Guardar\n"
                "11. Salir\n\n"
                "Digite el numero de la opcion que desea ejecutar: ";

        cin >> options;

        // validamos que el usuario ingrese un dato numérico
        if (cin.fail())
        {
            // llamamos a la función que limpia el estado de error y vacia completamente el buffer
            validate_cin();
        }
        else
        {
            switch (options)
            {
            case 1:
                insertar_contenido();
                break;
            case 2:
                saltar_celda();
                break;
            case 3:
                copiar();
                break;
            case 4:
                cortar();
                break;
            case 5:
                pegar();
                break;
            case 6:
                mover_izquierda();
                break;
            case 7:
                mover_derecha();
                break;
            case 8:
                mover_arriba();
                break;
            case 9:
                mover_abajo();
                break;
            case 10:
                guardar();
                break;
            case 11:
                limpiar_spreadsheet();
                break;
            default:
                cout << "\nOpcion invalida. Intente de nuevo.\n\n";
                imprimir_mensaje_confirmacion();
                opc = getche();
            }
        }
    }
}

// 1. Función que inserta contenido en una celda
void insertar_contenido()
{
    string value = "";
    bool error = true;

    do
    {
        clean_cin();
        cout << "\nPosicion actual: [" << index_actual_row << "," << colLetter << "]\n";
        cout << "Digite el valor a ingresar en la celda: ";
        getline(cin, value);

        if (value.length() > 8 || has_space(value))
        {
            cout << "\nERROR. Solo es posible escribir una palabra con un maximo de 8 caracteres\n";
            cout << "Presione una tecla para continuar...";
        }
        else
        {
            error = false;
            cout << index_actual_row << "\n";
            cout << index_actual_col << "\n";
            escribir_contenido(mainList, index_actual_row, index_actual_col, value);
        }
    } while (error);
}

// 2. Función para saltar a una celda en específico
void saltar_celda()
{
    int row = 0;
    int col = 0;
    char letter;
    bool error = true;
    bool error_cin = true;
    do
    {
        do
        {
            cout << "\nIngrese el numero de fila (1, 2, 3, 4,...) a la que desea saltar: ";
            cin >> row;

            if (cin.fail())
                // llamamos a la función que limpia el estado de error y vacia completamente el buffer
                validate_cin();
            else
                error_cin = false;
        } while (error_cin);

        error_cin = true;

        do
        {
            cout << "Ingrese la letra de la columna [A, B, C, D,...] a la que desea saltar: ";
            cin >> letter;

            if (cin.fail())
                // llamamos a la función que limpia el estado de error y vacia completamente el buffer
                validate_cin();
            else
                error_cin = false;
        } while (error_cin);

        col = letter_to_number(letter);

        if (row >= MAX_NUM_ROWS || col >= MAX_NUM_COLUMNS || row < 1 || col < 1)
        { // verifica que la entrada no exeda los límites de la tabla
            cout << "\nLa posicion ingresada excede los limites maximos permitidos por la hoja de calculo (15x15)\n";
        }
        else
        {
            if (row >= num_rows)
                for (int i = num_rows; i <= row; i++)
                    agregar_fila(mainList, i, num_columns, ASCII_CODE_LETTER_A);

            if (col >= num_columns)
            {
                MainListNode *auxRow = mainList;
                Cell *auxCell;

                int index_row = 0;
                int index_col = 0;

                while (auxRow != NULL)
                {
                    auxCell = auxRow->row;

                    for (int i = num_columns; i <= col; i++)
                    {
                        agregar_columna(auxCell, index_row, (num_columns + index_col - 1), ASCII_CODE_LETTER_A);
                        index_col++;
                    }

                    index_col = 0;

                    auxRow = auxRow->next;

                    index_row++;
                }

                num_columns = contar_columnas(mainList->row);
            }

            // Modificar el valor de las variables que contienen la localización
            index_actual_row = row;
            index_actual_col = col;
            num_rows = contar_filas(mainList);
            colLetter = letter;
            cout << "\nNueva posicion: [" << index_actual_row << "," << to_string(toupper(colLetter)) << "]\n";
            error = false;
        }
        imprimir_mensaje_confirmacion();
        opc = getche();
    } while (error);
}

// 3. Función para copiar el contenido de una celda
void copiar()
{
    cellcopy = copiar_celda(mainList, index_actual_row, index_actual_col); // Función de copiar recibe la tabla, posición y regresa un int que se guarda en cellcopu
    cout << "\nContendio copiado: " << cellcopy << "\n";
    imprimir_mensaje_confirmacion();
    opc = getche();
}

// 4. Función para cortar el contenido de una celda
void cortar()
{
    cellcopy = cortar_celda(mainList, index_actual_row, index_actual_col); // Función de copiar recibe la tabla, posición y regresa un int que se guarda en cellcopu
    cout << "\nContendio cortado: " << cellcopy << "\n";
    imprimir_mensaje_confirmacion();
    opc = getche();
}

// 5. Función para pegar el contenido copiado en una celda
void pegar()
{
    cout << "\nContenido pegado: " << cellcopy << "\n";
    escribir_contenido(mainList, index_actual_row, index_actual_col, cellcopy);
    imprimir_mensaje_confirmacion();
    opc = getche();
}

// 6. Función para moverse a la izquierda
void mover_izquierda()
{
    int valid_col = index_actual_col;
    valid_col--;

    if (valid_col <= 0 || valid_col >= MAX_NUM_COLUMNS)
    {
        cout << "\nMOVIMIENTO NO PERMITIDO.\n";
        cout << "La posicion a la que desea desplazarse excede los limites de la hoja de calculo (15x15)\n";
    }
    else
    {
        index_actual_col = valid_col;
        colLetter = colLetter - 1;
        cout << "\nNueva posicion: [" << index_actual_row << "," << toupper(colLetter) << "]\n"; // Porción de código que disminuye en 1 las columnas y revisa que no exeda los limites de la tabla
    }
    imprimir_mensaje_confirmacion();
    opc = getche();
}

// 7. Función para moverse a la derecha
void mover_derecha()
{
    int valid_col = index_actual_col;
    valid_col += 1;

    if (valid_col <= 0 || valid_col >= MAX_NUM_COLUMNS)
    {
        cout << "\nMOVIMIENTO NO PERMITIDO.\n";
        cout << "La posicion a la que desea desplazarse excede los limites de la hoja de calculo (15x15)\n";
    }
    else
    {
        // Verificamos si la columna a la que el usuario se desea desplazar ya existe
        if(valid_col >= num_columns)
        {
            // si no existe, agregamos una columna a cada fila
            MainListNode *auxRow = mainList;
            Cell *auxCell = auxRow->row;

            int index_row = 0;

            while (auxRow != NULL)
            {
                auxCell = auxRow->row;

                agregar_columna(auxCell, index_row, index_actual_col, ASCII_CODE_LETTER_A);

                auxRow = auxRow->next;

                index_row++;
            }
        }

        num_columns = contar_columnas(mainList->row);

        cout << num_columns << "\n";

        index_actual_col = valid_col;
        colLetter = colLetter + 1;
        cout << "\nNueva posicion: [" << index_actual_row << "," << toupper(colLetter) << "]\n"; // Porción de código que aumenta en 1 las columnas y revisa que no exeda los limites de la tabla
    }
    imprimir_mensaje_confirmacion();
    opc = getche();
}

// 8. Función para moverse hacia arriba
void mover_arriba()
{
    int valid_row = index_actual_row;
    valid_row--;
    if (valid_row <= 0 || valid_row >= MAX_NUM_ROWS)
    {
        cout << "\nMOVIMIENTO NO PERMITIDO.\n";
        cout << "La posicion a la que desea desplazarse excede los limites de la hoja de calculo (15x15)\n";
    }
    else
    {
        index_actual_row = valid_row;
        cout << "\nNueva posicion: [" << index_actual_row << "," << toupper(colLetter) << "]\n"; // Porción de código que aumenta en 1 las filas y revisa que no exeda los limites de la tabla
    }
    imprimir_mensaje_confirmacion();
    opc = getche();
}

// 9. Función para moverse hacia abajo
void mover_abajo()
{
    int valid_row = index_actual_row;
    valid_row++;

    if (valid_row <= 0 || valid_row >= MAX_NUM_ROWS)
    {
        cout << "\nMOVIMIENTO NO PERMITIDO.\n";
        cout << "La posicion a la que desea desplazarse excede los limites de la hoja de calculo (15x15)\n";
    }
    else
    {
        // verificamos si la fila a la que se desea desplazar el usuario ya existe
        if(valid_row >= num_rows)
            // si no existe, creamos una fila nueva
            agregar_fila(mainList, (index_actual_row + 1), num_columns, ASCII_CODE_LETTER_A);

        // actualizamos el número de filas de la matriz
        num_rows = contar_filas(mainList);
        index_actual_row = valid_row;
        cout << "\nNueva posicion: [" << index_actual_row << "," << toupper(colLetter) << "]\n"; // Porción de código que disminuye en 1 las filas y revisa que no exeda los limites de la tabla
    }
    imprimir_mensaje_confirmacion();
    opc = getche();
}

// 11. Función para eliminar la hoja de cálculo y reiniciar variables
void limpiar_spreadsheet()
{
    // limpiamos la memoria
    vaciar(&mainList);

    // reiniciamos todas las variables
    num_rows = 6;
    num_columns = 5;
    index_actual_row = 1;
    index_actual_col = 1;
    cellcopy = "";
    colLetter = 'A';

    obj = JSON::Object();
    cadena = "{";

}

// 10. Función para guardar el contenido de la hoja de calculo en un archivo JSON
void guardar()
{
    cout << "\nIngrese el nombre del archivo: ";
    cin >> filename;

    MainListNode *auxRow = mainList->next;
    Cell *auxCell;

    for(int i = 1; i < num_rows; i++)
    {
        cadena = cadena + "\"" + to_string(i) + "\":";

        auxCell = auxRow->row->next;

        for(int j = 1; j < num_columns; j++)
        {
            if (j == 1)
                cadena = cadena + " [";

            if (j == num_columns - 1)
            {
                cadena = cadena + "\"" + auxCell->value + "\"]";
            }
            else
            {
                cadena = cadena + "\"" + auxCell->value + "\",";
            }

            auxCell = auxCell->next;
        }

        auxRow = auxRow->next;

        if (i != num_rows - 1)
            cadena = cadena + ", ";
    }

    cadena = cadena + "}";

    if (save_file(cadena, filename + ".json"))
    {
        cout << "\nARCHIVO GUARDADO EXITOSAMENTE\n";
    }
    else
    {
        cout << "\nNo se ha podido guardar el archivo\n";
    }

    cout << "Presione una tecla para continuar...\n";
    opc = getche();

    cadena = "{";
}
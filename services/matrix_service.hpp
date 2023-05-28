#include <iostream>
#include <string>
#include <fstream>
#include "../utils/utils.hpp"

using namespace std;

// Nodo de las celdas de la hoja de cálculo
struct Cell
{
    string value;
    Cell *prev;
    Cell *next;
};

// Nodo de la lista principal que nos permite acceder a las filas
struct MainListNode
{
    Cell *row;
    string value;
    MainListNode *prev;
    MainListNode *next;
};

// Prototipos de funciones
void agregar_fila(MainListNode *&list, int index_row, int num_columns, char ascii_code_first_letter);
void agregar_columna(Cell *&list, int index_row, int index_colum, char ascii_code_first_letter);
void crear_hoja_calculo(MainListNode *&list, int num_rows, int num_columns, char ascii_code_first_letter);
void imprimir_hoja_calculo(MainListNode *&list, int num_rows, int num_columns, int actual_row, int actual_column);
void escribir_contenido(MainListNode *&list, int actual_row, int actual_col, std::string data);
bool save_file(std::string data, std::string filename);

// Función para agregar una nueva fila a la hoja de cálculo
void agregar_fila(MainListNode *&list, int index_row, int num_columns, char ascii_code_first_letter)
{
    MainListNode *new_node = new MainListNode();

    Cell *new_cell = new Cell();

    for (int j = 0; j < num_columns; j++)
        agregar_columna(new_cell, index_row, j, ascii_code_first_letter);

    if (index_row == 0)
        new_node->value = "";
    else
        new_node->value = to_string(index_row);

    new_node->row = new_cell;
    new_node->prev = NULL;
    new_node->next = NULL;

    if (list == NULL)
    {
        list = new_node;
    }
    else
    {
        MainListNode *aux1 = list;
        MainListNode *aux2 = NULL;

        while (aux1 != NULL)
        {
            aux2 = aux1;
            aux1 = aux1->next;
        }

        aux2->next = new_node;
        new_node->prev = aux2;
    }
}

// Función para agregar una nueva columna a la hoja de cálculo
void agregar_columna(Cell *&list, int index_row, int index_colum, char ascii_code_first_letter)
{
    Cell *new_cell = new Cell();

    if (index_row == 0)
        new_cell->value = (int)ascii_code_first_letter + index_colum;
    else
        new_cell->value = "";

    new_cell->prev = NULL;
    new_cell->next = NULL;

    if (list == NULL)
    {
        list = new_cell;
    }
    else
    {
        Cell *aux1 = list;
        Cell *aux2 = NULL;

        while (aux1 != NULL)
        {
            aux2 = aux1;
            aux1 = aux1->next;
        }

        aux2->next = new_cell;
        new_cell->prev = aux2;
    }
}

// Función para crear una nueva hoja de cálculo
void crear_hoja_calculo(MainListNode *&list, int num_rows, int num_columns, char ascii_code_first_letter)
{
    cout << num_columns;

    for (int i = 0; i < num_rows; i++)
        agregar_fila(list, i, num_columns, ascii_code_first_letter);
}

// Función para imprimir la hoja de cálculo
void imprimir_hoja_calculo(MainListNode *&list, int num_rows, int num_columns, int actual_row, int actual_column)
{
    MainListNode *row = list;
    Cell *cell;

    cout << "\n";

    for (int i = 0; i < num_rows; i++)
    {
        cell = row->row;

        for (int j = 0; j < num_columns; j++)
        {
            if (j == 0)
            {
                if (row->value == "")
                {
                    relleno(9);
                    cout << "|";
                }
                else
                {
                    relleno(9 - (row->value).length());
                    cout << row->value << "|";
                }
            }
            else
            {
                if (i == actual_row && j == actual_column)
                {
                    if (cell->value == "")
                    {
                        relleno(4);
                        cout << "_";
                        relleno(4);
                        cout << "|";
                    }
                    else
                    {
                        relleno(9 - (cell->value).length());
                        cout << cell->value << "|";
                    }
                }
                else
                {
                    if (cell->value == "")
                    {
                        relleno(9);
                        cout << "|";
                    }
                    else
                    {
                        relleno(9 - (cell->value).length());
                        cout << cell->value << "|";
                    }
                }
            }
            cell = cell->next;
        }

        row = row->next;
        cout << "\n";

        for (int j = 0; j < num_columns; j++)
            cout << "---------|";

        cout << "\n";
    }
}

// Función para escribir en una celda de la hoja de cálculo
void escribir_contenido(MainListNode *&list, int actual_row, int actual_col, string data)
{
    MainListNode *row = list;
    Cell *cell;

    for (int i = 0; i <= actual_row; i++)
    {
        if (i != actual_row)
        {
            row = row->next;
        }
        else
        {
            cell = row->row;

            for (int j = 0; i <= actual_col; j++)
            {
                if (j != actual_col)
                {
                    cell = cell->next;
                }
                else
                {
                    cell->value = data;
                    break;
                }
            }
            break;
        }
    }
}

// Función para saber el número de filas de la hoja de cálculo
int contar_filas(MainListNode *&list)
{
    MainListNode *aux = list;
    int contador = 0;

    while (aux != NULL)
    {
        contador++;
        aux = aux->next;
    }

    return contador;
}

// Función para saber el número de columnas de la hoja de cálculo
int contar_columnas(Cell *&list)
{
    Cell *aux = list;
    int contador = 0;

    while (aux != NULL)
    {
        contador++;
        aux = aux->next;
    }

    return contador;
}

// Función para copiar el contenido de una celda
string copiar_celda(MainListNode *&list, int actual_row, int actual_col)
{
    MainListNode *row = list;
    Cell *cell;
    string data;

    for (int i = 0; i <= actual_row; i++)
    {
        if (i != actual_row)
        {
            row = row->next;
        }
        else
        {
            cell = row->row;

            for (int j = 0; i <= actual_col; j++)
            {
                if (j != actual_col)
                {
                    cell = cell->next;
                }
                else
                {
                    data = cell->value;
                    break;
                }
            }
            break;
        }
    }

    return data;
}

// Función para cortar el contenido de una celda
string cortar_celda(MainListNode *&list, int actual_row, int actual_col)
{
    MainListNode *row = list;
    Cell *cell;
    string data;

    for (int i = 0; i <= actual_row; i++)
    {
        if (i != actual_row)
        {
            row = row->next;
        }
        else
        {
            cell = row->row;

            for (int j = 0; i <= actual_col; j++)
            {
                if (j != actual_col)
                {
                    cell = cell->next;
                }
                else
                {
                    data = cell->value;
                    cell->value = "";
                    break;
                }
            }
            break;
        }
    }

    return data;
}

// Función para eliminar la hoja de cálculo y vaciar las celdas de memoria ocupadas
void vaciar(MainListNode **nodoInicio)
{
    MainListNode *current = *nodoInicio;
    MainListNode *next;

    while (current != NULL)
    {
        next = current->next;
        delete (current);
        current = next;
    }
    *nodoInicio = NULL;
}

// Función para guardar la matriz en un archivo json
bool save_file(std::string data, std::string filename)
{
    int cantidad_archivos = contar_archivos();

    cantidad_archivos += 1;

    filename = "files/" + to_string(cantidad_archivos) + ". " + filename;

    std::ofstream file(filename, std::ios::binary);

    if (!file.is_open())
    {
        return false;
    }

    for (uint32_t i = 0; i < data.size(); ++i)
    {
        char c = data[i];
        file.write(&c, sizeof(char));
    }

    return true;
}
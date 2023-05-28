#include <iostream>
#include <conio.h>
#include <limits>
#include <string>
#include <fstream>
#include <dirent.h>

using namespace std;

// Función para limpiar el buffer del cin
void clean_cin()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Función para manejar los errores al ingresar mal un dato con cin
void validate_cin()
{
    char opc;

    // limpia el estado de error y vacia completamente el buffer
    clean_cin();
    std::cout << "\nEl dato ingresado no es valido. Intente de nuevo.\n\n";
    std::cout << "Presione una tecla para continuar...\n\n";
    opc = getche();
}

// Función para obtener el equivalente en número de una letra;
int letter_to_number(char letter)
{
    letter = toupper(letter);

    // Subtract 'a' from the letter to get its ASCII code.
    int ascii_code = letter - 'A' + 1;

    // Return the ASCII code modulo 26, which will be the number from 0 to 25.
    return ascii_code % 26;
}

// Función que permiti imprimir espacios en consola
void relleno(int tam)
{
	for(int i = 0; i < tam; i++)
        std::cout << " ";
}

// Función para imprimir el mensaje de confirmacion
void imprimir_mensaje_confirmacion()
{
    std::cout << "Presione una tecla para continuar...\n";
}

// Función para saber si una cadena tiene espacios
bool has_space(std::string word){
    for(int i = 0; i < word.length(); i++)
        if(word[i] == 32) return true;

    return false;
}

// Función que sirve para contar el número de archivos guardados en la carpeta "files"
int contar_archivos()
{
    string elem;
    string dir = "files";
    DIR *direccion;
    struct dirent *elementos;
    int cantidad_archivos = 0;

    if(direccion=opendir(dir.c_str()))
    {
        while(elementos=readdir(direccion))
        {
            if (elementos->d_namlen != 1 && elementos->d_namlen != 2)
            {
                cantidad_archivos++;
            }
        }
    }

    closedir(direccion);

    return cantidad_archivos;
}

// Definición del nodo que nos servirá para crear la lista donde guardaremos los archivos recuperados
struct File{
    string name;
    int index;
    File *next;
};

// Función para insertar un nuevo nodo a la lista de archivos
void insertar_elemento(File *&list, string value, int index)
{
    File *new_node = new File();

    new_node->name = value;
    new_node->index = index;
    new_node->next = NULL;

    if (list == NULL)
    {
        list = new_node;
    }
    else
    {
        File *aux1 = list;
        File *aux2 = NULL;

        while (aux1 != NULL)
        {
            aux2 = aux1;
            aux1 = aux1->next;
        }

        aux2->next = new_node;
    }
}

// Función que sirve para recuperar el nombre los archivos guardados en la carpeta "files"
void recuperar_archivos(File *&list)
{
    string elem;
    string dir = "files";
    DIR *direccion;
    struct dirent *elementos;
    int cantidad_archivos = 0;
    int file_index = 1;

    if(direccion=opendir(dir.c_str()))
    {
        while(elementos=readdir(direccion))
        {
            if (elementos->d_namlen != 1 && elementos->d_namlen != 2)
            {
                insertar_elemento(list, elementos->d_name, file_index);
                file_index++;
            }
        }
    }

    closedir(direccion);
}

// Función que sirve para imprimir el nombre de los archivos recuperados
void imprimir_nombre_archivos(File *&list)
{
    File *aux = list;

    while(aux != NULL)
    {
        cout << aux->name << "\n";
        aux = aux->next;
    }
}

// Función que sirve para recuperar el nombre de un archivo basado en su índice
string extraer_nombre_archivo(File *&list, int file_index)
{
    File *aux = list;

    while(aux != NULL)
    {
        if(aux->index == file_index) return aux->name;
        aux = aux->next;
    }

    return "";
}

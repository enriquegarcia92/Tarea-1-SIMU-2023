#include <iostream>
#include <conio.h>
#include <limits>
#include <string>

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
    std::cout << "Presione una tecla para continuar...\n\n";
}

// Función para saber si una cadena tiene espacios
bool has_space(std::string word){
    for(int i = 0; i < word.length(); i++)
        if(word[i] == 32) return true;

    return false;
}
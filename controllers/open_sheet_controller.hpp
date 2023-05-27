#include <iostream>
#include <conio.h>
#include <algorithm>
#include <string>
#include "../utils/JSON.hpp"

using namespace std;
using JSON = dnc::JSON;

void menu_archivos(){
    // int option = 0;

    /*do{

    }while (option != 0);  */

    JSON obj;

    obj.parseFromFile("prueba.json");

    string fila;

    string fila_formateada;

    int iterador_fila_formateada = 0;

    // Obtenemos el numero de columnas de cada fila

    // Obtenemos el primer arreglo del json
    string objeto_inicial = (obj.begin())->toString();

    // variable que nos servirá para obtener la cantidad de elementos de cada fila
    int cantidad_elementos = 0;

    for(int i = 0; i < objeto_inicial.length(); i++){
        // encontramos la cantidad de "comas" en el arreglo
        // la cantidad de elementos será cantidad_de_comas + 1
        if(objeto_inicial[i] == ',')
            cantidad_elementos++;
    }

    // sumamos 1 a la cantidad de comas encontradas para obtener el total de elementos
    cantidad_elementos += 1;

    string columnas[cantidad_elementos];

    string corchetes = "[]";

    for(auto it = obj.begin(); it != obj.end(); ++it)
    {
        //it.key() devuelve la clave del valor actual del iterador.
        fila = it->toString();
        
        for(int i = 0; i < fila.length(); i++)
            if(fila[i] == '[' || fila[i] == ']' || fila[i] == 32)
                fila.erase(i, 1);
            
        cout << fila << "\n";
    } 
}
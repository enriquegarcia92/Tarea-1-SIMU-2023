#include <iostream>

using namespace std;
int** crear_matriz(int rows, int cols);
void menu_principal(int menuoption);
void menu_matriz(int menuoption);
void imprimir_matriz(int **table, int rows, int columns);
void insertar_en_matriz(int **table,int row,int column,int value);
void limpiar_matriz(int **table,int rows, int cols);
int copiar_celda(int **table,int localrows,int localcols);
void pegar_celda(int **table,int localrows,int localcols,int cellcopy);
int cortar_celda(int **table,int localrows,int localcols);

int main(){
    int menuoption = 0;
    menu_principal(0);//Llama función de menú principal
    return 0;
}

void menu_principal(int menuoption){
    int options = 0;
    while(menuoption!=3){
        cout<<"Menú principal\n"
          "--------------\n"
          "1.nuevo\n"
          "2.abrir\n"
          "3.salir\n";
    cin>>menuoption;
    switch(menuoption){
        case 1:
        menu_matriz(options);//Llama función que gestiona menú de matriz
        break;
        case 2: cout<<"TODO\n";
        break;
        default: cout<<"Entrada invalida\n";
    }
    }
}

void menu_matriz(int options){
            int sizerows=5,sizecols=5; //variables que contienen dimensiones de la tabla
            int localrows=0,localcols=0,validrow=0,validcol=0;//Funciones que ocntienen la localización actual y auxiliares para validar que la entrada no exeda
            int **table = crear_matriz(sizerows,sizecols); //Se crea la matriz de vectores
            int cellcopy;//Variable que contiene el dato para las funciones de copiar,cortar,pegar
        while(options!=11){
            imprimir_matriz(table, 5, 5);
            cout<<"\nOpciones\n"
          "---------------------------\n"
          "1.Ingresar contenido\n"
          "2.Saltar a celda\n"
          "3.Copiar\n"
          "4.Cortar\n"
          "5.Pegar\n"
          "6.Mover a la izquierda\n"
          "7.Mover a la derecha\n"
          "8.Moverse arriba\n"
          "9.Moverse abajo\n"
          "10.Guardar\n"
          "11.Salir\n";
            cin>>options;
            switch(options){
                case 1:
                cout<<"Posicion actual: "<<localrows<<","<<localcols<<"\n";
                int value;
                cout<<"Ingrese el valor a ingresar\n";
                cin>>value;
                insertar_en_matriz(table,localrows,localcols,value); //función de insertar valor en una matriz, esta recibe la dirección de la tabla, y la posición actual, y el valor
                break;
                case 2:
                cout<<"Ingrese la fila a la que desea saltar\n";
                cin>>validrow;
                cout<<"Ingrese la columna a la que desea saltar\n";
                cin>>validcol;
                if(validrow>sizecols || validcol>sizerows || validcol<0 || validrow<0){//verifica que la entrada no exeda los límites de la tabla
                    cout<<"Posicion excede limites de la tabla\n";
                }else{
                    localrows = validrow;
                    localcols = validcol;//Módifica el valor de las variables que contienen la localización
                    cout<<"Nueva posicion: "<<localrows<<","<<localcols<<"\n";
                }
                break;
                case 3:
                cellcopy = copiar_celda(table,localrows,localcols); //Función de copiar recibe la tabla, posición y regresa un int que se guarda en cellcopu
                cout<<"Contendio copiado: "<<cellcopy<<"\n";
                break;
                case 4:
                cellcopy = cortar_celda(table,localrows,localcols);//Función de copiar recibe la tabla, posición y regresa un int que se guarda en cellcopu
                cout<<"Contendio cortado: "<<cellcopy<<"\n";
                break;
                case 5:
                cout<<"Pegar contendio: "<<cellcopy<<"\n";
                pegar_celda(table,localrows,localcols,cellcopy);//Función de pegar que instancia el valor de cellcopy en la celda de la localización actual
                break;
                case 6:
                validcol=localcols;
                validcol--;
                if(validcol<=0 || validcol>=auxcols){
                    cout<<"Posicion excede limites de la tabla\n";
                }else{
                    localcols = validcol;
                    cout<<"Nueva posicion: "<<localrows<<","<<localcols<<"\n"; //Porción de código que disminuye en 1 las columnas y revisa que no exeda los limites de la tabla
                }
                break;
                case 7:
                validcol=localcols;
                validcol++;
                if(validcol<=0 || validcol>=sizecols){
                    cout<<"Posicion excede limites de la tabla\n";
                }else{
                    localcols = validcol;
                    cout<<"Nueva posicion: "<<localrows<<","<<localcols<<"\n";//Porción de código que aumenta en 1 las columnas y revisa que no exeda los limites de la tabla
                }
                break;
                case 8:
                validrow=localrows;
                validrow--;
                if(validrow<=0 || validrow>=sizerows){
                    cout<<"Posicion excede limites de la tabla\n";
                }else{
                    localrows = validrow;
                    cout<<"Nueva posicion: "<<localrows<<","<<localcols<<"\n";//Porción de código que disminuye en 1 las filas y revisa que no exeda los limites de la tabla
                }
                break;
                case 9:
                validrow=localrows;
                validrow++;
                if(validrow<=0 || validrow>=sizerows){
                    cout<<"Posicion excede limites de la tabla\n";
                }else{
                    localrows = validrow;
                    cout<<"Nueva posicion: "<<localrows<<","<<localcols<<"\n";//Porción de código que aumenta en 1 las filas y revisa que no exeda los limites de la tabla
                }
                break;
                case 10: cout<<"TODO\n";
                break;
                case 11:
                limpiar_matriz(table,sizerows, sizecols); //Función que limpia la memoria ocupada por la matriz
                break;
                default: cout<<"Entrada invalida\n";
            }
}
}

int** crear_matriz(int rows, int cols){ //función que crea el arreglo 2d o matríz
        int **table = new int*[rows];
        for(int i = 0; i < rows; i++){
            table[i] = new int[cols];
        }
        
        return table; 
    }

void limpiar_matriz(int **table, int rows, int cols){ //funcón que la limpia
    for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < cols; j++) {
                        table[i][j] = NULL;
                    }
                }
                delete [] table;
                table = NULL;
}


void imprimir_matriz(int **table, int rows, int columns){//Función que imprime la matríz, si el contendio es 0 el formato que imprime es ___|___|___|
      for(int i = 0; i < rows; i++){
            for (int j = 0; j< columns; j++){
                if(table[i][j]==0){
                    cout<<"___|";
                }else{
                cout<<table[i][j]<<"|";
                }
            }
            cout<<endl;
        }
}

void insertar_en_matriz(int **table,int row,int column,int value){ //Función que coloca el valor recivido en la posición designada
    table[row][column] = value;
}

int copiar_celda(int **table,int localrows,int localcols){ //Función que retorna el valor de la celda
    return table[localrows][localcols];
}

void pegar_celda(int **table,int localrows,int localcols,int cellcopy){ //Función que inserta el valor almacenado en cellcopy a la celda
        table[localrows][localcols] = cellcopy;
}

int cortar_celda(int **table,int localrows,int localcols){ //Función que almacena el valor de la celda, limpia la celda y retorna el valor guardado
    int auxcut;
    auxcut = table[localrows][localcols];
    table[localrows][localcols]=NULL;
    return auxcut;
}
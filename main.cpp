#include <iostream>

using namespace std;
int** crear_matriz(int rows, int cols);
void menu_principal(int menuoption);
void menu_matriz(int menuoption);
void imprimir_matriz(int **table, int rows, int columns);
void insertar_en_matriz(int **table,int row,int column,int value);
void limpiar_matriz(int **table,int rows);
int copiar_celda(int **table,int localrows,int localcols);
void pegar_celda(int **table,int localrows,int localcols,int cellcopy);
int cortar_celda(int **table,int localrows,int localcols);

int main(){
    int menuoption = 0;
    menu_principal(0);
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
        menu_matriz(options);
        break;
        case 2: cout<<"TODO\n";
        break;
        default: cout<<"Entrada invalida\n";
    }
    }
}

void menu_matriz(int options){
            int minrows=5,mincols=5;
            int localrows=0,localcols=0;
            int **table = crear_matriz(minrows,mincols);
            int cellcopy;
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
                insertar_en_matriz(table,localrows,localcols,value);
                break;
                case 2:
                cout<<"Ingrese la fila a la que desea saltar\n";
                cin>>localrows;
                cout<<"Ingrese la columna a la que desea saltar\n";
                cin>>localcols;
                cout<<"Nueva posicion: "<<localrows<<","<<localcols<<"\n";
                break;
                case 3:
                cellcopy = copiar_celda(table,localrows,localcols);
                cout<<"Contendio copiado: "<<cellcopy<<"\n";
                break;
                case 4:
                cellcopy = cortar_celda(table,localrows,localcols);
                cout<<"Contendio cortado: "<<cellcopy<<"\n";
                break;
                case 5:
                cout<<"Pegar contendio: "<<cellcopy<<"\n";
                pegar_celda(table,localrows,localcols,cellcopy);
                break;
                case 6:
                localcols--;
                cout<<"Nueva posicion: "<<localrows<<","<<localcols<<"\n";
                break;
                case 7:
                localcols++;
                cout<<"Nueva posicion: "<<localrows<<","<<localcols<<"\n";
                break;
                case 8:
                localrows--;
                cout<<"Nueva posicion: "<<localrows<<","<<localcols<<"\n";
                break;
                case 9:
                localrows++;
                cout<<"Nueva posicion: "<<localrows<<","<<localcols<<"\n";
                break;
                case 10: cout<<"TODO\n";
                break;
                case 11:
                limpiar_matriz(table, 5);
                break;
                default: cout<<"Entrada invalida\n";
            }
}
}

int** crear_matriz(int rows, int cols){
        int **table = new int*[rows];
        for(int i = 0; i < rows; i++){
            table[i] = new int[cols];
        }
        
        return table;
    }

void limpiar_matriz(int **table, int rows){
    for(int i = 0; i < rows; i++){
            delete[] table[i];
        }
        delete[] table;
        table = NULL;
}


void imprimir_matriz(int **table, int rows, int columns){
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

void insertar_en_matriz(int **table,int row,int column,int value){
    table[row][column] = value;
}

int copiar_celda(int **table,int localrows,int localcols){
    return table[localrows][localcols];
}

void pegar_celda(int **table,int localrows,int localcols,int cellcopy){
        table[localrows][localcols] = cellcopy;
}

int cortar_celda(int **table,int localrows,int localcols){
    int auxcut;
    auxcut = table[localrows][localcols];
    table[localrows][localcols]=NULL;
    return auxcut;
}


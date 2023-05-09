#include <iostream>

using namespace std;
int** crear_matriz();
void menu_principal(int menuoption);
void menu_matriz(int menuoption);
void imprimir_matriz(int **table, int rows, int columns);
void insertar_en_matriz(int **table,int row,int column,int value);
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
            int **table = crear_matriz();
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
                int row,column,value;
                cout<<"Ingrese en que columna va a ingresar\n";
                cin>>column;
                cout<<"Ingrese en que fila va a ingresar\n";
                cin>>row;
                cout<<"Ingrese el valor a ingresar\n";
                cin>>value;
                insertar_en_matriz(table,row,column,value);
                break;
                case 2: cout<<"TODO\n";
                break;
                case 3: cout<<"TODO\n";
                break;
                case 4: cout<<"TODO\n";
                break;
                case 5: cout<<"TODO\n";
                break;
                case 6: cout<<"TODO\n";
                break;
                case 7: cout<<"TODO\n";
                break;
                case 8: cout<<"TODO\n";
                break;
                case 9: cout<<"TODO\n";
                break;
                case 10: cout<<"TODO\n";
                break;
                case 11: cout<<"TODO\n";
                break;
                default: cout<<"Entrada invalida\n";
            }
}
}

int** crear_matriz(){
        int rows=5,columns=5;
        int **table = new int*[rows];
        for(int i = 0; i < rows; i++){
            table[i] = new int[columns];
        }
        
        return table;
        /*for(int i = 0; i < rows; i++){
            delete[] table[i];
        }
        delete[] table;
        table = NULL;*/
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

    
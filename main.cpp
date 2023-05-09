#include <iostream>

using namespace std;
void crear_matriz();
void menu_principal();
void menu_matriz();
int main(){
    
    menu_principal();
    return 0;
}

void menu_principal(){
        int menuprin = 0;
    while(menuprin!=3){
        cout<<"Menú principal\n"
          "--------------\n"
          "1.nuevo\n"
          "2.abrir\n"
          "3.salir\n";
    cin>>menuprin;
    switch(menuprin){
        case 1:
        menu_matriz();
        break;
        case 2: cout<<"TODO\n";
        break;
        default: cout<<"Entrada invalida\n";
    }
    }
}

void menu_matriz(){
    int options = 0;
        while(options!=11){
            crear_matriz();
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
                case 1: cout<<"TODO\n";
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

void crear_matriz(){
        int rows=5,columns=5;
        string **table = new string*[rows];
        for(int i = 0; i < rows; i++){
            table[i] = new string[columns];
        }
        
        for(int i = 0; i < rows; i++){
            for (int j = 0; j< columns; j++){
                if(table[i][j]==""){
                    cout<<"___|";
                }else{
                cout<<table[i][j]<<"|";
                }
            }
            cout<<endl;

        }
        
        for(int i = 0; i < rows; i++){
            delete[] table[i];
        }
        delete[] table;
        table = NULL;
    }
    
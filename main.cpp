#include <iostream>

using namespace std;
string** crear_matriz(int rows, int cols);
void menu_principal(int menuoption);
void menu_matriz(int menuoption);
void imprimir_matriz(string **table, int rows, int columns);
void copy_matrix(string** source, string** destination, int rows, int columns);
void insertar_en_matriz(string **table,int row,int column,string value);
void limpiar_matriz(string **table,int rows, int cols);
string copiar_celda(string **table,int localrows,int localcols);
void pegar_celda(string **table,int localrows,int localcols,string cellcopy);
string cortar_celda(string **table,int localrows,int localcols);
int letter_to_number(char letter);

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
            int sizerows=6,sizecols=6; //variables que contienen dimensiones de la tabla
            int localrows=1,localcols=1,validrow=0,validcol=0;//Funciones que ocntienen la localización actual y auxiliares para validar que la entrada no exeda
            string **table = crear_matriz(sizerows,sizecols); //Se crea la matriz de vectores
            string cellcopy;//Variable que contiene el dato para las funciones de copiar,cortar,pegar
            string value;
            char colLetter='a';
        while(options!=11){
            imprimir_matriz(table, sizerows, sizecols);
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
                cout<<"Posicion actual: "<<colLetter<<","<<localrows<<"\n";
                cout<<"Ingrese el valor a ingresar\n";
                cin>>value;
                if (localrows > 5 || localcols > 5){
                    //crear matriz nueva, copiar valores de la anterior, pegar en nueva matriz e insertar el valor
                    string **expandedTable = crear_matriz(localrows, localcols);
                    copy_matrix(table, expandedTable, sizerows, sizecols);
                     for (int i = 0; i < sizerows; i++) {
                        delete[] table[i];
                    }
                    delete[] table;
                table = NULL;
                table = expandedTable;            
                sizerows=localrows;
                sizecols=localcols;
                if(localrows > 0 && localcols > 0){
                    insertar_en_matriz(table, localrows-1, localcols-1, value);
                }else if(localrows == 0 && localcols == 0){
                   insertar_en_matriz(table, localrows, localcols, value);
                   localrows = 1;
                   localcols = 1;
                }
                
                }else{
                    insertar_en_matriz(table,localrows,localcols,value); //función de insertar valor en una matriz, esta recibe la dirección de la tabla, y la posición actual, y el valor
                }
                break;
                case 2:
                cout<<"Ingrese la fila a la que desea saltar usando las letras a-z\n";
                cin>>colLetter;
                validcol = letter_to_number(colLetter);
                cout<<"Ingrese la columna a la que desea saltar con su valor numerico\n";
                cin>>validrow;
                if(validrow>25 || validcol>25 || validcol<1 || validrow<1){//verifica que la entrada no exeda los límites de la tabla
                    cout<<"Posicion excede limites de la tabla\n";
                }else{
                    localrows = validrow;
                    localcols = validcol;//Módifica el valor de las variables que contienen la localización
                    cout<<"Nueva posicion: "<<colLetter<<","<<localrows<<"\n";
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
                if(validcol<=0 || validcol>=sizecols){
                    cout<<"Posicion excede limites de la tabla\n";
                }else{
                    localcols = validcol;
                    cout<<"Nueva posicion: "<<colLetter<<","<<localrows<<"\n"; //Porción de código que disminuye en 1 las columnas y revisa que no exeda los limites de la tabla
                }
                break;
                case 7:
                validcol=localcols;
                validcol++;
                if(validcol<=0 || validcol>=sizecols){
                    cout<<"Posicion excede limites de la tabla\n";
                }else{
                    localcols = validcol;
                    cout<<"Nueva posicion: "<<colLetter<<","<<localrows<<"\n";//Porción de código que aumenta en 1 las columnas y revisa que no exeda los limites de la tabla
                }
                break;
                case 8:
                validrow=localrows;
                validrow--;
                if(validrow<=0 || validrow>=sizerows){
                    cout<<"Posicion excede limites de la tabla\n";
                }else{
                    localrows = validrow;
                    cout<<"Nueva posicion: "<<colLetter<<","<<localrows<<"\n";//Porción de código que disminuye en 1 las filas y revisa que no exeda los limites de la tabla
                }
                break;
                case 9:
                validrow=localrows;
                validrow++;
                if(validrow<=0 || validrow>=sizerows){
                    cout<<"Posicion excede limites de la tabla\n";
                }else{
                    localrows = validrow;
                    cout<<"Nueva posicion: "<<colLetter<<","<<localrows<<"\n";//Porción de código que aumenta en 1 las filas y revisa que no exeda los limites de la tabla
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

string** crear_matriz(int rows, int cols){ //función que crea el arreglo 2d o matríz
        string **table = new string*[rows];
        for(int i = 0; i < rows; i++){
            table[i] = new string[cols];
        }
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                table[i][0] = to_string(i);
                table[0][j] = 'a' + j - 1;
            }   
        }
        return table; 
    }

void copy_matrix(string** source, string** destination, int rows, int columns) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      destination[i][j] = source[i][j];
    }
  }
}

void limpiar_matriz(string **table, int rows, int cols){ //funcón que la limpia
   for (int i = 0; i < rows; i++) {
        delete[] table[i];
    }
            delete[] table;
}


void imprimir_matriz(string **table, int rows, int columns){//Función que imprime la matríz, si el contendio es 0 el formato que imprime es ___|___|___|
      for(int i = 0; i < rows; i++){
            for (int j = 0; j< columns; j++){
                if(table[i][j]==""){
                    cout<<"________|";
                }else{
                for (int k = 0; k < 8 - table[i][j].length(); k++) {
                    cout << " ";
                }    
                cout << table[i][j] << "|";
                }
            }
            cout<<endl;
        }
}

void insertar_en_matriz(string **table,int row,int column,string value){ //Función que coloca el valor recivido en la posición designada
        table[row][column] = value;
}

string copiar_celda(string **table,int localrows,int localcols){ //Función que retorna el valor de la celda
    return table[localrows][localcols];
}

void pegar_celda(string **table,int localrows,int localcols,string cellcopy){ //Función que inserta el valor almacenado en cellcopy a la celda
        table[localrows][localcols] = cellcopy;
}

string cortar_celda(string **table,int localrows,int localcols){ //Función que almacena el valor de la celda, limpia la celda y retorna el valor guardado
    string auxcut;
    auxcut = table[localrows][localcols];
    table[localrows][localcols]="";
    return auxcut;
}

int letter_to_number(char letter) {
  // Subtract 'a' from the letter to get its ASCII code.
  int ascii_code = letter - 'a'+1;

  // Return the ASCII code modulo 26, which will be the number from 0 to 25.
  return ascii_code % 26;
}
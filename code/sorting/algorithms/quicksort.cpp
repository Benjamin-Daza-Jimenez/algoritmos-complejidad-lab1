#include <iostream>
#include <vector>
using namespace std;
/*
Nombre: particion
Parametro: 
    vector<int>&lista: paso por referencia del vector.
    int inicio: inicio del vector
    int final: final del vector.
Retorno: 
    i-1: posicion del punto medio entre los mayores y los menores al pivote.
Busca realizar el sort a partir de un pivote (en este caso el primer elemento del vector). si es mayor avanza j, si es menor avanza j e i.
*/
int particion(vector<int>&lista, int inicio, int final){
    int pivoteIdx = rand() % (final - inicio + 1) + inicio;  // Índice aleatorio en el rango [inicio, final]
    swap(lista[inicio], lista[pivoteIdx]);  // Intercambiamos el pivote aleatorio con el primer elemento

    int pivote=lista[inicio];
    int i= inicio + 1;
    for(int j=i; j<=final; j++){
        if(lista[j]<pivote){
            swap(lista[i],lista[j]);
            i++;
        }
    }
    swap(lista[inicio],lista[i-1]);
    return i-1;
}
/*
Nombre: QuickSort
Parametro: 
    vector<int>&lista: paso por referencia del vector que se desea ordenar.
    int inicio: inicio del vector.
    int final: final del vector.
Retorno: N/A
Se llama recursivamente a si misma y a la funcion particion, la cual busca el punto medio entre los menores al pivote y los mayores al pivote.
*/
void QuickSort(vector<int>&lista, int inicio, int final){
    if(inicio<final){
        int pivote=particion(lista,inicio,final);
        QuickSort(lista,inicio,pivote-1);
        QuickSort(lista,pivote+1,final);
    }
}
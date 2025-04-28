#include <iostream>
#include <vector>
using namespace std;
/*
Nombre: SelectionSort
Parametro: 
    vector<int>&lista: paso por referencia de la lista que se desea ordenar
    int n: tamaño de la lista
Retorno: N/A
Se recorre caso a caso, comparando cada uno de los valores con los siguientes, intercambiando posiciones para luego, junto a una variable aux, cambiar los valores en la lista.
*/
void SelectionSort(vector<int>&lista, int n){
    for(int i=0; i<n; i++){
        int min_pos=i;
        for(int j=i+1; j<n+1; j++){
            if(lista[j]<lista[min_pos]){
                min_pos=j;
            }
        }
        if(min_pos!=i){
            int aux=lista[i];
            lista[i]=lista[min_pos];
            lista[min_pos]=aux;
        }
    }
}
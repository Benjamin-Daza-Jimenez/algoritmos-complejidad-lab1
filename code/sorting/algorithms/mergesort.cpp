#include <iostream>
#include <vector>
using namespace std;
/*
Nombre: Merge
Parametro: 
    vector<int>&lista: referencia del vector.
    int inicio: inicio del vector
    int mitad: mitad del vector
    int final: final del vector
Retorno: N/A
Mezcla los arreglos que nos queden restantes considerando el valor de los elementos.
*/
void Merge(vector<int>&lista, int inicio, int mitad, int final){
    int i,j,k;
    int elementoIzq=mitad-inicio+1;
    int elementoDer=final-mitad;

    vector<int>izquierda(elementoIzq);
    vector<int>derecha(elementoDer);

    for(i=0; i<elementoIzq; i++){
        izquierda[i]=lista[inicio+i];
    }
    for(j=0; j<elementoDer; j++){
        derecha[j]=lista[mitad+1+j];
    }
    i=0;
    j=0;
    k=inicio;
    while(i<elementoIzq && j<elementoDer){
        if(izquierda[i]<=derecha[j]){
            lista[k]=izquierda[i];
            i++;
        }
        else{
            lista[k]=derecha[j];
            j++;
        }
        k++;
    }
    while(j<elementoDer){
        lista[k]=derecha[j];
        j++;
        k++;
    }
    while(i<elementoIzq){
        lista[k]=izquierda[i];
        i++;
        k++;
    }
}
/*
Nombre: MergseSort
Parametro: 
    vector<int>&lista: referencia del vector
    int inicio: inicio del vector
    int final: fin del vector
Retorno: N/A
Funcion que busca llamar de forma recursiva a si misma en sus dos mitades y, a la función Merge encargada de realizar la union. 
Su objetivo es: dividir el arreglo en la mitad hasta que se vuelva un vector de una posicion.
*/
void MergeSort(vector<int>&lista,int inicio, int final){
    if(inicio<final){
        int mitad=inicio+(final-inicio)/2;
        MergeSort(lista,inicio,mitad);
        MergeSort(lista,mitad+1,final);
        Merge(lista, inicio, mitad, final);
    }
}
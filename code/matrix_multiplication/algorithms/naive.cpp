#include <iostream>
#include <vector>
using namespace std;
/*
Nombre: MultiMatrices
Parametro: 
    vector<vector<int>>m1: Copia de la primera matriz (vector de vectores) la cual se quiere multiplicar.
    vector<vector<int>>m2: Copia de la segunda matriz (vector de vectores) la cual se quiere multiplicar.
    vector<vector<int>>&m3: Paso por referencia de la matriz resultante inicializada en 0.
Retorno: N/A
Multiplica las matrices m1 y m2, guardando la suma de las multiplicaciones en m3 (método de multiplicación de matrices).
*/
void MultiMatrices(vector<vector<int>>m1,vector<vector<int>>m2,vector<vector<int>>&m3){
    int filasA=m1.size();
    int colAfilB=m1[0].size();
    int columnasB=m2[0].size();
    for(int i=0; i<filasA; i++){
        for(int j=0; j<columnasB; j++){
            for(int k=0; k<colAfilB; k++){
                m3[i][j]+= m1[i][k] * m2[k][j];
            }
        }
    }
}
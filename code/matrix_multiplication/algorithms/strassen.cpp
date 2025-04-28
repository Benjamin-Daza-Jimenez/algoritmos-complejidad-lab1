#include <iostream>
#include <vector>
using namespace std;
/*
Nombre: restar
Parametro: 
    const vector<vector<int>>&A: primera matriz que se desea restar.
    const vector<vector<int>>&B: segunda matriz que se desea restar.
Retorno: 
    C: matriz resultante de la resta entre A y B.
Resta la matriz A y B, posicion por posicion, guardando su resultado en la matriz C.
*/
vector<vector<int>> restar(const vector<vector<int>>&A, const vector<vector<int>>&B){
    vector<vector<int>> C(A.size(), vector<int>(A.size()));
    for(int i=0; i<A.size(); ++i){
        for(int j=0; j<A.size(); ++j){
            C[i][j]=A[i][j]-B[i][j];
        }
    }
    return C;
}
/*
Nombre: sumar
Parametro: 
    const vector<vector<int>>&A: primera matriz que se desea sumar.
    const vector<vector<int>>&B: segunda matriz que se desea sumar.
Retorno: 
    C: matriz resultante de la suma entre A y B.
Suma la matriz A y B, posicion por posicion, guardando su resultado en la matriz C.
*/
vector<vector<int>> sumar(const vector<vector<int>>&A, const vector<vector<int>>&B){
    vector<vector<int>> C(A.size(), vector<int>(A.size()));
    for (int i=0; i<A.size(); ++i) {
        for (int j=0; j<A.size(); ++j) {
            C[i][j]=A[i][j]+B[i][j];
        }
    }
    return C;
}
/*
Nombre: strassen
Parametro: 
    const vector<vector<int>>&A: primera matriz que se desea multiplicar.
    const vector<vector<int>>&B: segunda matriz que se desea multiplicar.
Retorno: 
    matrizC: matriz resultante de la multiplicación entre A y B.
Divide las matrices en 4 sub matrices, de las cuales se realizarán operaciones propuestas por strassen, llamando a la función suma y resta para realizar estas operaciones. 
*/
vector<vector<int>> strassen(const vector<vector<int>>&A, const vector<vector<int>>&B){
    int n = A.size();
    if(n == 1){
        vector<vector<int>> matrizC(1, vector<int>(1));
        matrizC[0][0] = A[0][0] * B[0][0];
        return matrizC;
    }
    int mitad = n / 2;
    vector<vector<int>> A11(mitad, vector<int>(mitad)), A12(mitad, vector<int>(mitad)), A21(mitad, vector<int>(mitad)), A22(mitad, vector<int>(mitad));
    vector<vector<int>> B11(mitad, vector<int>(mitad)), B12(mitad, vector<int>(mitad)), B21(mitad, vector<int>(mitad)), B22(mitad, vector<int>(mitad));
    for(int i=0; i<mitad; ++i){
        for(int j=0; j<mitad; ++j){
            A11[i][j]=A[i][j];
            A12[i][j]=A[i][j + mitad];
            A21[i][j]=A[i+mitad][j];
            A22[i][j]=A[i+mitad][j+mitad];
            B11[i][j]=B[i][j];
            B12[i][j]=B[i][j+mitad];
            B21[i][j]=B[i+mitad][j];
            B22[i][j]=B[i+mitad][j+mitad];
        }
    }
    vector<vector<int>> M1=strassen(sumar(A11, A22), sumar(B11, B22));
    vector<vector<int>> M2=strassen(sumar(A21, A22), B11);
    vector<vector<int>> M3=strassen(A11, restar(B12, B22));
    vector<vector<int>> M4=strassen(A22, restar(B21, B11));
    vector<vector<int>> M5=strassen(sumar(A11, A12), B22);
    vector<vector<int>> M6=strassen(restar(A21, A11), sumar(B11, B12));
    vector<vector<int>> M7=strassen(restar(A12, A22), sumar(B21, B22));
    vector<vector<int>> C11=sumar(restar(sumar(M1, M4), M5), M7);
    vector<vector<int>> C12=sumar(M3, M5);
    vector<vector<int>> C21=sumar(M2, M4);
    vector<vector<int>> C22=sumar(restar(sumar(M1, M3), M2), M6);
    vector<vector<int>> matrizC(n, vector<int>(n));
    for(int i=0; i<mitad; ++i){
        for(int j=0; j<mitad; ++j){
            matrizC[i][j]=C11[i][j];
            matrizC[i][j+mitad]=C12[i][j];
            matrizC[i+mitad][j]=C21[i][j];
            matrizC[i+mitad][j+mitad]=C22[i][j];
        }
    }
    return matrizC;
}
# Documentación

## Multiplicación de matrices
* [naive.cpp](https://github.com/Benjamin-Daza-Jimenez/INF221-2025-1-TAREA-1-master/blob/main/code/matrix_multiplication/algorithms/naive.cpp): Multiplica las matrices m1 y m2, guardando la suma de las multiplicaciones en m3 (método de multiplicación de matrices tradicional).

* [strassen.cpp](https://github.com/Benjamin-Daza-Jimenez/INF221-2025-1-TAREA-1-master/blob/main/code/matrix_multiplication/algorithms/strassen.cpp): Divide las matrices en 4 sub matrices, de las cuales se realizarán operaciones propuestas por strassen, llamando a la función suma y resta para realizar estas operaciones. 

Función suma: suma la matriz A y B, posición por posición, guardando su resultado en la matriz C.
Función resta: resta la matriz A y B, posición por posición, guardando su resultado en la matriz C.

### Programa principal matrices

* [matrix_multiplication.cpp](https://github.com/Benjamin-Daza-Jimenez/INF221-2025-1-TAREA-1-master/blob/main/code/matrix_multiplication/matrix_multiplication.cpp): recorre archivos generados en [matrix_input](https://github.com/Benjamin-Daza-Jimenez/INF221-2025-1-TAREA-1-master/tree/main/code/matrix_multiplication/data/matrix_input), cada 2 iteraciones del ciclo guarda ambas matrices necesarias para la multiplicación, realizando las operaciones necesarias a cada implementación desde la función prueba.

Función prueba: toma el tiempo en realizar cada algoritmo y su respectivo uso de memoria, esta información es agregada en una linea adicional en el archivo de texto almacenado en [measurements](https://github.com/Benjamin-Daza-Jimenez/INF221-2025-1-TAREA-1-master/tree/main/code/matrix_multiplication/data/measurements). Imprime por pantalla el algoritmo utilizado y la información antes dicha. Finalmente se almacena el resultado de la multiplicación de matrices en [matrix_output](https://github.com/Benjamin-Daza-Jimenez/INF221-2025-1-TAREA-1-master/tree/main/code/matrix_multiplication/data/matrix_output).

### Scripts

* [matrix_generator.py](https://github.com/Benjamin-Daza-Jimenez/INF221-2025-1-TAREA-1-master/blob/main/code/matrix_multiplication/scripts/matrix_generator.py): genera matrices de distintos tipos y tamaños, almacenándolas en la carpeta matrix_input.

* [plot_generator.py](https://github.com/Benjamin-Daza-Jimenez/INF221-2025-1-TAREA-1-master/blob/main/code/matrix_multiplication/scripts/plot_generator.py): abre los archivos almacenados en measurements y genera un gráfico de tiempo y un gráfico de memoria utilizada por los algoritmos en cada ejecución.

## Ordenamiento de arreglo unidimensional

* mergesort.cpp: busca llamar de forma recursiva a sí misma en sus dos mitades y, a la función Merge encargada de realizar la union. Su objetivo es dividir el arreglo en la mitad hasta que se vuelva un vector de una posición. Utiliza la función Merge para mezclar.

Función Merge: mezcla los arreglos que nos queden restantes considerando el valor de los elementos.

* quicksort.cpp: se llama recursivamente a sí misma y a la función partición, la cual busca el punto medio entre los menores al pivote y los mayores al pivote.

Función particion: busca realizar el sort a partir de un pivote (en este caso el primer elemento del vector). si es mayor avanza j, si es menor avanza j e i.

* selectionsort.cpp: se recorre caso a caso, comparando cada uno de los valores con los siguientes, intercambiando posiciones para luego, junto a una variable aux, cambiar los valores en la lista.

* sort.cpp: función sort de C++.

### Programa principal

* sorting.cpp: recorre archivos generados en array_input, cada iteración del ciclo realiza las operaciones necesarias a cada implementación desde la función prueba.

Función prueba: toma el tiempo en realizar cada algoritmo y su respectivo uso de memoria, esta información es agregada en una linea adicional en el archivo de texto almacenado en measurements. Imprime por pantalla el algoritmo utilizado y la información antes dicha. Finalmente se almacena el resultado del ordenamiento de en array_output.

### Scripts

* array_generator.py: genera arrays de distintos tipos y tamaños, almacenándolas en la carpeta matrix_input.

* plot_generator.py: abre los archivos almacenados en measurements y genera un gráfico de tiempo y un gráfico de memoria utilizada por los algoritmos en cada ejecución

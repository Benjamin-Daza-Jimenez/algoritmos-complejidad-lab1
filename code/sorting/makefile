# Archivos y carpetas
PYTHON_SCRIPT = array_generator.py
PYTHON_PLOT_SCRIPT = plot_generator.py
CPP_SOURCES = sorting.cpp algorithms/mergesort.cpp algorithms/quicksort.cpp algorithms/selectionsort.cpp algorithms/sort.cpp
CPP_EXEC = sorting

# Regla para ejecutar el script Python
run_python:
	cd scripts && python3 $(PYTHON_SCRIPT)

# Regla para compilar el código C++ y ejecutar el programa
run_cpp: run_python
	g++ $(CPP_SOURCES) -o $(CPP_EXEC)
	./$(CPP_EXEC)

# Regla para ejecutar scripts plot Python
run_plot_python: run_cpp
	cd scripts && python3 $(PYTHON_PLOT_SCRIPT)
	
# Regla por defecto para ejecutar todo
run: run_plot_python
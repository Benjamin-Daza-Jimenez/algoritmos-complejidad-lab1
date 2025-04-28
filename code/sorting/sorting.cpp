#include <bits/stdc++.h>
using namespace std;
void Merge(vector<int>&lista, int inicio, int mitad, int final);
void MergeSort(vector<int>&lista,int inicio, int final);
int particion(vector<int>&lista, int inicio, int final);
void QuickSort(vector<int>&lista, int inicio, int final);
void SelectionSort(vector<int>&lista, int n);
vector<int> sortArray(std::vector<int>& arr);

//Lector de memoria
#ifdef _WIN32
    #include <windows.h>
    #include <psapi.h>
    #pragma comment(lib, "Psapi.lib")
#endif
size_t getMemoryUsed(){
    #ifdef _WIN32
        // Windows
        PROCESS_MEMORY_COUNTERS memInfo;
        GetProcessMemoryInfo(GetCurrentProcess(), &memInfo, sizeof(memInfo));
        return memInfo.WorkingSetSize; // bytes
    #else
        // Linux / WSL
        std::ifstream statm("/proc/self/statm");
        long sizePages = 0;
        statm >> sizePages;
        long pageSize = sysconf(_SC_PAGESIZE); // bytes
        return sizePages * pageSize;
    #endif
}

//GLOBAL
string path_input = "data/array_input";
string path_measurements = "data/measurements";
string path_output = "data/array_output";
namespace fs = filesystem;

void carpetas(){
    string merge=path_output+"/mergesort";
    string quick=path_output+"/quicksort";
    string sortt=path_output+"/sort";
    string selection=path_output+"/selectionsort";

    if(!fs::exists(merge)){
        fs::create_directories(merge);
    }
    if(!fs::exists(quick)){
        fs::create_directories(quick);
    }
    if(!fs::exists(sortt)){
        fs::create_directories(sortt);
    }
    if(!fs::exists(selection)){
        fs::create_directories(selection);
    }
}

vector<int> split(string x){ //Función split
    istringstream iss(x);
    vector<int>v;
    string w;
    while(iss >> w){
        v.push_back(stoi(w));
    }
    return v;
}

void prueba(vector<int> v, string tipo, string name, ostream&file){

    auto start = chrono::high_resolution_clock::now(); //Inicio del clock

    if(tipo == "mergesort"){
        MergeSort(v,0,v.size()-1);
    }
    else if(tipo == "quicksort"){
        QuickSort(v,0,v.size()-1);
    }
    else if(tipo == "selectionsort"){
        SelectionSort(v,v.size()-1);
    }
    else{
        sortArray(v);
    }

    size_t memoria=getMemoryUsed()/1024.0;

    auto end = chrono::high_resolution_clock::now(); //Fin del clock
    chrono::duration<double> tiempo = end - start;//Fin-Inicio

    //Guardar archivo en su output correspondiente
    string path_o=path_output+"/"+tipo+"/"+name;
    ofstream archivo(path_o);

    if(archivo.is_open()){
        for(int valor:v){
            archivo<<valor<<" ";
        }
        archivo.close();

        string salida=name+" "+to_string(tiempo.count())+" [S] "+to_string(memoria)+" [KB]"+'\n';
        cout<<tipo<<": ordenó el archivo "<<name<<" en "<<tiempo.count()<<"[S] usando "<<memoria<<"[KB] de memoria."<<endl;

        file<<salida;
        
    }
    else{
        cout<<"No se abre el archivo"<<endl;
    }
}

void no_prueba(string tipo,string name, ostream&file){
    //Guardar archivo en su output correspondiente
    string path_o=path_output+"/"+tipo+"/"+name;
    ofstream archivo(path_o);

    if(tipo=="selectionsort"){
        archivo<<"No se realiza ordenamiento con 10000000 de datos por demora indeterminada (+5 horas).";
        cout<<tipo<<": no ordenó el archivo "<<name<<" por demora indeterminada (+5 horas)."<<endl;
        string salida=name+" - [S] - [KB]"+'\n';
        file<<salida;
    }else{
        archivo<<"No se realiza ordenamiento con 10000000 de datos por Segmentation Fault.";
        cout<<tipo<<": no ordenó el archivo "<<name<<" por Segmentation Fault."<<endl;
        string salida=name+" - [S] - [KB]"+'\n';
        file<<salida;
    }
    archivo.close();
}

int main(){

    //Crea carpetas del output
    carpetas();

    //Abrir archivos de tiempo y memoria
    ofstream file_mergesort(path_measurements+"/mergesort.txt");
    ofstream file_quicksort(path_measurements+"/quicksort.txt");
    ofstream file_selectionsort(path_measurements+"/selectionsort.txt");
    ofstream file_sort(path_measurements+"/sort.txt");

    vector<fs::directory_entry> archivos;
    for (const auto& archivo : fs::directory_iterator(path_input)) {
        archivos.push_back(archivo);
    }
    sort(archivos.begin(), archivos.end(), [](const fs::directory_entry& a, const fs::directory_entry& b) {
        auto get_num = [](const fs::directory_entry& e) {
            string s = e.path().filename().string();
            return stoi(s.substr(0, s.find('_')));
        };
        return get_num(a) < get_num(b);
    });
    

    for(const auto& archivo : archivos){
        ifstream file(archivo.path());
        string nombre_file = archivo.path().filename().string();

        string line;
        getline(file,line);
        vector<int> v = split(line);
        
        //Ordenamiento MergeSort
        prueba(v,"mergesort", nombre_file,file_mergesort);
        //Ordenamiento QuickSort
        if(nombre_file.find("10000000") == string::npos){
            prueba(v,"quicksort", nombre_file,file_quicksort);
        }else{
            no_prueba("quicksort",nombre_file,file_quicksort);
        }
        //Ordenamiento SelectionSort
        if(nombre_file.find("10000000") == string::npos){
            prueba(v,"selectionsort", nombre_file,file_selectionsort);
        }else{
            no_prueba("selectionsort",nombre_file,file_selectionsort);
        }
        //Ordenamiento Sort
        prueba(v,"sort", nombre_file,file_sort);

        file.close();
    }

    file_mergesort.close();
    file_quicksort.close();
    file_selectionsort.close();
    file_sort.close();    
    return 0;
}
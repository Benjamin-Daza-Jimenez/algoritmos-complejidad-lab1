#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> restar(const vector<vector<int>>&A, const vector<vector<int>>&B);
vector<vector<int>> sumar(const vector<vector<int>>&A, const vector<vector<int>>&B);
vector<vector<int>> strassen(const vector<vector<int>>&A, const vector<vector<int>>&B);
void MultiMatrices(vector<vector<int>>m1,vector<vector<int>>m2,vector<vector<int>>&m3);

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
string path_input = "data/matrix_input";
string path_measurements = "data/measurements";
string path_output = "data/matrix_output";
namespace fs = filesystem;

void carpetas(){
    string naive=path_output+"/naive";
    string strassen=path_output+"/strassen";

    if(!fs::exists(naive)){
        fs::create_directories(naive);
    }
    if(!fs::exists(strassen)){
        fs::create_directories(strassen);
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

void prueba(vector<vector<int>> vv1, vector<vector<int>> vv2, string tipo, string n1, string n2, ostream&file){

    auto start = chrono::high_resolution_clock::now(); //Inicio del clock
    vector<vector<int>>vv;
    if(tipo == "naive"){
        vector<vector<int>>vvx(vv1.size(),vector<int>(vv2.size(), 0));
        MultiMatrices(vv1,vv2,vvx);
        vv=vvx;
    }
    else{
        vv = strassen(vv1,vv2);
    }
    size_t memoria=getMemoryUsed()/1024.0;

    auto end = chrono::high_resolution_clock::now(); //Fin del clock
    chrono::duration<double> tiempo = end - start;//Fin-Inicio

    //Guardar archivo en su output correspondiente
    n1=n1.substr(0, n1.find_last_of('.'));
    string path_o=path_output+"/"+tipo+"/"+n1+"x2.txt";
    ofstream archivo(path_o);

    if(archivo.is_open()){
        for(vector<int>v:vv){
            for(int valor:v){
                archivo<<valor<<" ";
            }
            archivo<<'\n';
        }
        archivo.close();

        string salida=n1+"x2 "+to_string(tiempo.count())+" [S] "+to_string(memoria)+" [KB]"+'\n';
        cout<<tipo<<": multiplicó "<<n1<<" x "<<n2<<" en "<<tiempo.count()<<"[S] usando "<<memoria<<"[KB] de memoria."<<endl;

        file<<salida;
        
    }
    else{
        cout<<"No se abre el archivo"<<endl;
    }
}

int main(){
    
    //Crea carpetas del output
    carpetas();

    //Abrir archivos de tiempo y memoria
    ofstream file_naive(path_measurements+"/naive.txt");
    ofstream file_strassen(path_measurements+"/strassen.txt");

    bool flag = true;
    vector<vector<int>>vv1,vv2;
    string nf1,nf2;

    vector<fs::directory_entry> archivos;
    for (const auto& archivo : fs::directory_iterator(path_input)) {
        archivos.push_back(archivo);
    }

    sort(archivos.begin(), archivos.end(), [](const fs::directory_entry& a, const fs::directory_entry& b) {
        auto get_parts = [](const fs::directory_entry& e) {
            string s = e.path().filename().string();
            size_t first_underscore = s.find('_');
            size_t last_underscore = s.rfind('_');
            
            // Extraer n (antes del primer _)
            int n = stoi(s.substr(0, first_underscore));

            // Extraer tipos (entre el primer y el último _)
            string tipo = s.substr(first_underscore + 1, last_underscore - first_underscore - 1);
            
            // Extraer n2 (después del último _)
            int n2 = stoi(s.substr(last_underscore + 1));

            return make_tuple(n, tipo, n2);
        };

        auto [n_a, tipo_a, n2_a] = get_parts(a);
        auto [n_b, tipo_b, n2_b] = get_parts(b);

        // Comparar en el orden: n ascendente, luego tipo (alfabéticamente) y luego n2 (1 antes que 2)
        if (n_a != n_b) {
            return n_a < n_b;
        } else if (tipo_a != tipo_b) {
            return tipo_a < tipo_b;
        } else {
            return n2_a < n2_b;
        }
    });

    for(const auto& archivo : archivos){
        ifstream file(archivo.path());
        string nombre_file = archivo.path().filename().string();
        string line;
        vector<int>v;
        vector<vector<int>>vv;
        while(getline(file,line)){
            v=split(line);
            vv.push_back(v);
        }
        if(flag==true){
            vv1=vv;
            nf1=nombre_file;
            flag=!flag;
        }
        else{
            vv2=vv;
            nf2=nombre_file;
            //Multiplicación Naive
            prueba(vv1,vv2,"naive",nf1,nf2,file_naive);
            //Multiplicación Strassen
            prueba(vv1,vv2,"strassen",nf1,nf2,file_strassen);
            flag=!flag;
        }
        v.clear();
        vv.clear();
        file.close();
    }

    file_naive.close();
    file_strassen.close();

    return 0;
}
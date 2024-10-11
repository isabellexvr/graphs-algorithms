#include <iostream>
#include <vector>
#include <stack>
#include <fstream>
#include <algorithm>
#include <cstring>

using namespace std;

class Graph {
private:
    int vertices; // Número de vértices
    vector<vector<int>> adjList; // Lista de adjacência
    vector<int> index; // Índices dos vértices
    vector<int> lowlink; // Valores de lowlink dos vértices
    vector<bool> onStack; // Marca se um vértice está na pilha
    stack<int> s; // Pilha para armazenar os vértices
    int currentIndex; // Índice atual durante a DFS
    vector<vector<int>> sccs; // Armazena as SCCs encontradas

    void strongconnect(int v) {
        index[v] = currentIndex;
        lowlink[v] = currentIndex;
        currentIndex++;
        s.push(v);
        onStack[v] = true;

        for (int u : adjList[v]) {
            if (index[u] == -1) {
                strongconnect(u);
                lowlink[v] = min(lowlink[v], lowlink[u]);
            } else if (onStack[u]) {
                lowlink[v] = min(lowlink[v], index[u]);
            }
        }

        if (lowlink[v] == index[v]) {
            vector<int> scc;
            int w;
            do {
                w = s.top();
                s.pop();
                onStack[w] = false;
                scc.push_back(w);
            } while (w != v);
            sccs.push_back(scc); 
        }
    }

public:
    Graph(int vertices) : vertices(vertices), adjList(vertices), index(vertices, -1), lowlink(vertices, -1), onStack(vertices, false), currentIndex(0) {}

    void addEdge(int u, int v) {
        adjList[u].push_back(v);
    }

    void findSCCs() {
        for (int v = 0; v < vertices; v++) {
            if (index[v] == -1) {
                strongconnect(v);
            }
        }
    }

    void printSCCs(const std::string &outputFileName) const {
        ofstream outFile(outputFileName);

        if (!outFile.is_open()) {
            std::cerr << "Error opening file: " << outputFileName << std::endl;
            return; 
        }

        for (const auto& scc : sccs) {
            for (int v : scc) {
                cout << v+1 << " ";
                outFile << v+1 << " ";
            }
            cout << endl;
            outFile << endl;
        }

        outFile.close();
    }
};

void help(){
    cout << "-h : mostra o help" << endl;
    cout << "-o <arquivo> : redireciona a saida para o ‘‘arquivo’’" << endl;
    cout << "-f <arquivo> : indica o ‘‘arquivo’’ que contém o grafo de entrada" << endl;
}

void readInputFile(const string &filename, const string &outputFileName){
    ifstream file(filename);
    int n,m;

    file >> n >> m;
    Graph g(n);

    for (int i = 0; i < m; i++){
        int u,v;
        file >> u >> v;
        g.addEdge(u - 1, v - 1);
    }

    g.findSCCs();
    g.printSCCs(outputFileName);

}

int main(int argc, char const *argv[]){

    string outputFileName, inputFileName;

    for (int i = 1; i < argc; i++){

        if(strcmp(argv[i], "-h") == 0){
            help();

        }else if(strcmp(argv[i], "-o") == 0){
            outputFileName = argv[i + 1];

        }else if(strcmp(argv[i], "-f") == 0){
            inputFileName = argv[i + 1];

        }
    }

    if(outputFileName.empty()){
        outputFileName = "output.bin";
    }

    if(inputFileName.empty()){
        std::cerr << "No input file was specified." << std::endl;
        return 1;
    }else{
        readInputFile(inputFileName, outputFileName);
    }

    return 0;
}

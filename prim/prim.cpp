#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <cstring>
#include <fstream>

using namespace std;

typedef pair<int, int> Edge;

class Graph {
private:
    int n;
    vector<vector<Edge>> adjList;

public:

    Graph(int n) {
        this->n = n;
        adjList.resize(n); // Inicializa a lista de adjacência com 'n' vértices
    }

    void addEdge(int u, int v, int weight) {
        adjList[u].push_back({v, weight});
        adjList[v].push_back({u, weight});
    }

    void primMST(int start, bool solution) {
        vector<int> custo(n, INT_MAX);
        vector<int> prev(n, -1);
        vector<bool> inMST(n, false);

        priority_queue<Edge, vector<Edge>, greater<Edge>> pq;

        pq.push({0, start});
        custo[start] = 0;

        while (!pq.empty()) {
            int v = pq.top().second;
            pq.pop();

            if (inMST[v]) continue;

            inMST[v] = true;

            for (auto &edge : adjList[v]) {
                int u = edge.first; 
                int peso = edge.second;

                if (!inMST[u] && custo[u] > peso) {
                    custo[u] = peso;
                    prev[u] = v;

                    pq.push({custo[u], u});
                }
            }
        }

        if (solution) {
            for (int i = 0; i < n; ++i) {
                if (prev[i] != -1) {
                    cout << "(" << prev[i] + 1 << "," << i + 1 << ") ";
                }
            }
            cout << endl;
        } else {
            int totalWeight = 0;
            for (int i = 0; i < n; ++i) {
                if (prev[i] != -1) {
                    totalWeight += custo[i];
                }
            }
            cout << totalWeight << endl;
        }


    }

    void printGraph() {
        cout << "Grafo (Lista de Adjacência):\n";
        for (int i = 0; i < n; ++i) {
            cout << i << ": ";
            for (const auto& edge : adjList[i]) {
                cout << "(" << edge.first << ", " << edge.second << ") ";
            }
            cout << endl;
        }
    }
};

void help(){
    cout << "-h : mostra o help" << endl;
    cout << "-o <arquivo> : redireciona a saida para o ‘‘arquivo’’" << endl;
    cout << "-f <arquivo> : indica o ‘‘arquivo’’ que contém o grafo de entrada" << endl;
    cout << "-s : mostra a solução" << endl;
    cout << "-i : vértice inicial (para o algoritmo de Prim)" << endl;
}

void readInputFile(const string &filename, const string &outputFileName, int start, bool solution){
    ifstream file(filename);
    int n,m;

    file >> n >> m;
    Graph g(n);

    for (int i = 0; i < m; i++){
        int u, v, w;
        file >> u >> v >> w;
        g.addEdge(u - 1, v - 1, w);
    }

    g.primMST(start, solution);

}

int main(int argc, char const *argv[]) {
    string outputFileName, inputFileName;
    int solution = 0, start = 0;

    for (int i = 1; i < argc; i++){

        if(strcmp(argv[i], "-h") == 0){
            help();

        }else if(strcmp(argv[i], "-o") == 0){
            outputFileName = argv[i + 1];

        }else if(strcmp(argv[i], "-f") == 0){
            inputFileName = argv[i + 1];

        } else if(strcmp(argv[i], "-s") == 0){
            solution = 1  ;

        } else if(strcmp(argv[i], "-i") == 0){
           start = atoi(argv[i + 1]);

        }
    }

    if(outputFileName.empty()){
        outputFileName = "output.bin";
    }
    
    if(inputFileName.empty()){
        std::cerr << "No input file was specified." << std::endl;
        return 1;
    }

    readInputFile(inputFileName, outputFileName, start, solution);

    return 0;
}

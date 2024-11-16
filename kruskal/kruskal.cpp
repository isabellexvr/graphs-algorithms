#include <iostream>
#include <vector>
#include <queue> // Para usar a fila de prioridade (min-heap)
#include "grafo.h"
#include <climits>
#include <fstream>
#include <limits>
#include <cstring>

using namespace std;

// Comparador para min-heap (ordem crescente de peso)
struct ComparadorAresta {
    bool operator()(const Edge &a, const Edge &b) {
        return a.peso > b.peso;  // Retorna verdadeiro se 'a' for maior que 'b' (min-heap)
    }
};

class UnionFind {
private:
    vector<int> parent;
    vector<int> rank;

public:
    UnionFind(int n) {
        parent.resize(n + 1);
        rank.resize(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            parent[i] = i; // Cada vértice é seu próprio pai inicialmente
        }
    }

    int find(int v) {
        if (parent[v] != v) {
            parent[v] = find(parent[v]); // Compressão de caminho
        }
        return parent[v];
    }

    void union_sets(int u, int v) {
        int root_u = find(u);
        int root_v = find(v);

        if (root_u != root_v) {
            // União por rank
            if (rank[root_u] < rank[root_v]) {
                parent[root_u] = root_v;
            } else if (rank[root_u] > rank[root_v]) {
                parent[root_v] = root_u;
            } else {
                parent[root_v] = root_u;
                rank[root_u]++;
            }
        }
    }
};

void help() {
    cout << "-h : mostra o help" << endl;
    cout << "-o <arquivo> : redireciona a saída para o ‘‘arquivo’’" << endl;
    cout << "-f <arquivo> : indica o ‘‘arquivo’’ que contém o grafo de entrada" << endl;
    cout << "-s : mostra a solução" << endl;
    cout << "-i : vértice inicial" << endl;
}

void readInputFile(const string &inputFileName, const string &outputFileName, bool s) {
    ifstream inputFile(inputFileName);
    ofstream outputFile(outputFileName);

    int n, m;
    inputFile >> n >> m;

    Grafo adj(n);

    // Usando uma fila de prioridade (min-heap) para ordenar as arestas
    priority_queue<Edge, vector<Edge>, ComparadorAresta> minHeap;

    int u, v, peso;
    while (inputFile >> u >> v >> peso) {
        // Adiciona aresta ao grafo
        adj.add_edge(u, v, peso);

        Edge novaAresta(u, v, peso);
        minHeap.push(novaAresta);  // Insere a aresta na min-heap
    }

    // Continua com o código normal de processamento do MST...
    Grafo mst(n);
    UnionFind uf(n);

    int custo_total = 0;

    // Processa as arestas da min-heap (extração da aresta com menor peso)
    while (!minHeap.empty()) {
        Edge aresta = minHeap.top();
        minHeap.pop();

        // Verifica se a adição da aresta formaria um ciclo
        if (uf.find(aresta.u) != uf.find(aresta.v)) {
            mst.add_edge(aresta.u, aresta.v, aresta.peso); // Adiciona a aresta ao MST
            uf.union_sets(aresta.u, aresta.v); // Une os conjuntos
            custo_total += aresta.peso;
        }
        // Caso contrário, a aresta é ignorada (não é adicionada ao MST)
    }

    // Mostra a solução ou escreve no arquivo de saída
    if (s) {
        for (const auto& edge : mst.get_edges()) {
            outputFile << "(" << edge.u << "," << edge.v << ") ";
            cout << "(" << edge.u << "," << edge.v << ") ";
        }
        cout << endl;
    } else {
        outputFile << custo_total;
        cout << custo_total << endl;
    }

    inputFile.close();
    outputFile.close();
}


int main(int argc, char const *argv[]) {
    string outputFileName, inputFileName;
    int initialVertex = 1, showSolution = false; // vértice inicial vindo do user pelo "-i"

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0) {
            help();
        } else if (strcmp(argv[i], "-o") == 0) {
            outputFileName = argv[i + 1];
        } else if (strcmp(argv[i], "-f") == 0) {
            inputFileName = argv[i + 1];
        } else if (strcmp(argv[i], "-i") == 0) {
            initialVertex = stoi(argv[i + 1]);
            cout << initialVertex << endl;
        } else if (strcmp(argv[i], "-s") == 0) {
            showSolution = true;
        }
    }

    if (outputFileName.empty()) {
        outputFileName = "output.bin";
    }

    if (inputFileName.empty()) {
        cerr << "No input file was specified." << endl;
        return 1;
    } else {
        readInputFile(inputFileName, outputFileName, showSolution);
    }

    return 0;
}

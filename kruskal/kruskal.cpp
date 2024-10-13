#include <iostream>
#include <vector>
#include "grafo.h"
#include <climits>
#include <queue>
#include <fstream>
#include <limits>
#include <cstring>

using namespace std;

class UnionFind {
private:
    std::vector<int> parent;
    std::vector<int> rank;

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


void help(){
    cout << "-h : mostra o help" << endl;
    cout << "-o <arquivo> : redireciona a saida para o ‘‘arquivo’’" << endl;
    cout << "-f <arquivo> : indica o ‘‘arquivo’’ que contém o grafo de entrada" << endl;
    cout << "-s : mostra a solução" << endl;
    cout << "-i : vértice inicial";
}


void readInputFile(const string &inputFileName, const string &outputFileName, bool s){

    ifstream inputFile(inputFileName);
    ofstream outputFile(outputFileName);

    int n, m;
    inputFile >> n >> m;

    Grafo adj(n);

    int u, v, peso;
    while (inputFile >> u >> v >> peso) {
        adj.add_edge(u, v, peso);
    }

    adj.ordernarArestas();

    auto edges = adj.get_edges(); 
    Grafo mst(n);
    UnionFind uf(n);

    int custo_total = 0;

    // Adiciona arestas ao MST
    for (size_t i = 0; i < edges.size(); ++i) {
        const auto& edge = edges[i];
        
        // Verifica se a adição da aresta formaria um ciclo
        if (uf.find(edge.u) != uf.find(edge.v)) {
            mst.add_edge(edge.u, edge.v, edge.peso); // Adiciona a aresta ao MST
            uf.union_sets(edge.u, edge.v); // Une os conjuntos
            custo_total += edge.peso;
        }
        // Caso contrário, a aresta é ignorada (não é adicionada ao MST)
    }

    if(s){
        for (const auto& edge : mst.get_edges()) {
            outputFile << "(" << edge.u << "," << edge.v << ") ";
            std::cout << "(" << edge.u << "," << edge.v << ") ";
        }
        cout<<endl;
    }else{
        outputFile<<custo_total;
        cout<<custo_total<<endl;        
    }


    inputFile.close();
    outputFile.close();
}


int main(int argc, char const *argv[])
{

    string outputFileName, inputFileName;
    int initialVertex = 1, showSolution = false; // vértice inicial vindo do user pelo "-i"

    for (int i = 1; i < argc; i++){

        if(strcmp(argv[i], "-h") == 0){
            help();

        }else if(strcmp(argv[i], "-o") == 0){
            outputFileName = argv[i + 1];

        }else if(strcmp(argv[i], "-f") == 0){
            inputFileName = argv[i + 1];

        } else if(strcmp(argv[i], "-i")==0){
            initialVertex = stoi(argv[i+1]);
            cout << initialVertex << endl;
        }else if(strcmp(argv[i], "-s")==0){
            showSolution = true;
        }
    }

    if(outputFileName.empty()){
        outputFileName = "output.bin";
    }


    if(inputFileName.empty()){
        std::cerr << "No input file was specified." << std::endl;
        return 1;
    }else{ 
        readInputFile(inputFileName, outputFileName, showSolution);
    }


    return 0;
}

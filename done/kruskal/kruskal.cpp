#include <iostream>
#include <vector>
#include "grafo.h"
#include <climits>
#include <queue>
#include <fstream>
#include <limits>

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

int main(int argc, char const *argv[])
{
    ifstream arquivo("entrada.dat");

    if (!arquivo) {
        std::cerr << "Erro ao abrir o arquivo." << std::endl;
        return 1;
    }

    int n, m;
    arquivo >> n >> m;

    Grafo adj(n);

    int u, v, peso;
    while (arquivo >> u >> v >> peso) {
        adj.add_edge(u, v, peso);
    }

    adj.ordernarArestas();

    const auto& edges1 = adj.get_edges(); // Obtém as arestas do grafo
    for (const auto& edge : edges1) {
        std::cout << edge.u << " " << edge.v << ", Peso: " << edge.peso << std::endl;
    }

    auto edges = adj.get_edges(); 
    Grafo mst(n);
    UnionFind uf(n);

    // Adiciona arestas ao MST
    for (size_t i = 0; i < edges.size(); ++i) {
        const auto& edge = edges[i];
        
        // Verifica se a adição da aresta formaria um ciclo
        if (uf.find(edge.u) != uf.find(edge.v)) {
            mst.add_edge(edge.u, edge.v, edge.peso); // Adiciona a aresta ao MST
            uf.union_sets(edge.u, edge.v); // Une os conjuntos
        }
        // Caso contrário, a aresta é ignorada (não é adicionada ao MST)
    }

    //cout << "\nArestas do MST:" << endl;
    for (const auto& edge : mst.get_edges()) {
        std::cout << "(" << edge.u << "," << edge.v << ") ";
    }

    cout<<endl;

    arquivo.close();
    return 0;
}

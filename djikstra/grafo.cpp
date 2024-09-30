#include "grafo.h"

Grafo::Grafo(int n) : n(n), adj(n+1){}

void Grafo::add_edge(int u, int v, double peso){
    adj[u].emplace_back(v, peso);
    adj[v].emplace_back(u, peso);
}

void Grafo::print_graph() const {
    for (int i = 1; i <= n; ++i) {
        std::cout << i << ": ";
        for (const auto& [vizinho, peso] : adj[i]) {
            std::cout << "(" << vizinho << ", " << peso << ") ";
        }
        std::cout << std::endl;
    }
}

std::vector<std::pair<int, int>> Grafo::N(int vertice) const {
    return adj[vertice]; // Retorna os vizinhos e seus pesos
}
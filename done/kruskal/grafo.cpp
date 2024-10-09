#include "grafo.h"
#include <algorithm>

Grafo::Grafo(int n) : n(n), adj(n+1){}

void Grafo::add_edge(int u, int v, double peso){
    adj[u].emplace_back(v, peso);
    adj[v].emplace_back(u, peso);
    edges.emplace_back(u, v, peso);
}

void Grafo::print_graph() const {
    for (int i = 0; i <= n; ++i) {
        std::cout << i << ": ";
        for (const auto& [vizinho, peso] : adj[i]) {
            std::cout << "(" << vizinho << ", " << peso << ") ";
        }
        std::cout << std::endl;
    }
}

bool Grafo::compararArestas(const Edge& a1, const Edge& a2) {
    return a1.peso < a2.peso; // Ordena por peso
}

void Grafo::ordernarArestas() {
    std::sort(edges.begin(), edges.end(), [this](const Edge& a1, const Edge& a2) {
        return this->compararArestas(a1, a2);
    });
}

std::vector<std::pair<int, int>> Grafo::N(int vertice) const {
    return adj[vertice]; // Retorna os vizinhos e seus pesos
}

const std::vector<Edge>& Grafo::get_edges() const {
    return edges;
}


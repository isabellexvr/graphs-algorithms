#ifndef GRAFO_H
#define GRAFO_H

#include <vector>
#include <iostream>

struct Edge{
    int u, v, peso;

    Edge(int u, int v, int peso) : u(u), v(v), peso(peso) {}
};

class Grafo {
private:
    int n; // Número de vértices
    std::vector<std::vector<std::pair<int, int>>> adj; // Lista de adjacências
    std::vector<Edge> edges;
    //std::vector<int>pai(n+1);

public:
    // Construtor: inicializa o grafo com n vértices
    Grafo(int n);

    // Adiciona uma aresta entre dois vértices
    void add_edge(int u, int v, double peso);

    // Imprime o grafo
    void print_graph() const;

    // Vizinho
    std::vector<std::pair<int, int>> N(int vertice) const;

    bool compararArestas(const Edge& a1, const Edge& a2);

    void ordernarArestas();
    
    const std::vector<Edge>& get_edges() const;
    

};

#endif // GRAFO_H

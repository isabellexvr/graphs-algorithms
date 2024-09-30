#ifndef GRAFO_H
#define GRAFO_H

#include <vector>
#include <iostream>

class Grafo {
private:
    int n; // Número de vértices
    std::vector<std::vector<std::pair<int, int>>> adj; // Lista de adjacências

public:
    // Construtor: inicializa o grafo com n vértices
    Grafo(int n);

    // Adiciona uma aresta entre dois vértices
    void add_edge(int u, int v, double peso);

    // Imprime o grafo
    void print_graph() const;

    // Vizinho
    std::vector<std::pair<int, int>> N(int vertice) const; 
};

#endif // GRAFO_H

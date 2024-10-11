#include <iostream>
#include <vector>
#include <queue>
#include <climits> // Para INT_MAX
using namespace std;

// Define uma aresta como um par de (vértice, peso)
typedef pair<int, int> Edge;

class Graph {
private:
    int n; // Número de vértices
    vector<vector<Edge>> adjList; // Lista de adjacência

public:
    // Construtor
    Graph(int n) {
        this->n = n;
        adjList.resize(n); // Inicializa a lista de adjacência com 'n' vértices
    }

    // Função para adicionar uma aresta ao grafo
    void addEdge(int u, int v, int weight) {
        adjList[u].push_back({v, weight}); // Aresta de u para v
        adjList[v].push_back({u, weight}); // Aresta de v para u (grafo não-direcionado)
    }

    // Função que implementa o algoritmo de Prim
    void primMST(int start) {
        // Vetor de custos: inicializado com valores infinitos
        vector<int> custo(n, INT_MAX);
        // Vetor de predecessores
        vector<int> prev(n, -1);
        // Vetor para marcar os vértices já incluídos na árvore geradora mínima
        vector<bool> inMST(n, false);

        // Fila de prioridade mínima: armazena pares (custo, vértice)
        priority_queue<Edge, vector<Edge>, greater<Edge>> pq;

        // Começamos pelo vértice inicial, com custo 0
        pq.push({0, start});
        custo[start] = 0;

        while (!pq.empty()) {
            // Extraímos o vértice com o menor custo
            int v = pq.top().second;
            pq.pop();

            // Se o vértice já está na árvore, ignoramos
            if (inMST[v]) continue;

            // Marcamos o vértice como incluído na árvore
            inMST[v] = true;

            // Percorremos todos os vizinhos de 'v'
            for (auto &edge : adjList[v]) {
                int u = edge.first;  // Vértice adjacente
                int peso = edge.second;  // Peso da aresta v-u

                // Se 'u' ainda não está na árvore e o peso é menor que o custo atual
                if (!inMST[u] && custo[u] > peso) {
                    // Atualizamos o custo e o predecessor de 'u'
                    custo[u] = peso;
                    prev[u] = v;
                    // Inserimos o novo custo na fila de prioridade
                    pq.push({custo[u], u});
                }
            }
        }

        // Exibir o resultado da árvore geradora mínima
        cout << "Arestas da Árvore Geradora Mínima:\n";
        for (int i = 0; i < n; ++i) {
            if (prev[i] != -1) {
                cout << prev[i] << " - " << i << "  com peso: " << custo[i] << endl;
            }
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

int main() {
    int n = 7;

    Graph g(n);

    g.addEdge(0,1,2);
    g.addEdge(0,4,4);
    g.addEdge(0,5,5);
    g.addEdge(1,4,1);
    g.addEdge(1,3,3);
    g.addEdge(1,2,7);
    g.addEdge(1,6,4);
    g.addEdge(1,5,8);
    g.addEdge(3,2,10);
    g.addEdge(3,4,2);
    g.addEdge(2,6,6);
    g.addEdge(6,5,1);

    g.printGraph();

    g.primMST(0);

    return 0;
}

#include <iostream>
#include <vector>
#include <stack>
#include <fstream>
using namespace std;

class Graph {
private:
    int numVertices;             // Número de vértices no grafo
    vector<vector<int>> adjList; // Lista de adjacências (vetor de vetores)

public:
    // Construtor: Inicializa o grafo com um número de vértices
    Graph(int vertices)
    {
        numVertices = vertices;
        adjList.resize(vertices); // Redimensiona a lista de adjacências
    }

    int getNumVertices() {
        return numVertices;
    }

    // Função para adicionar uma aresta ao grafo direcionado (somente src -> dest)
    void addEdge(int src, int dest)
    {
        adjList[src].push_back(dest); // Adiciona a aresta de origem para destino
    }

    // Função para realizar a busca em profundidade (DFS) e empilhar os vértices na ordem de término
    void dfsOriginalGraph(int vertex, vector<bool>& visitedVertices, stack<int>& firstDFSVisits)
    {
        visitedVertices[vertex] = true;     // Marca o vértice atual como visitado

        for (int adj : adjList[vertex])
        {                                   // Para cada vértice adjacente
            if (!visitedVertices[adj])
            {                               // Se ainda não foi visitado
                dfsOriginalGraph(adj, visitedVertices, firstDFSVisits); // Faz uma chamada recursiva
            }
        }

        firstDFSVisits.push(vertex);        // Empilha o vértice ao final da DFS
    }

    // Função para inverter o grafo
    Graph reverseGraph()
    {
        Graph reversedGraph(numVertices);

        for (int i = 0; i < numVertices; i++)
        {
            for (int j : adjList[i])
            {
                reversedGraph.addEdge(j, i); // Inverte as arestas
            }
        }

        return reversedGraph;
    }

    // Função para realizar a DFS e imprimir os vértices de uma SCC
    void dfsOnReversedGraph(int vertex, vector<bool>& visitedVertices)
    {
        visitedVertices[vertex] = true;     // Marca o vértice atual como visitado
        cout << vertex + 1 << " ";              // Imprime o vértice atual (pertencente à SCC)

        for (int adj : adjList[vertex])
        {
            if (!visitedVertices[adj])
            {
                dfsOnReversedGraph(adj, visitedVertices); // Continua a DFS no grafo invertido
            }
        }
    }

    // Função para exibir a lista de adjacências do grafo
    void printGraph()
    {
        for (int i = 0; i < numVertices; i++)
        {
            cout << "Vértice " << i + 1 << ":";
            for (int j : adjList[i])
            {
                cout << " -> " << j + 1;
            }
            cout << endl;
        }
    }

    // Função para gerar um novo vetor de visitados
    vector<bool> createVisitedVector()
    {
        return vector<bool>(numVertices, false); // Retorna um novo vetor de visitados
    }
};

// Função que implementa o algoritmo de Kosaraju
int kosaraju(Graph& graph)
{
    stack<int> firstDFSVisits;
    vector<bool> visited = graph.createVisitedVector(); // Vetor de visitados para a primeira DFS

    // Primeira DFS para empilhar vértices de acordo com a ordem de término
    for (int i = 0; i < graph.getNumVertices(); i++)
    {
        if (!visited[i])
        {
            graph.dfsOriginalGraph(i, visited, firstDFSVisits);
        }
    }

    // Inverte o grafo
    Graph reversedGraph = graph.reverseGraph();

    // Reseta o vetor de visitados para a segunda DFS
    visited = reversedGraph.createVisitedVector();
    int components = 0;

    // Processa os vértices na ordem do topo da pilha
    while (!firstDFSVisits.empty())
    {
        int v = firstDFSVisits.top();
        firstDFSVisits.pop();

        // Se o vértice ainda não foi visitado no grafo invertido, processa a SCC
        if (!visited[v])
        {
            reversedGraph.dfsOnReversedGraph(v, visited); // Segunda DFS no grafo invertido
            cout << endl;
            components++;
        }
    }

    return components; // Retorna o número de componentes fortemente conectadas 
}

int main()
{
    ifstream file("entrada.dat");

    if (!file) {
        std::cerr << "An error occurred on trying to open the file." << std::endl;
        return 1;
    }

    int n, m;
    file >> n >> m;

    Graph g(n);

    for (int i = 0; i < m; i++){
        int u, v;
        file >> u >> v;
        g.addEdge(u - 1, v - 1);
    }

    kosaraju(g);

    return 0;
}

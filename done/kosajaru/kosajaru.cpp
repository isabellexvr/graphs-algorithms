#include <iostream>
#include <vector>
#include <stack>
#include <fstream>
#include <algorithm>
#include <cstring>

using namespace std;

class Graph
{
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

    int getNumVertices()
    {
        return numVertices;
    }

    // Método para imprimir o grafo (lista de adjacências)
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

    // Função para adicionar uma aresta ao grafo direcionado (somente src -> dest)
    void addEdge(int src, int dest)
    {
        adjList[src].push_back(dest); // Adiciona a aresta de origem para destino
    }

    // Método para imprimir o vetor de vértices visitados
    void printVisited(const vector<bool> &visitedVertices)
    {
        for (int i = 0; i < visitedVertices.size(); i++)
        {
            cout << "Vértice " << i + 1 << ": " << (visitedVertices[i] ? "Visitado" : "Não Visitado") << endl;
        }
    }

    // Função para realizar a busca em profundidade (DFS) e empilhar os vértices na ordem de término
    void dfsOriginalGraph(int vertex, vector<bool> &visitedVertices, stack<int> &firstDFSVisits)
    {
        visitedVertices[vertex] = true; // Marca o vértice atual como visitado

        for (int adj : adjList[vertex])
        { // Para cada vértice adjacente
            if (!visitedVertices[adj])
            {                                                           // Se ainda não foi visitado
                dfsOriginalGraph(adj, visitedVertices, firstDFSVisits); // Faz uma chamada recursiva
            }
        }

        firstDFSVisits.push(vertex); // Empilha o vértice ao final da DFS
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
    void dfsOnReversedGraph(int vertex, vector<bool> &visitedVertices, vector<int> &scc)
    {
        // cout << "vertex: " << vertex << endl;
        visitedVertices[vertex] = true; // Marca o vértice atual como visitado
        scc.push_back(vertex + 1);      // Adiciona o vértice ao componente atual

        // cout << "a: " << vertex << endl;
        // cout << "adjList size: " << adjList.size() << endl;
        for (int adj : adjList[vertex])
        {
            // cout << "b: " << adj << endl;
            if (!visitedVertices[adj])
            {
                // cout << "debug\n";
                dfsOnReversedGraph(adj, visitedVertices, scc); // Continua a DFS no grafo invertido
            }
        }
    }

    // Função para gerar um novo vetor de visitados
    vector<bool> createVisitedVector()
    {
        return vector<bool>(numVertices + 1, false); // Retorna um novo vetor de visitados
    }
};

// Função que implementa o algoritmo de kosajaru
int kosajaru(Graph &graph, const std::string &filename)
{
    std::ofstream outFile(filename);

    if (!outFile.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return -1; 
    }

    stack<int> firstDFSVisits;
    vector<bool> visited = graph.createVisitedVector(); 

    for (int i = 0; i < graph.getNumVertices(); i++)
    {
        if (!visited[i])
        {
            graph.dfsOriginalGraph(i, visited, firstDFSVisits);
        }
    }

    // Reverse the graph
    Graph reversedGraph = graph.reverseGraph();

    // Reset the visited vector for the second DFS
    visited = reversedGraph.createVisitedVector();
    int components = 0;

    // Process vertices in order from the stack
    while (!firstDFSVisits.empty())
    {
        int v = firstDFSVisits.top();
        firstDFSVisits.pop();

        // If the vertex is not visited in the reversed graph, process the SCC
        if (!visited[v])
        {
            vector<int> scc;                                   // Store vertices of the strongly connected component
            reversedGraph.dfsOnReversedGraph(v, visited, scc); // Second DFS on the reversed graph

            // Sort the component to ensure correct output order
            sort(scc.begin(), scc.end());

            // Write the strongly connected component to the file
            for (int vertex : scc)
            {
                cout << vertex << " ";
                outFile << vertex << " ";
            }
            cout << endl;
            outFile << endl;

            components++;
        }
    }

    outFile.close(); // Close the file after writing
    return components; // Return the number of strongly connected components
}

void help(){
    cout << "-h : mostra o help" << endl;
    cout << "-o <arquivo> : redireciona a saida para o ‘‘arquivo’’" << endl;
    cout << "-f <arquivo> : indica o ‘‘arquivo’’ que contém o grafo de entrada" << endl;
}

void readInputFile(const string &filename, const string &outputFileName){
    ifstream file(filename);
    int n,m;

    file >> n >> m;
    Graph g(n);

    for (int i = 0; i < m; i++){
        int u,v;
        file >> u >> v;
        g.addEdge(u - 1, v - 1);
    }

    kosajaru(g, outputFileName);

}

int main(int argc, char const *argv[]){

    string outputFileName, inputFileName;

    for (int i = 1; i < argc; i++){

        if(strcmp(argv[i], "-h") == 0){
            help();

        }else if(strcmp(argv[i], "-o") == 0){
            outputFileName = argv[i + 1];

        }else if(strcmp(argv[i], "-f") == 0){
            inputFileName = argv[i + 1];

        }
    }

    if(outputFileName.empty()){
        outputFileName = "output.bin";
    }

    if(inputFileName.empty()){
        std::cerr << "No input file was specified." << std::endl;
        return 1;
    }else{
        readInputFile(inputFileName, outputFileName);
    }


    return 0;
}

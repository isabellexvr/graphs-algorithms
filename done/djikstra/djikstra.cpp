#include <iostream>
#include <vector>
#include "grafo.h"
#include <climits>
#include <queue>
#include <fstream>
#include <limits>
#include <sstream>

using namespace std;


vector<double> djikstra(Grafo & grafo, int vn, vector<double> & dist){
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    
    queue<int> visited;

    pq.emplace(0, vn); //peso, vértice inicial
    dist[vn] = 0; //distancia dele pra ele: 0

    while(!pq.empty()){
        int currentDist = pq.top().first;
        int currentV = pq.top().second;
        pq.pop();

        if(currentDist > dist[currentV]){
            continue;
        }

        for(const auto& [vizinho, peso] : grafo.N(currentV)){
            int novaDist = currentDist + peso;
            if(novaDist<dist[vizinho]){
                dist[vizinho] = novaDist;
                pq.emplace(novaDist, vizinho);
            }
        }
    }

    return dist;
    
}

int main(int argc, char const *argv[])
{
    ifstream arquivo("entrada.dat");

    if (!arquivo) {
        std::cerr << "Erro ao abrir o arquivo." << std::endl;
        return 1;
    }

    int n, m;
    arquivo >> n >> m;
    arquivo.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignora o resto da linha

    Grafo adj(n);
    
    vector<double> dist(n+1, std::numeric_limits<double>::max());
    
    string line;
    while (getline(arquivo, line)) {
        stringstream ss(line);
        int u, v, peso = 1;

        ss >> u >> v;  // Lê os dois primeiros valores (u e v)

        if (ss >> peso) {
            // Caso exista um terceiro valor, ele é usado como peso
        }

        adj.add_edge(u, v, peso);
    }

    int origem = 1;
    djikstra(adj, origem, dist);

    //std::cout << "Distâncias a partir do vértice " << origem << ":" << std::endl;
    for (int i = 1; i <= n; ++i) {
        if (dist[i] == std::numeric_limits<double>::max()) {
            std::cout << i << ":"<< -1 << " ";
        } else {
            std::cout << i << ":" << dist[i] << " ";
        }
    }

    cout << std::endl;

    arquivo.close();

    return 0;
}


    /* for (int i = 0; i < m; i++) {
        int u, v;
        arquivo >> u >> v;
        g.addEdge(u, v);
    } */
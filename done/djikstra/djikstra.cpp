#include <iostream>
#include <vector>
#include "grafo.h"
#include <climits>
#include <queue>
#include <fstream>
#include <limits>

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

    Grafo adj(n);
    
    vector<double> dist(n+1, std::numeric_limits<double>::max());
    
    int u, v, peso;
    while (arquivo >> u >> v >> peso) {
        adj.add_edge(u, v, peso);
    }


    int origem = 1;
    djikstra(adj, origem, dist);

    std::cout << "Distâncias a partir do vértice " << origem << ":" << std::endl;
    for (int i = 0; i <= n; ++i) {
        if (dist[i] == std::numeric_limits<double>::max()) {
            std::cout << "Vértice " << i << ": "<< -1 << std::endl;
        } else {
            std::cout << "Vértice " << i << ": " << dist[i] << std::endl;
        }
    }

    arquivo.close();

    return 0;
}

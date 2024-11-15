#include <iostream>
#include <vector>
#include "grafo.h"
#include <climits>
#include <queue>
#include <fstream>
#include <limits>
#include <sstream>
#include <cstring>

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

void help(){
    cout << "-h : mostra o help" << endl;
    cout << "-o <arquivo> : redireciona a saida para o ‘‘arquivo’’" << endl;
    cout << "-f <arquivo> : indica o ‘‘arquivo’’ que contém o grafo de entrada" << endl;
    cout << "-i : vértice inicial";
}


void readInputFile(const string &inputFileName, const string &outputFileName, int initial){

    ifstream inputFile(inputFileName);
    ofstream outputFile(outputFileName);

    int n, m;
    inputFile >> n >> m;


    Grafo adj(n);

    vector<double> dist(n+1, std::numeric_limits<double>::max());

    string line;



    while (getline(inputFile, line)) {
        stringstream ss(line);

        int u, v, w = 1; // u, v e w

        if (!(ss >> u >> v)) {
            //cerr << "Error: Failed to extract u or v from the line: " << line << endl;
            continue;  // Skip this line
        }

        if (!(ss >> w)) {
            w = 1;  // Default weight if not present
        }


        ss >> u >> v;  // Lê os dois primeiros valores (u e v)

        if (ss >> w) {
            // Caso exista um terceiro valor, ele é usado como w
        }


        adj.add_edge(u, v, w);
    }

    int origem = initial;
    djikstra(adj, origem, dist);

    for (int i = 1; i <= n; ++i) {
        if (dist[i] == std::numeric_limits<double>::max()) {
            std::cout << i << ":"<< -1 << " ";
            outputFile << i << ":" << -1 << " ";
        } else {
            std::cout << i << ":" << dist[i] << " ";
            outputFile << i << ":" << dist[i] << " ";
        }
    }

    cout << std::endl;

    inputFile.close();
    outputFile.close();
}


int main(int argc, char const *argv[])
{

    string outputFileName, inputFileName;
    int initialVertex = 1; // vértice inicial vindo do user pelo "-i"

    for (int i = 1; i < argc; i++){

        if(strcmp(argv[i], "-h") == 0){
            help();

        }else if(strcmp(argv[i], "-o") == 0){
            outputFileName = argv[i + 1];

        }else if(strcmp(argv[i], "-f") == 0){
            inputFileName = argv[i + 1];

        } else if(strcmp(argv[i], "-i")==0){
            initialVertex = stoi(argv[i+1]);
            cout << initialVertex << endl;
        }
    }

    if(outputFileName.empty()){
        outputFileName = "output.bin";
    }


    if(inputFileName.empty()){
        std::cerr << "No input file was specified." << std::endl;
        return 1;
    }else{ 
        readInputFile(inputFileName, outputFileName, initialVertex);
    }


    return 0;
}

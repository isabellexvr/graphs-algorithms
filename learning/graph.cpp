//Monitoria prática de Teoria dos Grafos - Estruturas e busca
#include<bits/stdc++.h>
using namespace std;

int cont = 0;

void bfs( vector<vector<int>>&grafo, vector<int>&pai, int V, int v){ 
	queue<int> q;//Estrutura de dados fila
	vector<bool> visited(V+1, false);//Vetor de visitados

	visited[v] = true;
	pai[v] = 0;
	q.push(v);

	while(not q.empty()){
		int s = q.front(); q.pop();
		for(auto vertice : grafo[s]){
			if(not visited[vertice]){
				visited[vertice] = true;
				pai[vertice] = s;
				q.push(vertice);
			}
		}
	}
}

void dfs_rec(vector<vector<int>> & grafo, vector<int> & pre, vector<int> & pai, int v){
	pre[v] = cont++;//Incrementa a ordem dos visitados

	for(int e : grafo[v]){//Para cada vertice adjacente a V, executar recusivamente
		if(pre[e] == -1){
			dfs_rec(grafo, pre, pai, e);
			pai[e] = v;//Adiciona o pai de e que é v;
		}
	}
	return;
}

void dfs(vector<vector<int>> & grafo, vector<int> & pre, vector<int> & pai, int V){
	for(int i = 0; i<=V; i++){
		pre[i] = -1;//Preencher os vetores pre e pai com -1
		pai[i] = -1;
	}

	for(int i = 1; i <=V; i++){
		if(pre[i] == -1) dfs_rec(grafo, pre, pai, i);	
	}
}

int main(){

	int V,E;
	cin >> V >> E;

	//Tipos de grafos representados computacionalmente
	vector<vector<int>> grafo(V+1); //vetor de vetor de inteiros
	vector<vector <pair<int, int>>> grafo2(V+1); // vetor de vetor de pares de inteiros
	vector<tuple<int,int,int>> grafo3(E); // vetor de tuplas de inteiros

	//Vetores de pre e pai
	vector<int> pre(V+1);
	vector<int> pai(V+1);
	vector<int> pai2(V+1);


	for(int i = 0; i < E;i++){//Leitura do grafo
		int u,v;
		cin >> u >> v;
		grafo[u].push_back(v);
	}


	cout << "====================== LISTA DE ADJACENCIA ======================" << endl << endl;
	for(int i = 1; i <=V; i++){
	cout << "[" << i << "]: ";
		for(int e : grafo[i]){
			cout << e << " ";
		}
	cout << endl;
	}
	cout << endl;

	cout << "====================== DFS =====================" << endl;
	
	dfs(grafo, pre, pai, V);
	
	cout << endl;
	cout << "VETOR PRE DFS ==============" << endl;
	for(int i = 1; i <= V;i++){
		cout << "[" << i << "] : " << pre[i] << endl;
	}	

	cout << endl <<"VETOR PAI DFS ==============" << endl;
	for(int i = 1; i <= V; i++){
		cout << "[" << i << "]: " << pai[i] << endl;
	}
	cout << endl;

	cout << "====================== BFS ======================" << endl << endl;;
	bfs(grafo, pai2, V, 1);
	cout << "VETOR PAI BFS ===================" << endl;
	for(int i = 1; i <= V; i++){
		cout << "[" << i << "]: " << pai2[i] << endl;
	}
	cout << endl;


	return 0;
}


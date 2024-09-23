#include<bits/stdc++.h>
using namespace std;
#define V 8
#define pb push_back

unordered_map< int, vector<int> > adj, rev; // original graph and reverse graph

void DFS1(int i, vector<bool>& visited, stack<int>& mystack){ // receives a vertex, a visited array and a stack

	visited[i] = true; // define vertex as visited

	for(int j: adj[i]){ // for all adjacent vertices of i -> adj is a key (int) value (int vector) pair
		if( visited[j] == false ){  //recursive call to DFS1 if vertex is not visited
			DFS1(j, visited, mystack);

        }
    }

	mystack.push(i); // when all adjacent vertices are visited and there's no more way, push the vertex to the stack
}

void reverse()
{
	for(int i=0;i<V;++i)
	{
		for(int j: adj[i]) // creates the reverse graph by reversing the edges
			rev[j].pb(i);
	}
}

void DFS2(int i,vector<bool>& visited)
{
	cout<<i<<" ";
	visited[i] = true;
	for(int j: rev[i])
		if(!visited[j])
			DFS2(j,visited);
}

void findSCCs(){
	stack<int> mystack; // def a stack to store the vertices in order of their finish time

	vector<bool> visited(V,false); // to keep track of visited vertices

	for(int i=0 ; i<V ; ++i){
		if(!visited[i]){ // if vertex is not visited, then call DFS1
			DFS1(i,visited,mystack);
        }
    }

	reverse();

	for(int i=0;i<V;++i)
		visited[i] = false;

	cout<<"Strongly Connected Components are:\n";
	while(!mystack.empty()) // while stack is not empty, pop the top element and call DFS2
	{
		int curr = mystack.top();
		mystack.pop();
		if(visited[curr]==false)
		{
			DFS2(curr,visited);
			cout<<"\n";
		}
	}
}

int main()
{
	adj[0].pb(1);
	adj[1].pb(2);
	adj[2].pb(0);
	adj[2].pb(3);
	adj[3].pb(4);
	adj[4].pb(5);
	adj[4].pb(7);
	adj[5].pb(6);
	adj[6].pb(4);
	adj[6].pb(7);

	findSCCs();
	return 0;
}

#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Graph {
public:
	Graph();
	void addCity(string name);
	void addEdge(string city1, string city2, int distance,bool choice);
	void removeCity(string name);
	void removeEdge(string city1, string city2,int distance,bool choice);
	void updateCity(string oldName, string newName);
	void updateEdge(string city1, string city2, int oldDistance, int newDistance,bool choice);
	void display();
	void bfs(string start);
	void dfs(string start);
	void dijkstra(string start, string end);
	unordered_map<string, list<pair<string, int>>> adjList;
};


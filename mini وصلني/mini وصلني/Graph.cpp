#include "Graph.h"
Graph::Graph() {
	cout << "Welcome to our project Dr.Hanan" << endl;
}

void Graph::addCity(string name) {
	if (adjList.find(name) == adjList.end()) {
		adjList[name] = list<pair<string, int>>();
	}
}

void Graph::addEdge(string city1, string city2, int distance, bool choice) {
	if (adjList.find(city1) != adjList.end() && adjList.find(city2) != adjList.end()) {
		adjList[city1].push_back(make_pair(city2, distance));
		if (choice == true)
		{
			adjList[city2].push_back(make_pair(city1, distance));
		}
	}
}

void Graph::removeCity(string name) {
	if (adjList.find(name) != adjList.end()) {
		// remove all edges connected to the city
		for (auto& adj : adjList[name]) {
			for (auto itAdj = adjList[adj.first].begin(); itAdj != adjList[adj.first].end(); ++itAdj) {
				if (itAdj->first == name) {
					adjList[adj.first].erase(itAdj);
					break;
				}
			}
		}
		// remove the city itself
		adjList.erase(name);
	}
}

void Graph::removeEdge(string city1, string city2, int distance, bool choice) {
	if (adjList.find(city1) != adjList.end() && adjList.find(city2) != adjList.end()) {
		// remove the edge between the cities
		for (auto it = adjList[city1].begin(); it != adjList[city1].end(); ++it) {
			if (it->first == city2 && it->second == distance) {
				adjList[city1].erase(it);
				break;
			}
		}
		if (choice == true)
		{
			for (auto it = adjList[city2].begin(); it != adjList[city2].end(); ++it) {
				if (it->first == city1 && it->second == distance) {
					adjList[city2].erase(it);
					break;
				}
			}
		}
	}
}

void Graph::updateCity(string oldName, string newName) {
	if (adjList.find(oldName) != adjList.end()) {
		auto adjListOld = adjList[oldName];
		adjList.erase(oldName);
		adjList[newName] = adjListOld;
		// update all edges connected to the city
		for (auto& adj : adjList[newName]) {
			if (adj.first == oldName) {
				adj.first = newName;
			}
			for (auto& adjAdj : adjList[adj.first]) {
				if (adjAdj.first == oldName) {
					adjAdj.first = newName;
				}
			}
		}
	}
}

void Graph::updateEdge(string city1, string city2, int oldDistance, int newDistance, bool choice) {
	if (adjList.find(city1) != adjList.end() && adjList.find(city2) != adjList.end()) {
		// update the edge between the cities
		for (auto& adj : adjList[city1]) {
			if (adj.first == city2 && adj.second == oldDistance) {
				adj.second = newDistance;
				break;
			}
		}
		if (choice == true)
		{
			for (auto& adj : adjList[city2]) {
				if (adj.first == city1 && adj.second == oldDistance) {
					adj.second = newDistance;
					break;
				}
			}
		}
	}
}

void Graph::display() {
	for (auto& city : adjList) {
		cout << city.first << ": ";
		for (auto& adj : city.second) {
			cout << "(" << adj.first << ", " << adj.second << ") ";
		}
		cout << endl;
	}
}

void Graph::bfs(string start) {
	queue<string> q;
	map<string, bool> visited;
	q.push(start);
	visited[start] = true;
	while (!q.empty()) {
		auto curr = q.front();
		q.pop();
		cout << curr << " ";
		for (auto& adj : adjList[curr]) {
			if (!visited[adj.first]) {
				q.push(adj.first);
				visited[adj.first] = true;
			}
		}
	}
	cout << endl;
}

void Graph::dfs(string start) {
	stack<string> s;
	map<string, bool> visited;
	s.push(start);
	visited[start] = true;
	while (!s.empty()) {
		auto curr = s.top();
		s.pop();
		cout << curr << " ";
		for (auto& adj : adjList[curr]) {
			if (!visited[adj.first]) {
				s.push(adj.first);
				visited[adj.first] = true;
			}
		}
	}
	cout << endl;
}

void Graph::dijkstra(string start, string end) {
	priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;
	map<string, int> dist;
	map<string, string> prev;
	for (auto& city : adjList) {
		dist[city.first] = INT_MAX;
	}
	dist[start] = 0;
	pq.push(make_pair(0, start));
	while (!pq.empty()) {
		auto curr = pq.top();
		pq.pop();
		if (curr.second == end) {
			cout << "Path found from " << start << " to " << end << " with distance " << curr.first << endl;
			// print the path
			auto currCity = end;
			while (prev.find(currCity) != prev.end()) {
				cout << currCity << " <- ";
				currCity = prev[currCity];
			}
			cout << currCity << endl;
			return;
		}
		for (auto& adj : adjList[curr.second]) {
			auto newDist = dist[curr.second] + adj.second;
			if (newDist < dist[adj.first]) {
				dist[adj.first] = newDist;
				prev[adj.first] = curr.second;
				pq.push(make_pair(newDist, adj.first));
			}
		}
	}
	cout << "No path found from " << start << " to " << end << endl;
}
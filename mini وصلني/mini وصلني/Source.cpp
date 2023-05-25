#include <fstream>
#include <iostream>
#include <string>
#include "Graph.h"
int main() {
	Graph g;
	// load graph data from file
	ifstream inputFile("Graph.txt");
	if (inputFile.is_open()) {
		// read vertices
		int numVertices;
		inputFile >> numVertices;
		for (int i = 0; i < numVertices; i++) {
			string name;
			inputFile >> name;
			g.addCity(name);
		}

		// read edges
		int numEdges;
		inputFile >> numEdges;
		for (int i = 0; i < numEdges; i++) {
			string city1, city2;
			int distance;
			inputFile >> city1 >> city2 >> distance;
			g.addEdge(city1, city2, distance, false);
		}
	}
	inputFile.close();

	// main program loop
	while (true) {
		cout << "Choose an option:" << endl;
		cout << "1. Add city" << endl;
		cout << "2. Add edge" << endl;
		cout << "3. Remove city" << endl;
		cout << "4. Remove edge" << endl;
		cout << "5. Display graph" << endl;
		cout << "6. Update city" << endl;
		cout << "7. Update edge" << endl;
		cout << "8. Perform BFS" << endl;
		cout << "9. Perform DFS" << endl;
		cout << "10. Perform Dijkstra's algorithm" << endl;
		cout << "11. Save and exit" << endl;

		int choice;
			cin >> choice;
		switch (choice) {
		case 1: {
			string name;
			cout << "Enter city name: ";
			cin >> name;
			g.addCity(name);
			break;
		}
		case 2: {
			string city1, city2;
			int distance, i;
			bool choice = false;
			cout << "Enter city 1: ";
			cin >> city1;
			cout << "Enter city 2: ";
			cin >> city2;
			cout << "Enter distance: ";
			cin >> distance;
			cout << "If graph undirected please enter 1 : ";
			cin >> i;
			if (i == 1)
			{
				choice = true;
			}
			g.addEdge(city1, city2, distance,choice);
			break;
		}
		case 3: {
			string name;
			cout << "Enter city name: ";
			cin >> name;
			g.removeCity(name);
			break;
		}
		case 4: {
			string city1, city2;
			int distance, i;
			bool choice = false;
			cout << "Enter city 1: ";
			cin >> city1;
			cout << "Enter city 2: ";
			cin >> city2;
			cout << "Enter distance: ";
			cin >> distance;
			cout << "If graph undirected please enter 1 : ";
			cin >> i;
			if (i == 1)
			{
				choice = true;
			}
			g.removeEdge(city1, city2, distance,choice);
			break;
		}
		case 5: {
			g.display();
			break;
		}
		case 6: {
			string oldName, newName;
			cout << "Enter the name of the city you want to update: ";
			cin >> oldName;
			cout << "\n Enter the new name: ";
			cin >> newName;
			g.updateCity(oldName, newName);
			break;
		}
		case 7: {
			string city1,city2 ;
			int newDistance, oldDistance, i;
			bool choice = false;
			cout << "Enter city 1: ";
			cin >> city1;
			cout << "Enter city 2: ";
			cin >> city2;
			cout << "Enter distance that you want to change: ";
			cin >> oldDistance;
			cout << "Enter new distance: ";
			cin >> newDistance;
			cout << "If graph undirected please enter 1 : ";
			cin >> i;
			if (i == 1)
			{
				choice = true;
			}
			g.updateEdge(city1, city2, oldDistance, newDistance,choice);
			break;
		}
		case 8: {
			string start;
			cout << "Enter starting city: ";
			cin >> start;
			g.bfs(start);
			break;
		}
		case 9: {
			string start;
			cout << "Enter starting city: ";
			cin >> start;
			g.dfs(start);
			break;
		}
		case 10: {
			string start, end;
			cout << "Enter starting city: ";
			cin >> start;
			cout << "Enter ending city: ";
			cin >> end;
			g.dijkstra(start, end);
			break;
		}
		case 11: {
			// save graph data to file
			ofstream outputFile("Graph.txt");
			outputFile << g.adjList.size() << endl;
			int numEdges = 0;
			for (auto it = g.adjList.begin(); it != g.adjList.end(); it++) {
				outputFile << it->first << endl;
				numEdges += it->second.size();
			}
			outputFile << numEdges << endl;
			for (auto it = g.adjList.begin(); it != g.adjList.end(); it++) {
				string city1 = it->first;
				for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++) {
					string city2 = it2->first;
					int distance = it2->second;
					outputFile << city1 << " " << city2 << " " << distance << endl;
				}
			}
			outputFile.close();
			return 0;
		}
		default: {
			cout << "Invalid choice" << endl;
			break;
		}
		}
	}
}

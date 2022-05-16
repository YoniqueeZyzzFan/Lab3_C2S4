#include <iostream>
#include <string>
#include "Graph.h"

int main() {
	Graph<Vertex, Edge> g;
	g.addVertex(Vertex("Samara", 15));
	g.addVertex(Vertex("Moscow", 20));
	g.addVertex(Vertex("SaintP", 17));
	g.addVertex(Vertex("Novosibirsk", 5));
	g.addVertex(Vertex("Omsk", 11));
	g.addVertex(Vertex("Kazan", 9));
	//g.deleteVertex(Vertex("Samara", 15));
	g.addVertex(Vertex("Krasnoyarsk", 13));
	g.addVertex(Vertex("Kuraka", 3));
	g.addVertex(Vertex("Temp", 5));
	g.addEdge(Vertex("Samara", 15), Vertex("Moscow", 20), Edge("Moscow", 100, true, 1));
	g.addEdge(Vertex("Samara", 15), Vertex("Kazan", 9), Edge("Kazan", 33, true, 0));	
	g.addEdge(Vertex("Samara", 15), Vertex("Kuraka", 3),  Edge("Kuraka", 27, false, 1));
	g.addEdge(Vertex("Moscow", 20), Vertex("Novosibirsk", 5),  Edge("Novosibirsk", 16, false, 0));
	g.addEdge(Vertex("Moscow", 20), Vertex("Omsk", 11),  Edge("Omsk", 9, true, 1));
	g.addEdge(Vertex("SaintP", 17), Vertex("Samara", 15), Edge("Samara", 11, false, 0));
	g.addEdge(Vertex("SaintP", 17), Vertex("Kuraka", 3), Edge("Kuraka", 49, false, 1));
	g.addEdge(Vertex("SaintP", 17), Vertex("Omsk", 11), Edge("Omsk", 78, true, 0));
	g.addEdge(Vertex("Novosibirsk", 5), Vertex("Moscow", 20), Edge("Moscow", 5, true, 1));
	g.addEdge(Vertex("Novosibirsk", 5), Vertex("Kazan", 9), Edge("Kazan", 81, true, 0));
	g.addEdge(Vertex("Novosibirsk", 5), Vertex("Omsk", 11), Edge("Omsk", 1, true, 0));
	g.addEdge(Vertex("Omsk", 11), Vertex("Kazan", 9), Edge("Kazan", 21, false, 0));
	g.addEdge(Vertex("Omsk", 11), Vertex("Samara", 15), Edge("Samara", 37, false, 1));
	g.addEdge(Vertex("Kazan", 9), Vertex("Kuraka", 3), Edge("Kuraka", 21, true, 1));
	g.addEdge(Vertex("Kazan", 9), Vertex("Kazan", 9), Edge("SaintP", 20, false, 1));
	g.addEdge(Vertex("Krasnoyarsk", 13), Vertex("Samara", 15), Edge("Samara", 115, true, 1));
	g.addEdge(Vertex("Krasnoyarsk", 13), Vertex("Kazan", 9), Edge("Kazan", 63, false, 0));
	g.addEdge(Vertex("Krasnoyarsk", 13), Vertex("SaintP", 17), Edge("SaintP", 21, true, 1));
	g.addEdge(Vertex("Kuraka", 3), Vertex("Samara", 15), Edge("Samara", 125,true, 0));
	g.addEdge(Vertex("Temp", 5), Vertex("Krasnoyarsk", 13), Edge("Krasnoyarsk", 5, false, 0));
	//g.deleteEdge(Vertex("Temp", 5), Vertex("Krasnoyarsk", 13));
	g.print();
	//std::cout << g.dfs(Vertex("Temp", 5), Vertex("Krasnoyarsk", 13));
	std::vector<Vertex>path= g.dijkstra(Vertex("Temp", 5), Vertex("Kuraka", 3));
}
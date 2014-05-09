//Put any include statements here
#include <string>
#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <fstream>
#include <sstream>
#include <cstdlib>
//This class will be used to create a graph library.
enum Type {DIRECTED,UNDIRECTED};

class Graph{
	private:
		struct Edge{
			int vf;
			int vt;
			double weight;
			bool operator <(const Edge& rhs){
         		return weight<rhs.weight;
      		}
		};
		//Put your private data members here
		Type type;
		std::vector<std::list<Edge>> edgeList;
		std::vector<bool> visited;
		int vertices;
		int edges;
		//Put your private methods here
		void resetVisit();
	public:
		//Construct an empty graph of the specified type
		Graph(Type t);
		//Delete a graph
		~Graph();
		//Read a graph from a file
		void readFromFile(std::string file);
		//Write a graph to a file
		void writeToFile(std::string file);
		//Empty
		bool empty();
		//Add edge
		void addEdge(int v1, int v2, double weight);
		//Add vertex
		void addVertex();
		//Count connected components
		int numConnectedComponents();
		//Tree check
		bool tree();
		//Depth First Traverse - proceed from source
		void DFT(int source,std::string file);
		//Breadth First Traverse - proceed from source
		void BFT(int source,std::string file);
		//Closeness - determine minimum number of edges to get
		// from one node to the other
		int closeness(int v1, int v2);
		//* Partition - determine if you can partition the graph
		bool partitionable();			
		//* MST - print the minimum spanning tree of the graph
		//to a file with the passed name
		bool MST(std::string file);
		//* Step Away - print the nodes who are a degree of
		//closeness from the source to a file with the passed name
		void stepAway(int source, int closeness, std::string file);
};

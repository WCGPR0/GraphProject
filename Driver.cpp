#include "Graph.h" 
#include <iostream>
#include <cstdlib>

using namespace std;

int main(int argc, char *argv[]) {
	//cout << "------Driver code----" << endl;
	if (argc <= 1) 
		cout << "You have not specified a file";
	else {
		//srand(); //Randomize seed

		cout << "Please input a file" << endl;
		Graph myGraph(UNDIRECTED); //Undirected by default, overide by readFile
		
		myGraph.readFromFile(argv[1]); //Error handling inside function

		cout << "Calling empty():" << myGraph.empty() << endl;

		cout << "Calling numConnectedComponents():" << myGraph.numConnectedComponents() << endl;

		cout << "Calling tree():" << myGraph.tree() << endl;

		myGraph.DFT(2,"DFTtest--2");

		myGraph.BFT(7,"BFTtest--7");

		cout << "closeness of 1 and 3: " << myGraph.closeness(1,3)<<endl;
		cout << "closeness of 7 and 6: " << myGraph.closeness(7,6)<<endl;
		cout << "closeness of 4 and 6: " << myGraph.closeness(4,6)<<endl;

		//cout << "Calling partitionable()" << myGraph.partitionable() << endl;

		//cout << "Calling MST()" << myGraph.MST("MSTtest");

		cout << "Calling stepAway" << endl; 

		myGraph.stepAway(4,-1,"stepAwaytest"); 
	}
	return 0;
}

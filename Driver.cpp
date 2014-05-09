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

		myGraph.DFT(1,"DFTtest-g1-1");

		myGraph.BFT(2,"BFTtest-g1-2");

		cout << "closeness of 1 and 2: " << myGraph.closeness(1,3)<<endl;
		cout << "closeness of 4 and 5: " << myGraph.closeness(4,5)<<endl;
		cout << "closeness of 2 and 6: " << myGraph.closeness(2,6)<<endl;

		//cout << "Calling partitionable()" << myGraph.partitionable() << endl;

		cout << "Calling MST()" << myGraph.MST("g1-MST-Test")<<endl;

		cout << "Calling stepAway" << endl; 

		myGraph.stepAway(2,-1,"stepAwaytest-2--1"); 
		myGraph.stepAway(1,2,"stepAwaytest-1-2"); 
		myGraph.stepAway(2,1,"stepAwaytest-2-1"); 
		
		myGraph.writeToFile("Output-test");
	}
	return 0;
}

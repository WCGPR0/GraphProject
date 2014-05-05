#include "Graph.h"
#include <iostream>
using namespace std;


Graph::Graph(Type t){
	type = t;
	vertices = 0;
	edges = 0;
}

Graph::~Graph(){
}

void Graph::readFromFile(string file){
	ifstream inFile;
	inFile.open(file);
	if(!(inFIle.is_open())){
		cout<<"fail to open the inputFile!"<<endl;
		exit(0);
	}
	string buff;
	getline(inFile,buff);
	if(buff.compare("directed")){
		type = DIRECTED;
	}
	else if(buff.compare("undirected")){
		type = UNDIRECTED;
	}
	else{
		cout<<"invalide graph type!"<<endl;
		exit(0);
	}
	getline(inFile,buff);
	vertices = atoi(buff.c_str());
	for(int i=0;i<n;i++){
		addVertex();
	}
	getline(inFile,buff);
	edges = atoi(buff.c_str());
	stringstream ss;
	int v1;
	int v2;
	double _weight;
	if(type==DIRECTED){
		while(getline(inFile,buff)){
			ss<<buff;
			ss>>v1>>v2>>_weight;
			addEdge(v1,v2,_weight);
		}
	}
	else{
		while(getline(inFile,buff)){
			ss<<buff;
			ss>>v1>>v2>>_weight;
			addEdge(v1,v2,_weight);
			addEdge(v2,v1,_weight);
		}
	}
}

bool Graph::empty(){
	return vertices==0;
}

void Graph::addVertex(){
	list<Edge> newList;
	edgeList.push_back(newList);
	visited.push_back(false);
}

void Graph::addEdge(int v1,int v2,double weight){
	if(v1>vertices||v2>vertices){
		cout<<"invalid edges!"<<endl;
		exit(0);
	}
	else{
		Edge newEdge;
		newEdge.vt = v2;
		newEdge.weight = _weight;
		edgeList[v1-1].push_back(newEdge);
	}
}

int Graph::numConnectedComponents(){
	int retVal = 0;
	if(!empty()){
		for(int t=0;t<vertices;t++){
			if(!visited[t]){
				retVal++;	
				visited[t].flip();
				process.push_back(t);
				int current;
				size_t stackSize;
				list<Edge>::literator i;
				while(!process.empty()){
					current = process.top();
					i = edgeList[current].begin();
					stackSize = process.size();
					while(i!=edgeList[current].end()){
						if(!visited[i->vt]){
							process.push_back(i->vt);
							visited[i->vt].flip();
							break;
						}
						i++;
					}
					if(stackSize==process.size()){
						process.pop();
					}
				}
				process.clear();
			}
		}
	}
	return retVal;
}

void Graph::DFT(int source,string file){
	ofstream outFile;
	outFile.open(file);
	if(!outFile.is_open()){
		cout<<"invalid DFT file"<<endl;
		exit(0);
	}
	stack<int> process;
	if(!empty()){
		for(int t=0;t<vertices;t++){
			if(!visited[t]){	
				visited[t].flip();
				process.push_back(t);
				outFile<<t+1<<endl;
				int current;
				size_t stackSize;
				list<Edge>::literator i;
				while(!process.empty()){
					current = process.top();
					i = edgeList[current].begin();
					stackSize = process.size();
					while(i!=edgeList[current].end()){
						if(!visited[i->vt]){
							process.push_back(i->vt);
							visited[i->vt].flip();
							outFile<<i->vt+1<<endl;
							break;
						}
						i++;
					}
					if(stackSize==process.size()){
						process.pop();
					}
				}
				process.clear();
			}
		}
	}
}

void Graph::BFT(int source,string file){
	ofstream outFile;
	outFile.open(file);
	if(!outFile.is_open()){
		cout<<"invalid BFT file"<<endl;
		exit(0);
	}
	queue<int> process;
	int current;
	list<Edge>::literator i;
	if(!empty()){
		for(int t=0;t<vertices;t++){
			if(!visited[t]){
				visited[t].flip();
				process.push(t);
				outFile<<t+1<<endl;
				while(!process.empty()){
					current = process.back();
					i=edgeList[current].begin();
					while(i!=edgeList[current].end()){
						if(!visited[i->vt]){
							visited[i->vt].flip();
							process.push(i->vt);
							outFile<<i->vt+1<<endl;
						}
						i++;
					}
					process.pop();
				}
				process.clear();
			}
		}	
	}
}



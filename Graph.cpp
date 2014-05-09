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
	if(!(inFile.is_open())){
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
	for(int i=0;i<vertices;i++){
		addVertex();
	}
	getline(inFile,buff);
	edges = atoi(buff.c_str());
	stringstream ss;
	int v1;
	int v2;
	double _weight;
	while(getline(inFile,buff)){
		ss<<buff;
		ss>>v1>>v2>>_weight;
		addEdge(v1,v2,_weight);
		ss.clear();//clear any bits set
		ss.str(std::string());
	}
	inFile.close();
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
	if(v1>vertices&&v2>vertices){
		cout<<"invalid edges!"<<endl;
		exit(0);
	}
	else{
		if(type==1){
			Edge newEdge;
			newEdge.vf = v1-1;
			newEdge.vt = v2-1;
			newEdge.weight = weight;
			edgeList[v1-1].push_back(newEdge);
		}
		else{
			Edge newEdge1;
			newEdge1.vf = v1-1;
			newEdge1.vt = v2-1;
			newEdge1.weight = weight;
			edgeList[v1-1].push_back(newEdge1);
			Edge newEdge2;
			newEdge2.vf = v2-1;
			newEdge2.vt = v1-1;
			newEdge2.weight = weight;
			edgeList[v2-1].push_back(newEdge2);
		}
	}
}

int Graph::numConnectedComponents(){
	int retVal = 0;
	if(!empty()){
		for(int t=0;t<vertices;t++){
			if(!visited[t]){
				stack<int> process;
				retVal++;	
				visited[t].flip();
				process.push(t);
				int current;
				size_t stackSize;
				list<Edge>::iterator i;
				while(!process.empty()){
					current = process.top();
					i = edgeList[current].begin();
					stackSize = process.size();
					while(i!=edgeList[current].end()){
						if(!visited[i->vt]){
							process.push(i->vt);
							visited[i->vt].flip();
							break;
						}
						i++;
					}
					if(stackSize==process.size()){
						process.pop();
					}
				}
			}
		}
	}
	resetVisit();
	return retVal;
}

bool Graph::tree(){
	stack<int> process;
	if(!empty()){
		visited[0].flip();
		process.push(0);
		int current;
		size_t stacksize;
		int count=1;
		list<Edge>::iterator i;
		while(!process.empty()){
			current = process.top();
			i=edgeList[current].begin();
			stacksize=process.size();
			while(i!=edgeList[current].end()){
				if(visited[i->vt]){
					resetVisit();
					return false;
				}
				else{
					process.push(i->vt);
					visited[i->vt].flip();
					break;
				}
				i++;
			}
			if(stacksize==process.size()){
				count++;
				process.pop();
			}
		}
		if(count==vertices){
			resetVisit();
			return true;
		}
		else{
			resetVisit();
			return false;
		}
	}
	else
		return true;
}


void Graph::DFT(int source,string file){
	ofstream outFile;
	outFile.open(file);
	if(!outFile.is_open()){
		cout<<"invalid DFT file"<<endl;
		exit(0);
	}
	stack<int> process;
	if(!empty()&&source<=vertices){
				visited[source-1].flip();
				process.push(source-1);
				int current;
				size_t stackSize;
				list<Edge>::iterator i;
				while(!process.empty()){
					current = process.top();
					i = edgeList[current].begin();
					stackSize = process.size();
					while(i!=edgeList[current].end()){
						if(!visited[i->vt]){
							process.push(i->vt);
							visited[i->vt].flip();
							break;
						}
						i++;
					}
					if(stackSize==process.size()){
						outFile<<current+1<<endl;
						process.pop();
					}
				}
	}
	else{
		cout<<"can not find the vertices in DFT"<<endl;
	}
	outFile.close();
	resetVisit();
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
	list<Edge>::iterator i;
	if(!empty()&&source<=vertices){
				visited[source-1].flip();
				process.push(source-1);
				outFile<<source<<endl;
				while(!process.empty()){
					current = process.front();
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
	}
	else{
		cout<<"can not find the vertices in BFT"<<endl;
	}
	outFile.close();
	resetVisit();
}

/*
bool Graph::MST(string file){
	ofstream outFile;
	outFile.open(file);
	if(!outFile.is_open()){
		cout<<"invalid MST file"<<endl;
		return false;
	}
	priority_queue<Edge> process;
	vector<int> MSTnodes;
	vector<Edge> MSTedges;
	int components=1;
	int next;
	list<Edge>::iterator i;
	if(!empty()){
		for(int t=0;t<vertices;t++){
			if(!visited[t]){
				visited[t].flip();
				for(i=edgeList[t].begin();i!=edgeList[t].end();i++){
					if(!visited[i->vt]){
						process.push(*i);
					}
				}
				while(!process.empty()){
					next = process.top().vt;
					MSTedges.push_back(process.top());
					MSTnodes.push_back(next);
					process.pop();
					visited[next].flip();
					i=edgeList[next].begin();
					while(i!=edgeList[next].end()){
						if(!visited[i->vt]){
							process.push(*i);
						}
					}
				}
				outFile<<"component "<<components<<": { {";
				for(size_t j=0;j<MSTnodes.size();i++){
					if(j!=MSTnodes.size()-1)
						outFile<<MSTnodes[j]<<", ";
					else{
						outFile<<MSTnodes[j];
					}
				}
				outFile<<" } { ";
				for(size_t p=0;p<MSTedges.size();p++){
					if(p!=MSTnodes.size()-1)
						outFile<<"("<<MSTedges[p].vf<<","<<MSTedges[p].vt<<","<<MSTedges[p].weight<<"), ";
					else
						outFile<<"("<<MSTedges[p].vf<<","<<MSTedges[p].vt<<","<<MSTedges[p].weight<<")";
				}
				outFile<<" } }"<<endl;
			}
		}
	}
	outFile.close();
	resetVisit();
	return true;
}

*/

int Graph::closeness(int v1, int v2){
		int count=1;
		queue<int> process;
		int current;
		int first;
		visited[v1-1].flip();
		process.push(v1-1);
		while(!process.empty()){
			current = process.front();
		list<Edge>::iterator i=edgeList[current].begin();
			first=0;	
			while(i!=edgeList[current].end()){
				if(i->vt==v2-1){
					resetVisit();
					if(first==0){
						return count;
					}
					else{
						return count-1;
					}
				}
				if(!visited[i->vt]){
					visited[i->vt].flip();
					process.push(i->vt);
					if(first==0){
						count++;
						first++;
					}
				}
				++i;
			}	
			process.pop();
		}
		resetVisit();
		return -1;
}


void Graph::stepAway(int source, int closeness,string file){
	ofstream outFile;
	outFile.open(file);
	if(!outFile.is_open()){
		cout<<"invalid stepAway file"<<endl;
		exit(0);
	}
	if(!empty()){
			if(source>vertices){
				cout<<"can not find the source vertices"<<endl;
			}
			int count=1;
			queue<int> process;
			int current;
			int first;
			list<Edge>::iterator i;
			visited[source-1].flip();
			process.push(source-1);
			while(!process.empty()){
				current=process.front();
				i=edgeList[current].begin();
				first=0;
				while(i!=edgeList[current].end()){
					if(closeness==(count-first)&&!visited[i->vt]){
						outFile<<i->vt+1<<endl;
					}
					else if(!visited[i->vt]){
						visited[i->vt].flip();
						process.push(i->vt);
						if(first==0){
							count++;
							first++;
						}
					}
					i++;
				}
				process.pop();
			}
	}
	if(closeness==-1){
		for(int j=0;j<vertices;j++){
			if(!visited[j]){
				outFile<<j+1<<endl;
			}
		}
	}
	outFile.close();
}

void Graph::resetVisit(){
	for(int i=0;i<vertices;i++){
		visited[i]=false;
	}
}


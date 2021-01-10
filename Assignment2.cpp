/*Name: Yen Pham
CS3110
Assignment 2
*/

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <list>

using namespace std;

int get_vertice_index(int vertice)
{
	int index;
	ifstream fin;
	fin.open("data2.txt"); //open file
	if(fin.fail())
	{
		cout << "Cannot open the file data2.txt" << endl;
		exit(EXIT_FAILURE);
	}

	string line;
	int temp_vertice;

	int count = 0;
	while (getline(fin, line) && line.length() != 0)
	{
		stringstream is(line);
		is >> temp_vertice;
		if (temp_vertice == vertice)
		{
			index = count; //get index
		}
		count++;
	}
	fin.close();
	return index;
}

class Graph
{
	private:
	int vertice_count; //number of vertice
	list <int> *adj_vertice_list;

	public:
	Graph(int count);//constructor
	//function to add an edge to graph-from vertice to the adj_vertice 
	void add_edge(int vertice, int adj_vertice);
	
	//print BFS traversal from a given source
	void BFS(int source);
};

Graph::Graph(int count)
{
	vertice_count = count;
	adj_vertice_list = new list<int>[count];
}

void Graph::add_edge(int vertice, int adj_vertice)
{
	adj_vertice_list[get_vertice_index(vertice)].push_back(adj_vertice);
}

void Graph::BFS(int source)
{
	ofstream fout;
	fout.open("out2.txt");

	bool *visited = new bool[vertice_count];
	// Mark all the vertices as not visited 
	for (int g = 0; g < vertice_count; g++)
	{
		visited[g] = false;
	}

	// Create a queue for BFS
	list<int> queue;

	// Mark the current node as visited and enqueue it 
	visited[get_vertice_index(source)] = true;
	queue.push_back(source);

	// 'i' will be used to get all adjacent 
	// vertices of a vertex
	list<int>::iterator i; 

	while(!queue.empty())
	{
		// Dequeue a vertex from queue
		source = queue.front(); 
		//cout << source << " ";
		queue.pop_front();

		// Get all adjacent vertices of the dequeued 
		// vertex s. If a adjacent has not been visited,  
		// then mark it visited and enqueue it

		for (i = adj_vertice_list[get_vertice_index(source)].begin(); i!= adj_vertice_list[get_vertice_index(source)].end(); i++)
		{
			//cout << *i << endl;
			if (!visited[get_vertice_index(*i)])
			{
				visited[get_vertice_index(*i)] = true;
				queue.push_back(*i);
			}
		}
	}

	bool connected = true;
	//Check if all the vertices in the graph have been visited
	for (int g = 0; g < vertice_count; g++)
	{
		if (!visited[g])
		{
			connected = false;
		}
	}

	//If not all the vertices in the graph been visited, print not connected to the file out2.txt
	if (!connected)
	{
		fout << "Graph is not connected" << endl;
	}
	else
	{
		fout << "Graph is connected" << endl;
	}
	fout.close();
}

int get_vertice_count() //get number of vertices in the graph
{
	ifstream fin;
	fin.open("data2.txt");
	if(fin.fail())
	{
		cout << "Cannot open the file data2.txt" << endl;
		exit(EXIT_FAILURE);
	}

	string line;
	
	int line_count = 0;
	while(getline(fin, line) && line.length() != 0)
	{
		line_count++;
	}
	fin.close();
	return line_count;
}

int main()
{
	ifstream fin;
	fin.open("data2.txt"); //open file
	if(fin.fail())
	{
		cout << "Cannot open the file data2.txt" << endl;
		exit(EXIT_FAILURE);
	}

	string line;
	int vertice;
	int adj_vertice;
	int vertice_count = get_vertice_count();
	Graph graph(vertice_count);

	//Read the adjency list
	while(getline(fin, line) && line.length() != 0)
	{
		stringstream is(line);
		is >> vertice;
		while(is >> adj_vertice)
		{
			graph.add_edge(vertice, adj_vertice);	
		}
	}
	graph.BFS(2); //BFS starting from vertex 2
	fin.close();
	
	return 0;
}
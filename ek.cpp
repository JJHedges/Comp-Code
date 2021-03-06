#include <vector>
#include <queue>
#include <limits.h>
#include <iostream>
#include <set>
#include <algorithm>

//Adjacency matrix to hold provided graph and edge capacities
//capMatrix[i][j] = x implies the capacity of edge from i to j is x
std::vector<std::vector<int> > capMatrix(7, std::vector<int> (7, -1));
//Adjacency matrix to hold current flow from i to j
std::vector<std::vector<int> > flowMatrix(7, std::vector<int> (7, -1));
//Residual matrix defined as capacity - flow for a edge (u,v) and flow for the reverse edge (v,u)
std::vector<std::vector<int> > residualMatrix(7, std::vector<int> (7, -1));

//BFS from start to end (source to sink) and return the flow of the augmenting path
//if one can be found
int bfs(int start, int end)
{
	std::vector<int> parentsList(7, -1);
	int curPathCapacity = INT_MAX;
	std::queue<int> q;
	
	q.push(0);
	
	int currentNode;
	std::set<int> seen;
	while(!q.empty())
	{
		currentNode = q.front(); q.pop();
		seen.insert(currentNode);
		
		if(currentNode == end) break;	
		
		for(int i = 0; i < 7; i++)
		{		
			//If node has not been seen before and a path with non-zero remaining capacity
			// exists push the node on and remember its parent	
			if(seen.count(i) == 0 && capMatrix[currentNode][i] != -1 
				&& residualMatrix[currentNode][i] != 0)
			{
				q.push(i);
				parentsList[i] = currentNode;
			}
		}
	}
	
	if(currentNode != end) return 0;
	//Find the minimum amount of flow that can be pushed by retracing the path found
	while(currentNode != start)
	{
		int parent = parentsList[currentNode];
		curPathCapacity = std::min(residualMatrix[parent][currentNode], curPathCapacity);
		currentNode = parent;
	}
	currentNode = end;
	//Push the flow by updating the flow matrix and the residual matrix and return the amount pushed
	while(currentNode != start)
	{
		int parent = parentsList[currentNode];
		flowMatrix[parent][currentNode] += curPathCapacity;
        residualMatrix[parent][currentNode] = capMatrix[parent][currentNode] - flowMatrix[parent][currentNode];
        residualMatrix[currentNode][parent] = flowMatrix[parent][currentNode];
		currentNode = parent;
	}
	return curPathCapacity;	
}

//Given source and sink call bfs repeatedly until no more flow can be pushed
int edmondsKarp(int source, int sink)
{
	int maxFlow = 0;
	while(true)
	{
		int flow = bfs(source, sink);
		if(flow == 0)
		{
			break;
		}
		maxFlow += flow;
	}
	return maxFlow;
}

//Test using example graph, flow should be 5
void test1()
{
	capMatrix[0][1] = 3;
	capMatrix[0][3] = 3;
	capMatrix[1][2] = 4;
	capMatrix[2][0] = 3;
	capMatrix[2][3] = 1;
	capMatrix[2][4] = 2;
	capMatrix[3][4] = 2;
	capMatrix[3][5] = 6;
	capMatrix[4][1] = 1;
	capMatrix[4][6] = 1;
	capMatrix[5][6] = 9;
	
	capMatrix[1][0] = 3;
	capMatrix[3][0] = 3;
	capMatrix[2][1] = 4;
	capMatrix[0][2] = 3;
	capMatrix[3][2] = 1;
	capMatrix[4][2] = 2;
	capMatrix[4][3] = 2;
	capMatrix[5][3] = 6;
	capMatrix[1][4] = 1;
	capMatrix[6][4] = 1;
	capMatrix[6][5] = 9;
		
	flowMatrix[0][1] = 0;
	flowMatrix[0][3] = 0;
	flowMatrix[1][2] = 0;
	flowMatrix[2][0] = 0;
	flowMatrix[2][3] = 0;
	flowMatrix[2][4] = 0;
	flowMatrix[3][4] = 0;
	flowMatrix[3][5] = 0;
	flowMatrix[4][1] = 0;
	flowMatrix[4][6] = 0;
	flowMatrix[5][6] = 0;
	
	flowMatrix[1][0] = 0;
	flowMatrix[3][0] = 0;
	flowMatrix[2][1] = 0;
	flowMatrix[0][2] = 0;
	flowMatrix[3][2] = 0;
	flowMatrix[4][2] = 0;
	flowMatrix[4][3] = 0;
	flowMatrix[5][3] = 0;
	flowMatrix[1][4] = 0;
	flowMatrix[6][4] = 0;
	flowMatrix[6][5] = 0;
	
    residualMatrix[0][1] = capMatrix[0][1] - flowMatrix[0][1];
	residualMatrix[0][3] = capMatrix[0][3] - flowMatrix[0][3];
	residualMatrix[1][2] = capMatrix[1][2] - flowMatrix[1][2];
	residualMatrix[2][0] = capMatrix[2][0] - flowMatrix[2][0];
	residualMatrix[2][3] = capMatrix[2][3] - flowMatrix[2][3];
	residualMatrix[2][4] = capMatrix[2][4] - flowMatrix[2][4];
	residualMatrix[3][4] = capMatrix[3][4] - flowMatrix[3][4];
	residualMatrix[3][5] = capMatrix[3][5] - flowMatrix[3][5];
	residualMatrix[4][1] = capMatrix[4][1] - flowMatrix[4][1];
	residualMatrix[4][6] = capMatrix[4][6] - flowMatrix[4][6];
	residualMatrix[5][6] = capMatrix[5][6] - flowMatrix[5][6];
	
	residualMatrix[1][0] = flowMatrix[0][1];
	residualMatrix[3][0] = flowMatrix[0][3];
	residualMatrix[2][1] = flowMatrix[1][2];
	residualMatrix[0][2] = flowMatrix[2][0];
	residualMatrix[3][2] = flowMatrix[2][3];
	residualMatrix[4][2] = flowMatrix[2][4];
	residualMatrix[4][3] = flowMatrix[3][4];
	residualMatrix[5][3] = flowMatrix[3][5];
	residualMatrix[1][4] = flowMatrix[4][1];
	residualMatrix[6][4] = flowMatrix[4][6];
	residualMatrix[6][5] = flowMatrix[5][6];
    
	int maxFlow = edmondsKarp(0, 6);
    if(maxFlow == 5)
        std::cout << "Found max flow of " << maxFlow << " correctly" << std::endl;
}

int main(int argc, char **argv)
{
	test1();	
}

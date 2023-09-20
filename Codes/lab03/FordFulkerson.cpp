#include <bits/stdc++.h>

using namespace std;

class FordFulkerson {
  int nodesCount;
  vector<int> parentNode;
  vector<vector<int> > recidualGraph;
  int sourceNode, sinkNode, maxFlow, currentPathFlow;

 public:
  void initialize(vector<vector<int> > graph, int source, int sink, int count) {
    recidualGraph = graph;
    nodesCount = count;
    vector<int> rough(nodesCount, 0);
    parentNode = rough;
    sourceNode = source;
    sinkNode = sink;
    maxFlow = 0;
    // cout<< nodesCount;
    // for(int i=0;i<nodesCount;i++)for(int
    // j=0;j<nodesCount;j++)cout<<recidualGraph[i][j]<<" "<<rough[i]<<"a";
  }

  void countMaxFlow() {
    maxFlow = 0;
    while (bfs()) {
      currentPathFlow = INT_MAX;
      int prevNode;
      for (int currentNode = sinkNode; currentNode != sourceNode;
           currentNode = parentNode[currentNode]) {
        prevNode = parentNode[currentNode];
        currentPathFlow =
            min(currentPathFlow, recidualGraph[prevNode][currentNode]);
      }
      for (int currentNode = sinkNode; currentNode != sourceNode;
           currentNode = parentNode[currentNode]) {
        prevNode = parentNode[currentNode];
        recidualGraph[prevNode][currentNode] -= currentPathFlow;
        recidualGraph[currentNode][prevNode] += currentPathFlow;
      }
      maxFlow += currentPathFlow;
    }
  }

  bool bfs() {
    vector<bool> isVisited(nodesCount, false);
    queue<int> bfsQueue;
    bfsQueue.push(sourceNode);
    isVisited[sourceNode] = true;
    parentNode[sourceNode] = -1;
    int currentNode;
    while (!bfsQueue.empty()) {
      currentNode = bfsQueue.front();
      bfsQueue.pop();

      for (int i = 0; i < nodesCount; i++) {
        if (!isVisited[i] && recidualGraph[currentNode][i] > 0) {
          if (i == sinkNode) {
            parentNode[i] = currentNode;
            return true;
          }
          bfsQueue.push(i);
          isVisited[i] = true;
          parentNode[i] = currentNode;
        }
      }
    }
    return false;
  }

  void printMaxFlow() {
    cout << "The Maximum Flow for given graph is: " << maxFlow << endl;
  }
};

int main() {
  // cout<<"debug";
  vector<vector<int> > graph = {{0, 16, 13, 0, 0, 0}, {0, 0, 10, 12, 0, 0},
                                {0, 4, 0, 0, 14, 0},  {0, 0, 9, 0, 0, 20},
                                {0, 0, 0, 7, 0, 4},   {0, 0, 0, 0, 0, 0}};

  FordFulkerson fordFulkerson;
  fordFulkerson.initialize(graph, 0, 5, 6);
  fordFulkerson.countMaxFlow();
  fordFulkerson.printMaxFlow();
  return 0;
}

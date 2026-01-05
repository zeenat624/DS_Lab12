#include <iostream>
using namespace std;

class Dijkstra {
private:
    int vertices;
    int Adj[6][6];
    int dist[6];         
    int prev[6];        
    bool visited[6]; 
    char names[26];  

public:
    Dijkstra(int v, int inputAdj[6][6]) {
        vertices = v;

        for (int i = 0; i < vertices; i++) {
            names[i] = 'A' + i;
            dist[i] = 1e9;      
            prev[i] = -1;
            visited[i] = false;
        }
        for(int i = 0; i < vertices; i++) {
            for(int j = 0; j < vertices; j++) {
                Adj[i][j] = inputAdj[i][j];
            }
        }
    }

    void compute(int source) {
        dist[source] = 0;

        for (int i = 0; i < vertices; i++) {
            int u = selectMinVertex();
            if (u == -1){
            	break;
			} 

            visited[u] = true;

            for (int v = 0; v < vertices; v++) {
                if (Adj[u][v] != 0 && visited[v] == false) {
                    int newDist = dist[u] + Adj[u][v];
                    if (newDist < dist[v]) {
                        dist[v] = newDist;
                        prev[v] = u;
                    }
                }
            }
        }
    }

    int selectMinVertex() {
        int minVertex = -1;
        for (int i = 0; i < vertices; i++) {
           if (visited[i] == false && minVertex == -1) {
           minVertex = i;
           } 
		   else if (visited[i] == false && dist[i] < dist[minVertex]) {
            minVertex = i;
           }
        }
        return minVertex;
    }

    void printTable() {
        cout << "Node  Distance  Previous "<<endl;
        for (int i = 0; i < vertices; i++) {
            cout << names[i] << "     ";
            if (dist[i] >= 1e9){
            	cout << "infity";
			} 			 
			else {
				cout << dist[i];
			}
            cout << "       ";
            if (prev[i] == -1){
            	cout << "-";
			} 
			else{
            int nodeIndex = prev[i];      
            char node = names[nodeIndex];  
            cout << node;
			}
            cout << endl;
        }
    }

   void printPathRecursive(int src, int dest) {
    if (dest == -1){
    	return;
	}  

    if (dest != src) {
        printPathRecursive(src, prev[dest]);
        cout << " -> ";
    }

    cout << names[dest];
  }

  void printPath(int src, int dest) {
    if (dist[dest] >= 1e9) {
        cout << "No path exists" << endl;
        return;
    }

    cout << "Shortest path from " << names[src]<< " to " << names[dest] << ": ";

    printPathRecursive(src, dest); 

    cout << "  Cost: " << dist[dest] << endl;
}

};

int main() {
    int adj[6][6] = {
        {0, 2, 0, 0, 0, 0},
        {2, 0, 0, 5, 6, 0},
        {0, 0, 0, 0, 0, 3},
        {0, 5, 0, 0, 0, 1},
        {0, 6, 0, 0, 0, 0},
        {0, 0, 3, 1, 0, 0}
    };

    Dijkstra d(6, adj);
    d.compute(0);  
    d.printTable();
    d.printPath(0, 2);  

    return 0;
}


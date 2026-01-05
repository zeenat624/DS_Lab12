#include <iostream>
using namespace std;

class FloydWarshall {
private:
    int vertices;
    int dist[4][4];
    int pred[4][4];
    char names[26];
public:
    
    FloydWarshall(int v, int inputAdj[4][4]) {
        vertices = v;
        
        for (int i = 0; i < vertices; i++) {
            names[i] = 'A' + i;
        }
        for(int i = 0; i < vertices; i++) {
            for(int j = 0; j < vertices; j++) {
                dist[i][j] = inputAdj[i][j];
            
            if(i != j && dist[i][j] != 0){
            	pred[i][j] = i;
			}
			else{
				pred[i][j] = -1;	
			}
            }
        }
    }

    void shortestPath() {
        for(int k = 0; k < vertices; k++) {
            for(int i = 0; i < vertices; i++) {
                for(int j = 0; j < vertices; j++) {
                    if(dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                        pred[i][j] = pred[k][j];
                    }
                }
            }
        }
    }

    void printPath(int src, int dest) {
    if(src == dest) {
        cout << "Path: " << names[src] << endl;
        cout << "Distance: " << dist[src][dest] << endl;
        return;
    }

    int path[4];
    int index = 0;
    int current = dest;
    while(current != src) {
        path[index++] = current;
        current = pred[src][current];
    }
    path[index++] = src;

    cout << "Shortest path from " << names[src] << " to " << names[dest] << ": ";
    for(int i = index-1; i >= 0; i--) {
    int nodeIndex = path[i];      
    char node = names[nodeIndex];  
    cout << node;

        if(i != 0){
        cout << " -> ";	
		}
    }
    cout << " Distance: " << dist[src][dest] << endl;
  }

    
};

int main() {
    int inputAdj[4][4] = {
        {0, 2, 4, 6},
        {3, 0, 2, 6},
        {2, 4, 0, 4},
        {-2, 0, 2, 0}
    };
    
    FloydWarshall fw(4, inputAdj);
    fw.shortestPath();

    fw.printPath(2, 1); 
    fw.printPath(0, 3); 
    fw.printPath(1, 2); 

    return 0;
}


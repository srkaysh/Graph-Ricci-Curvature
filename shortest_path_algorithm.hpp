#ifndef __SHORTEST_PATH__
#define __SHORTEST_PATH__

#include<bits/stdc++.h>
using namespace std;

class Graph{
    private:
        int vertices;
        int **matrix=NULL;

    public:
        Graph(int **adjMat) {
            matrix = adjMat;
            vertices = sizeof(*matrix) / sizeof(**matrix);
        }

        /*
        void addEdge(int source, int destination, int weight) {
            //add edge
            matrix[source][destination] = weight;

            //add back edge for undirected graph
            matrix[destination][source] = weight;
        }
        */

        //get the vertex with minimum distance which is not included in SPT
        int getMinimumVertex(bool mst[], int key[]){
            int minKey = INT_MAX;
            int vertex = -1;
            for (int i = 0; i <vertices ; i++) {
                if(mst[i]==false && minKey>key[i]){
                    minKey = key[i];
                    vertex = i;
                }
            }
            return vertex;
        }

        void dijkstra_GetMinDistances(int sourceVertex){
            bool spt[vertices]={false};
            int distance[vertices];

            //Initialize all the distance to infinity
            for (int i = 0; i <vertices ; i++) {
                distance[i] = INT_MAX;
            }

            //start from the vertex 0
            distance[sourceVertex] = 0;

            //create SPT
            for (int i = 0; i <vertices ; i++) {
                //get the vertex with the minimum distance
                int vertex_U = getMinimumVertex(spt, distance);

                //include this vertex in SPT
                spt[vertex_U] = true;

                //iterate through all the adjacent vertices of above vertex and update the keys
                for (int vertex_V = 0; vertex_V <vertices ; vertex_V++) {
                    //check of the edge between vertex_U and vertex_V

                    if(matrix[vertex_U][vertex_V]>0){
                        //check if this vertex 'vertex_V' already in spt and
                        // if distance[vertex_V]!=Infinity

                        if(spt[vertex_V]==false && matrix[vertex_U][vertex_V]!=INT_MAX){
                            //check if distance needs an update or not
                            //means check total weight from source to vertex_V is less than
                            //the current distance value, if yes then update the distance

                            int newKey =  matrix[vertex_U][vertex_V] + distance[vertex_U];
                            if(newKey<distance[vertex_V])
                                distance[vertex_V] = newKey;
                        }
                    }
                }
            }
            //print shortest path tree
            printDijkstra(sourceVertex, distance);
        }

        void printDijkstra(int sourceVertex, int key[]){
            cout << "Dijkstra Algorithm: (Adjacency Matrix)" << endl;
            for (int i = 0; i <vertices ; i++) {
                cout << "Source Vertex: " << sourceVertex << " to vertex " << i << " distance: " << key[i] << endl;
            }
        }
};
/*
int main() {
    int vertices = 6;
    Graph graph(vertices);
    int sourceVertex = 0;
    graph.addEdge(0, 1, 4);
    graph.addEdge(0, 2, 3);
    graph.addEdge(1, 2, 1);
    graph.addEdge(1, 3, 2);
    graph.addEdge(2, 3, 4);
    graph.addEdge(3, 4, 2);
    graph.addEdge(4, 5, 6);
    graph.dijkstra_GetMinDistances(sourceVertex);

    return 0;
}
*/
#endif __SHORTEST_PATH__
#include "graph.hpp"
#include "mu.hpp"
#include "shortest_path_algorithm.hpp"

using namespace std;

/*
void visualiseGraph(graph G, char *fName) {
    ofstream file;
    file.open(fName + ".txt");
    for(int i=0; i<G.nodes; i++) {
        for(int j=0; j<G.nodes; j++) {
            if(j==G.nodes-1)
                file << G.adjMat[i][j];
            else
                file << G.adjMat[i][j] << ",";
        }
        file << endl;
    }
    file.close();
}
*/

int main() {
    int vertices = 8;
    int edges = 12;

    graph inputGraph(vertices,edges);
    inputGraph.showGraph();
    cout << endl;
    all_pair_shortest_path_length(inputGraph);
    all_pair_shortest_hop_length(inputGraph);

    for(int i=0; i<inputGraph.nodes; i++){
        delete[] inputGraph.adjMat[i];
        delete[] inputGraph.apsh[i];
        delete[] inputGraph.apsp[i];
    }
    delete[] inputGraph.adjMat;
    delete[] inputGraph.apsp;
    delete[] inputGraph.apsh;

    return 0;
}

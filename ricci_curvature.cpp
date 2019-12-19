#include "graph.h"
#include "mu.h"
#include "shortest_path_algorithm.hpp"

using namespace std;

int main() {
    int vertices = 8;
    int edges = 12;
    
    graph inputGraph(vertices,edges);
    inputGraph.showGraph();
    cout << endl;
    all_pair_shortest_path_length(inputGraph.adjMat, inputGraph.apsp, inputGraph.nodes);
    all_pair_shortest_hop_length(inputGraph.adjMat, inputGraph.apsh, inputGraph.nodes);

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
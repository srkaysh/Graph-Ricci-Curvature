#include "graph.hpp"
#include "mu.hpp"
#include "shortest_path_algorithm.hpp"

using namespace std;

void visualiseGraph(graph G) {
    ofstream file;
    file.open("temp_adjMat.csv");
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
    system("python ricci.py");
}

int main() {
    int vertices = 8;
    int edges = 12;

    graph inputGraph(vertices,edges);
    inputGraph.showGraph();
    cout << endl;
    all_pair_shortest_path_length(inputGraph);
    all_pair_shortest_hop_length(inputGraph);
    visualiseGraph(inputGraph);

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

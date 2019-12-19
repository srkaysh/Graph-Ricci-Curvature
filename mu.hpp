#ifndef __MU_HPP__
#define __MU_HPP__

#include<bits/stdc++.h>
#include"graph.h"

using namespace std;

void getMu(graph G) {
    ofstream myfile;
    myfile.open("output.txt");
    int sum=0;
    for(int i=0;i<G.nodes;i++) {
        sum=0;
        for(int j=0;j<G.nodes;j++)
            sum+=G.adjMat[i][j];
        for(int j=0;j<G.nodes;j++)
            myfile<<(float)((G.adjMat[i][j]*1.0)/(sum*1.0))<<",";
        myfile<<endl;
    }
}

#endif
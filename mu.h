#include<bits/stdc++.h>
#include "graph.h"
using namespace std;
getMu(graph G)
{
    ofstream myfile;
    myfile.open("output.txt");
    int sum=0;
    for(int i=0;i<G.nodes;i++)
    {
        sum=0;
        for(int j=0;j<G.nodes;j++)
            sum+=G.adjMat[i][j];
        for(int j=0;j<G.nodes;j++)
        {
            if(j==G.nodes-1)
                myfile<<(float)((G.adjMat[i][j]*1.0)/(sum*1.0));
            else
                myfile<<(float)((G.adjMat[i][j]*1.0)/(sum*1.0))<<",";
        }
        myfile<<endl;
    }
}

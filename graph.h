#include<bits/stdc++.h>
#include <stdlib.h>
#include <time.h>
using namespace std;
class graph
{
    public:
    int nodes,edges,i,j;
    int **adjMat;
    int temp;
    graph(int n,int e)
    {
        nodes=n;
        edges=e;
        adjMat=new int*[n];
        for( i=0;i<n;i++)
        {
            adjMat[i]=new int[n];
        }
        for(i=0;i<n;i++)
            for( j=0;j<n;j++)
                adjMat[i][j]=0;
        srand (time(NULL));
        while(e>0)
        {
            i=rand()%n;
            j=rand()%n;
            if(i!=j)
            {
                if(adjMat[i][j]==0)
                {
                    temp=rand()%10+1;
                    adjMat[i][j]=temp;
                    adjMat[j][i]=temp;
                    e--;
                }
            }
        }
    }
    void showGraph()
    {
        for(int i=0;i<nodes;i++)
        {
            for(int j=0;j<nodes;j++)
                cout<<adjMat[i][j]<<" ";
            cout<<endl;
        }
    }

};

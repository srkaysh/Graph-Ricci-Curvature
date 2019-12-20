import importlib
import time

import cvxpy as cvx
import networkx as nx
import numpy as np
import matplotlib.pyplot as plt

'''
G = nx.DiGraph()
#G.add_edges_from([(1, 2), (2, 3), (3, 4), (2, 4), (4, 2), (1, 5), (5, 4)])
i=1
G.add_node(i,pos=(i,i))
G.add_node(2,pos=(2,2))
G.add_node(3,pos=(1,0))
G.add_node(4,pos=(2,0))
G.add_node(5,pos=(0,2))
G.add_node(6,pos=(3,1))
G.add_node(7,pos=(1,3))

nx.add_path(G, [1,2], weight = 6)
nx.add_path(G, [2,3], weight = 20)
nx.add_path(G, [3,4], weight = 25)
nx.add_path(G, [4,5], weight = 6)
nx.add_path(G, [5,1], weight = 3)
nx.add_path(G, [2,4], weight = 6)
nx.add_path(G, [1,6], weight = 3)
nx.add_path(G, [5,7], weight = 6)
nx.add_path(G, [6,7], weight = 6)

print("number of nodes", nx.number_of_nodes(G))
print("number of edges", nx.number_of_edges(G))

G = nx.to_undirected(G)
'''

A = np.loadtxt(open("Results/temp_adjMat.csv", "rb"), delimiter=",")
G = nx.from_numpy_matrix(A)
G.edges(data=True)
nx.draw_networkx(G, pos = None, with_labels=True, font_weight='bold')
plt.savefig("Results/inputGraph.png")

EPSILON = 1e-7  # to prevent divided by zero
weight=None; edge_list=None; method="OTD"; verbose=False

print(nx.is_weighted(G))
print(nx.is_negatively_weighted(G))
#print(nx.negative_edge_cycle(G))

length = dict(nx.all_pairs_dijkstra_path_length(G, weight = 'weight'))
hop_distance = dict(nx.all_pairs_bellman_ford_path_length(G, weight = 'weight'))
#print(length)

if not edge_list:
    edge_list = G.edges()
print(edge_list)

args = [(G, source, target, length, hop_distance, verbose, method) for source, target in edge_list]
args

scalar = 0
file1 = open("Results/Ricci_Curvature.txt","w")
file1.close()
if method == 'OTD':    #optimal transport distance
    for arg in args:
        print('The method starts here')
        G = arg[0]
        source_val = arg[1]
        target_val = arg[2]
        length_val = arg[3]
        hop_dist_val = arg[4]
        
        print("source_node and target_node is: ", source_val, target_val)
        
        assert source_val != target_val, "Self loop is not allowed."  # to prevent self loop
        # If the weight of edge is too small, return 0 instead.
        if length_val[source_val][target_val] < EPSILON:
            print("Zero Weight edge detected, return ricci Curvature as 0 instead.")
            
        source_nbr = list(nx.all_neighbors(G, source_val))
        target_nbr = list(nx.all_neighbors(G, target_val))
        
        print(source_nbr, target_nbr)
        
        # getting the value of d_x and d_y
        # construct the cost dictionary from x to y
        d = np.zeros((len(source_nbr), len(target_nbr)))
        d_x = 0; d_y = 0
        for i, s in enumerate(source_nbr):
            d_x += length_val[source_val][s]
            
        for j, t in enumerate(target_nbr):
            d_y += length_val[target_val][t]
        
        print("d_x and d_y is: ", d_x, d_y)
        #getting the matrix for hop distance
        for i, s in enumerate(source_nbr):
            for j, t in enumerate(target_nbr):
                #assert t in length[s], "Target node not in list, should not happened, pair (%d, %d)" % (s, t)
                d[i][j] = hop_dist_val[s][t]
        
        mu_x = np.zeros((len(source_nbr))) 
        #mu_x = (1.0) * len(source_nbr)
        mu_y = np.zeros((len(target_nbr)))  
        #mu_y = (1.0) * len(target_nbr)
        
        #getting the matrix mu_x and mu_y
        for i, s in enumerate(source_nbr):
            mu_x[i] = length_val[source_val][s]
        mu_x = mu_x / d_x    
        for j, t in enumerate(target_nbr):
            mu_y[j] = length_val[target_val][t]
        mu_y = mu_y / d_y
        print("modified d is: ", d)
        print(mu_x, mu_y)
        
        mu_x = np.array([mu_x]).T  # the mass that source neighborhood initially owned
        mu_y = np.array([mu_y]).T  # the mass that target neighborhood needs to received
        
        rho = cvx.Variable((len(target_nbr), len(source_nbr)))  # the transportation plan rho
        print(type(rho))
        print(np.multiply(d.T, mu_x.T))
        # objective function d(x,y) * rho * x, need to do element-wise multiply here
        obj = cvx.Minimize(cvx.sum(cvx.multiply(np.multiply(d.T, mu_x.T), rho)))
        # \sigma_i rho_{ij}=[1,1,...,1]
        source_sum = cvx.sum(rho, axis=0, keepdims=True) #adds the element column wise
        constrains = [rho * mu_x == mu_y, source_sum == np.ones((1, (len(source_nbr)))), 0 <= rho, rho <= 1]
        prob = cvx.Problem(obj, constrains)
        # solve for optimal transportation cost
        m = prob.solve(solver="ECOS_BB")  # change solver here if you want
        result = 1 - (m / hop_dist_val[source_val][target_val])  # divided by the length of d(i, j)
        scalar = scalar + result
        file1 = open("Results/Ricci_Curvature.txt","a") 
        string_to_write = "source: " + str(source_val) + ", target: " + str(target_val) + ", Olivier-Ricci curvature: " + str(result) + "\n"
        file1.write(str(string_to_write))
        file1.close() 
file1 = open("Results/Ricci_Curvature.txt","a")
file1.write("The scalar curvature is: " + str(scalar) + "\n")
file1.close()

A = nx.adjacency_matrix(G)
file1 = open("Results/inputGraph.txt","w") 
file1.write(str(A.todense())) 
file1.close() #to change file access modes 

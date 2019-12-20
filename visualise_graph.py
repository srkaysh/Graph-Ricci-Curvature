import numpy
import networkx as nx
import matplotlib.pyplot as plt

A = numpy.loadtxt(open("adjMat.csv", "rb"), delimiter=",")
G = nx.from_numpy_matrix(A)
G.edges(data=True)
nx.draw_networkx(G,pos=None,with_labels=True,font_weight='bold')
plt.savefig("inputGraph.png")
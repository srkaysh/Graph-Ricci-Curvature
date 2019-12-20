import importlib
import time
import cvxpy as cvx
import networkx as nx
import numpy as np
f=open("output.txt", "r")
if f.mode == 'r':
	contents =f.read()
contentArray=contents.split('\n')
contentArray.pop()
mu =[] 
for i in contentArray:
	mu.append(i.split(','))

for i in range(len(mu)) :
	for j in range(len(mu[i])):
		mu[i][j]=float(mu[i][j]);
for i in range(len(mu)):
	for j in range(len(mu[i])):
		if(mu[i][j]!=0):
			mux=mu[i];
			muy=mu[j];
			a1=[]
			a2=[]
			for k in range(len(mux)):
				if(mux[k]!=0):
					a1.append(k);
			for k in range(len(muy)):
				if(muy[k]!=0):
					a2.append(k)
			d= np.ones((len(a1),len(a2)))
			mux = [k for k in mux if k!=0]	
			muy = [k for k in mux if k!=0]
			
			mux=np.array([mux]).T
			muy=np.array([muy]).T
			rho = cvx.Variable((len(muy),len(mux)))
			print(len(d), len(d[0]))
			np.multiply(d.T,mux.T)
			obj=cvx.Minimize(cvx.sum(cvx.multiply(np.multiply(d.T,mux.T),rho)))
			obj = cvx.Minimize(cvx.sum(cvx.multiply(np.multiply(d.T, mux.T), rho)))
	        source_sum = cvx.sum(rho, axis=0, keepdims=True) #adds the element column wise
	        constrains = [rho * mux == muy, source_sum == np.ones((1, (len(mux)))), 0 <= rho, rho <= 1]
	       	prob = cvx.Problem(obj, constrains)
	        solve for optimal transportation cost
	        m = prob.solve(solver="ECOS_BB")
import numpy as np
import scipy as sp
import sys
import os

def analyze(m):
    d=np.linalg.det(m)
    r=np.linalg.matrix_rank(m)
    c=np.linalg.cond(m)
    cd=np.linalg.cholesky(m)
    svd=np.linalg.svd(m)
    print('--------------------')
    print(m)
    print('--------------------')
    print('rank=',r,'det=',d,'condition number=',c)
    print(cd)
    print('--------------------')
    print('singular value decomposition')
    u = svd[0]
    s = np.diag(svd[1])
    v = svd[2]
    print('u')
    print(u)
    print('sigma')
    print(s)
    print('v transpose')
    print(v.T)
    print('--------------------')
    print('reconstruct m from svd m = U*S*V.T')
    m1 = np.dot(np.dot(u, s), v.T)
    print(m1)
    print('--------------------')
    print('show u is orthognoal matrix')
    u0 = u[:,0]
    u1 = u[:,1]
    print("u0=",u0)
    print("u1=",u1)
    print('dot product of u0 dot u1 = 0')
    print(np.dot(u0,u1))
    print('u*u.T is the idenity')
    print(np.dot(u,u.T))
    print('--------------------')
    v0T = v.T[:,0]
    v1T = v.T[:,1]
    print(v0T)
    print(v1T)
    print(np.dot(v0T,v1T))
    print('--------------------')
    a1=s[0,0]*np.dot(np.reshape(u0,(2,1)),np.reshape(v0T,(1,2)))
    print(a1)
    a2=s[1,1]*np.dot(np.reshape(u1,(2,1)),np.reshape(v1T,(1,2)))
    print(a2)
    m2 = a1 + a2
    print(m2)
   
def main():
    print("start")
    m = np.array([[3, 1], [1, 2]])
    analyze(m)
    


if __name__ == '__main__' :
    main()

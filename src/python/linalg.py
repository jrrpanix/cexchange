import numpy as np
import scipy as sp
import sys
import os
from sklearn.decomposition import PCA

def analyze(m):
    #d=np.linalg.det(m)
    r=np.linalg.matrix_rank(m)
    c=np.linalg.cond(m)
    #cd=np.linalg.cholesky(m)
    svd=np.linalg.svd(m)
    print('--------------------')
    print(m)
    print('--------------------')
    print('rank=',r,'condition number=',c)
    #print(cd)
    print('--------------------')
    print('singular value decomposition')
    u = svd[0]
    s = np.zeros(m.shape)#np.diag(svd[1])
    s[0,0]=svd[1][0]
    s[1,1]=svd[1][1]
    v = svd[2]
    print('u')
    print(u)
    print('sigma')
    print(s)
    print('v transpose')
    print(v)
    print('--------------------')
    print('reconstruct m from svd m = U*S*V.T')
    m1 = np.dot(np.dot(u, s), v)
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
    print('show v is orthognoal matrix')
    v0T = v[0,:]
    v1T = v[1,:]
    print("v0.T=",v0T)
    print("v1.T=",v1T)
    print(np.dot(v0T,v1T))
    print('u*u.T is the idenity')
    print(np.dot(u,u.T))
    print('v*v.T is the idenity')
    print(np.dot(v,v.T))
    print('--------------------')
    print('recreate A matrix from indivudual components')
    print('a1 = s1 * u1 * v1.T')
    ur,uc = u.shape
    vr,vc = v.shape
    a1=s[0,0]*np.dot(np.reshape(u0,(ur,1)),np.reshape(v0T,(1,vc)))
    print(a1)
    print('a2 = s2 * u2 * v2.T')
    a2=s[1,1]*np.dot(np.reshape(u1,(ur,1)),np.reshape(v1T,(1,vc)))
    print(a2)
    print('A = a1 + a2')
    m2 = a1 + a2
    print(m2)
    print('--------------------')
    print('norms')
    A=m
    print('------------------------')
    print('norms(A)')
    print('A l1',np.linalg.norm(A, 1))
    print('A l2',np.linalg.norm(A, 2))
    print('A fro',np.linalg.norm(A, 'fro'))
    print('A inf',np.linalg.norm(A, np.inf))

    print('------------------------')
    print('norm(a1)')
    print('a1 rank', np.linalg.matrix_rank(a1))
    print('l1',np.linalg.norm(a1, 1))
    print('l2',np.linalg.norm(a1, 2))
    print('fro',np.linalg.norm(a1, 'fro'))
    print('inf',np.linalg.norm(a1, np.inf))

    dx = m-a1
    print('------------------------')
    print('norm(A-a1)')
    print('||A-a1|| l1',np.linalg.norm(dx, 1))
    print('||A-a1|| l2',np.linalg.norm(dx, 2))
    print('||A-a1|| fro',np.linalg.norm(dx, 'fro'))
    print('||A-a1|| inf',np.linalg.norm(dx, np.inf))

    # pca
    print('------------------------')
    print('pca')
    pca = PCA(n_components=2)
    pca.fit(m)  
    print(pca.explained_variance_ratio_) 
    print(pca.singular_values_) 
    z = pca.fit_transform(m)
    print(z)
    iv = pca.inverse_transform(z)
    print(iv)
    print('------------------------')
    print('recreate pca from svd')
    print('s0=',s[0,0])
    print('s1=',s[1,1])
    # step 1 center the data around means
    mu = np.mean(m, axis=0)
    print('mu-',mu)
    A0 = A - mu
    print(A0)
    # step 2 compute covar matrix
    cov = np.dot(A0.T, A0) / (len(mu)-1)
    print('covar matrix')
    print(cov)
    sv_cov = np.linalg.svd(cov)
    print("svd u", sv_cov[0])
    print("svd s", sv_cov[1])
    print("svd v", sv_cov[2]) 
    eig=np.linalg.eig(cov)
    tot = sum(sv_cov[1])
    print(sv_cov[1][0]/tot)
    print(np.sqrt(sv_cov[1]))
    print(np.sqrt(sv_cov[1])/sum(np.sqrt(sv_cov[1])))
    print(np.dot(A0, sv_cov[2]))
    
    
def main():
    print("start")
    m = np.array([[3, 1], [1, 2], [4, 1], [5,2],[11,3],[18,4]])
    analyze(m)
    


if __name__ == '__main__' :
    main()

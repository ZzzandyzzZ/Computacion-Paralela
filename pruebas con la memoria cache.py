import random as r
import numpy as np
import time
import matplotlib.pyplot as plt


def for_i_j(size):
    start_time = time.time()
    for i in range(size):
        for j in range(size):
            y[i]+=(A[i][j]*x[j])
    return time.time() - start_time
def for_j_i(size):
    start_time = time.time()
    for j in range(size):
        for i in range(size):
            y[i]+=(A[i][j]*x[j])
    return time.time() - start_time
# EJERCICIO 1
nz=10
MAX=400
name="MAX={},r=(1,{})".format(MAX,nz)
r.seed(24)
B=[[r.randint(1,nz) for _ in range(MAX)] for _ in range(MAX)]
A=[[r.randint(1,nz) for _ in range(MAX)] for _ in range(MAX)]
x=[r.randint(1,nz) for _ in range(MAX)]
t1=[]
t2=[]
it=range(50,MAX+50,50)
"""
for i in it:
    y=np.empty(i)
    t1.append(for_i_j(i))
    y=np.empty(i)
    t2.append(for_j_i(i))  
plt.plot(it,t1,label="for_i_j")
plt.plot(it,t2,label="for_j_i")
plt.xlabel("tamaño vector")
plt.ylabel("tiempo ejecucion")
plt.text(100,max(t1)*0.8,"Mean i j %.5f"%(np.mean(t1)))
plt.text(100,max(t2)*0.6,"Mean j i %.5f"%(np.mean(t2)))
plt.title(name)
plt.legend()
plt.savefig(name+".png")
plt.show()
"""
def multiply(size):
    C=np.empty((size,size))
    start_time = time.time()
    for i in range(size):
       for j in range(size):
           for k in range(size):
               C[i][j] += (A[i][k] * B[k][j])
    return time.time() - start_time
def block_multiply(size,b_size):
    C=np.empty((size,size))
    start_time = time.time()
    for i in range(0,size,b_size):
        for j in range(0,size,b_size):
            for k in range(size):
                for l in range(j,min(j+b_size,size)):
                    for m in range(i,min(i+b_size,size)):
                        C[k][l]+=(A[k][m]*B[m][l])
    return time.time() - start_time
def block_multiply_(size,b_size):
    C=np.empty((size,size))
    start_time = time.time()
    for i0 in range(0,size,b_size):
        for j0 in range(0,size,b_size):
            for k0 in range(0,size,b_size):
                for i in range(i0,min(i0+b_size,size)):
                    for j in range(j0,min(j0+b_size,size)):
                        for k in range(k0,min(k0+b_size,size)):
                            C[i][j]+=(A[i][k]*B[k][j])
    return time.time() - start_time
# ejercicio 2
"""
t3=[]
for i in it:
    t3.append(multiply(i))
name="MAX={},r=(1,{})".format(MAX,nz)
plt.plot(it,t3)
plt.xlabel("tamaño matriz")
plt.ylabel("tiempo ejecucion")
plt.title(name)
plt.savefig(name+".png")
plt.show()
"""
"""
for i in range(40,200,40):
    print(i)
    t4=[]
    for j in it:
        t4.append(block_multiply_(j,i))
    plt.plot(it,t4,label="block size="+str(i))
        
name="ej3 MAX={},r=(1,{})".format(MAX,nz)
plt.xlabel("tamaño matriz")
plt.ylabel("tiempo ejecucion")
plt.title(name)
plt.legend()
plt.savefig(name+".png")
plt.show()
"""
t5=[]
t6=[]
for i in it:
    print(i,int(i/16)+1)
    t5.append(multiply(i))
    t6.append(block_multiply_(i,int(i/16)+1))
name="comparacion MAX={},block=1_16".format(MAX,nz)
plt.xlabel("tamaño matriz")
plt.ylabel("tiempo ejecucion")
plt.title(name)
plt.plot(it,t5,label="Normal")
plt.plot(it,t6,label="Block")
plt.legend()
plt.savefig(name+".png")
plt.show()    
print("A")

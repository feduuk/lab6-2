import numpy as np
import matplotlib.pyplot as plt
data1=np.loadtxt("file111.txt")
data2=np.loadtxt("file222.txt")
data3=np.loadtxt("file333.txt")
data4=np.loadtxt("file444.txt")
data5=np.loadtxt("file555.txt")
dataT1=np.loadtxt("fileT3.txt")

plt.plot(data1[:,0],data1[:,1])
plt.plot(data2[:,0],data2[:,1])
plt.plot(data3[:,0],data3[:,1])
plt.plot(data4[:,0],data4[:,1])
plt.plot(data5[:,0],data5[:,1])
plt.plot(dataT1[:,0],dataT1[:,1])
plt.plot(dataT1[:,0],dataT1[:,1], 'o')

plt.grid(True)
plt.show()





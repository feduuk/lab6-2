import numpy as np
import matplotlib.pyplot as plt
data1=np.loadtxt("file11.txt")
data2=np.loadtxt("file22.txt")
data3=np.loadtxt("file33.txt")
data4=np.loadtxt("file44.txt")
data5=np.loadtxt("file55.txt")
dataT1=np.loadtxt("fileT2.txt")

plt.plot(data1[:,0],data1[:,1])
plt.plot(data2[:,0],data2[:,1])
plt.plot(data3[:,0],data3[:,1])
plt.plot(data4[:,0],data4[:,1])
plt.plot(data5[:,0],data5[:,1])
plt.plot(dataT1[:,0],dataT1[:,1])
plt.plot(dataT1[:,0],dataT1[:,1], 'o')

plt.grid(True)
plt.show()




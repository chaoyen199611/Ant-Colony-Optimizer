import matplotlib.pyplot as plt

path='output.txt'
f=open(path,'r')
index=[]
length=[]
num=1

for line in f:
	length.append(float(line))
	index.append(num)
	num=num+1

plt.plot(index,length)
plt.xticks([0,100,200,300,400,500,600,700,800,900,1000])
plt.yticks([400,500,600,700,800,900,1000,1100])
plt.title("Use Ant Colony Optimizaion to solve TSP", fontsize=20) 
plt.xlabel("Iteration", fontsize=10)
plt.ylabel("Length", fontsize=10)
plt.show()
import matplotlib.pyplot as plt

file=open('file.txt', 'r')
mHeap=[]
number=[]

lines = file.readlines()
for line in lines:
    i, heap=line.split()
    mHeap.append(heap)
file.close()

plt.plot(mHeap)
plt.savefig('Graph.png')
plt.show()
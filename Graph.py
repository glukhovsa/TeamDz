import matplotlib.pyplot as plt


file=open('file.txt', 'r')
mBubble=[]
mHeap=[]
number=[]
lines = file.readlines()
for line in lines:
    i, bubble, heap=line.split()
    mBubble.append(bubble)
    mHeap.append(heap)
    number.append(i)
file.close()

plt.plot(mHeap)
plt.plot(mBubble)
plt.savefig('Graph.png')
plt.show()
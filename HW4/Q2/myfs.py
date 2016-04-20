import sys as ss
from sklearn.metrics import f1_score
fp=open('output.txt')
file = 'hasit.testingop0'
fp1=open(ss.argv[1])
x = []
y = []
for i in fp1:
	x.append(str(int(i)))
for i in fp:
	y.append(str(int(i)))
fp1.close()
fp.close()

t = f1_score(x,y,average=None);
print t
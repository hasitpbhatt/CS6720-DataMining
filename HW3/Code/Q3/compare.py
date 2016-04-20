fileName = raw_input('Enter File Name 1')

d = dict()
s = []
for i in open(fileName):
	a = set(i.split());
	s.append(a)

cnt = 0
sa = 0
d = dict()
fileName = raw_input('Enter File Name 1')
for i in open(fileName):
	a = set([j for j in i.split()]);
	for j in s:
		c = a.intersection(j);
		if(len(c) > 0):
			try:
				d[len(c)] += 1
			except:
				d[len(c)] = 1
			#print 'FOUND'
for i in d:
	print i,d[i]
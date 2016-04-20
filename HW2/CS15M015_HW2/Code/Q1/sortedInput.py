d = dict()
def compare(a,b):
	return d[a]-d[b];

n = input('Enter the value of k for top-k%')
cnt = 0
for i in open('retail.dat'):
	cnt += 1
	for k in i.split():
		try:
			d[int(k)] += 1
		except:
			d[int(k)] = 1
p = d.keys()
p.sort(compare)
p = p[::-1]
p = p[:(cnt*n)/100]

filename =  raw_input('Output file name?')
g = open(filename,'w')
stra = ''
for i in open('retail.dat'):
	r = []
	for k in i.split():
		if(int(k) in p):
			r.append(k)
	if(len(r) > 0):
		stra += ' '.join(r)+'\n'
g.write(stra)
g.close()
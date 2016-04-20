from matplotlib import pyplot as plt;

fileName = raw_input('Give input file name');
start = input('start angle');
end = input('end angle');

d = dict();
#step = input('step')

for i in open(fileName):
	try:
		d[int(10*float(i))/10] += 1;
	except:
		d[int(10*float(i))/10] = 1;

a = []
b = []

for i in d.keys():
	a.append(i)
	b.append(d[i])

plt.bar(a,b);
axis = plt.gca();
axis.set_xlim(start,end);
plt.xlabel("Angle between points");
plt.ylabel("count");
plt.show()

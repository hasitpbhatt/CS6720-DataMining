import sklearn;
import numpy as np;
from sklearn.ensemble import RandomForestClassifier, BaggingClassifier, AdaBoostClassifier, GradientBoostingClassifier, ExtraTreesClassifier;
from sklearn import svm;
from sklearn.svm import SVC
from sklearn.cross_validation import StratifiedShuffleSplit
from sklearn.grid_search import GridSearchCV
from sklearn.feature_selection import RFE
from sklearn.tree import DecisionTreeClassifier
from sklearn.feature_selection import SelectKBest,chi2
from sklearn.linear_model import SGDClassifier
from sklearn.naive_bayes import GaussianNB

a = np.genfromtxt('AllFeatures');
m = np.genfromtxt('AllActiveFeatures');

#print a.size

b = [int(i[0]) for i in a];
c = [i[1:] for i in a];
#print b;

#sk = SelectKBest(chi2,k=50)
#sk.fit(c,b)
#r = RandomForestClassifier(n_estimators = 10);
#r.fit(c,b);
from sklearn.utils import resample

#from sklearn import linear_model

dc = DecisionTreeClassifier();
#pp = r.predict(m)
#for i in pp:
#	print i

et = ExtraTreesClassifier(n_jobs=-1)

#C_range = np.logspace(-2, 10, 13)
#gamma_range = np.logspace(-9, 3, 13)
#param_grid = dict(gamma=gamma_range, C=C_range)
#cv = StratifiedShuffleSplit(b, n_iter=5, test_size=0.2, random_state=42)
#grid = GridSearchCV(SVC(), param_grid=param_grid, cv=cv)
#grid.fit(c, b)
bg = BaggingClassifier(n_jobs=-1,bootstrap_features=True)

rf = RandomForestClassifier(n_estimators=100, n_jobs=-1)
#estimator=svm.SVC(class_weight='auto')
#selector = RFE(estimator, 5, step=1)

#selector.fit(c,b)c,b)
#rf.fit(c,b)
#pp = rf.predict(m)

#c = sk.transform(c)
#bg.fit(c,b)

#ad = AdaBoostClassifier(base_estimator=bg)

#ad = AdaBoostClassifier(base_estimator=bg)

gb = GradientBoostingClassifier()

gb.fit(c,b)
dc.fit(c,b)
rf.fit(c,b)
bg.fit(c,b)
et.fit(c,b)
#ad.fit(c,b)
#m = sk.transform(m)

#c,b = resample(c,b)
sgd = SGDClassifier(n_jobs=-1,class_weight='auto')
sgd.fit(c,b)

pp = rf.predict(m)
pq = bg.predict(m)
pr = gb.predict(m)
ps = dc.predict(m)
pt = et.predict(m)
#pu = ad.predict(m)
pv = sgd.predict(m)
#z = dc.predict(m)
for i in range(len(pt)):
	ans = 1
	#if(pp[i]==pr[i] and pp[i]==pq[i]):
	#	ans = pp[i]
	if(pp[i]+pq[i]+pr[i]+ps[i]+pt[i]+pv[i] < 2):
		ans = 0
	print ans
	#a = [max(pp[i][0],pq[i][0],pr[i][0],ps[i][0]),max(pp[i][1],pq[i][1],pr[i][1],ps[i][1])]
	#if(a[0] > a[1]):
	#	print -1
	#else:
	#	print 1
#for i in pq:
#	print int(i)
/*
Author : Hasit Bhatt <hasit.p.bhatt@gmail.com>
K-means clustering algorithm, to find inter/intra cluster ration for different values of k
*/

#include<bits/stdc++.h>
using namespace std;

struct Point{
	double* dimensions;
	int numberOfDimensions;

	Point() : Point(0){
	}

	Point(double n_dims) {
		numberOfDimensions = n_dims;
		dimensions = new double[numberOfDimensions];
		for(int i=0;i<n_dims;i++) 
			dimensions[i]=0;
	}

	void setDims(double dims[]) {
		for(int i=0;i<numberOfDimensions;i++)
			dimensions[i] = dims[i];
	}

	void addDims(double dims[]) {
		for(int i=0;i<numberOfDimensions;i++)
			dimensions[i] += dims[i];
	}

	string toString() {
		string s = "";
		if(numberOfDimensions)
			s = to_string(dimensions[0]);
		for(int i=1;i<numberOfDimensions;i++) {
			s += " ";
			s += to_string(dimensions[i]);
		}
		return s;
	}

	double distance(Point &p) {
		double ans = 0;
		for(int i=0;i< numberOfDimensions;i++) {
			ans += pow((p.dimensions[i]-dimensions[i]),2);
		}
		return ans;
	}

	void divide(int n) {
		for(int i=0;i<numberOfDimensions;i++)
			dimensions[i]/=n;
	}
};

void readInput(vector<Point>& points,std::string fileName,int n_dims) {
	std::ifstream fin(fileName);
	double a[n_dims];
	while(fin) {
		for(int i=0;i < n_dims ; i++) {
			fin >> a[i];
		}
		if(fin.good()) {
			Point p(n_dims);
			p.setDims(a);
			points.push_back(p);
		}
	}
	//cout << points.size() << endl;
}

double getIntraInterRatio(vector<Point>& points, int k,int numberOfDimensions);

int main(int argc, char *argv[]) {
	vector<Point> points;
	
	int numberOfDimensions;
	string fileName = "";
	ofstream fout("output.txt");

	numberOfDimensions = 4;
	fileName = "input.txt";
	switch(argc) {
		case 2: 
			fileName = argv[1];
			break;
		case 3: 
			fileName = argv[1];
			stringstream ss(argv[2]);
			ss >> numberOfDimensions;
			break;
	}
	readInput(points, fileName, numberOfDimensions);

	for(int i = 2; i < 20; i++ ) {
		cout << i << " " << getIntraInterRatio(points, i, numberOfDimensions) << endl;
		fout << i << " " << getIntraInterRatio(points, i, numberOfDimensions) << endl;
	}
	fout.close();
	return 0;
}

void show(vector<int>& v) {
	for(int i=0;i<v.size();i++) {
		if(i)
			cout << " ";
		cout << v[i];
	}
	cout <<endl;
}

double getIntraInterRatio(vector<Point>& points, int k,int numberOfDimensions) {
	int numberOfPoints = points.size();
	double tmp, mx;
	double ans , distSum = 0;
	int indexI, indexJ;
	
	map<int,int> clusterAssignment;
	int numberOfAssignedClusterId = 0;
	
	vector<int> clusterPoints[k];
	Point clusterSums[k];
	Point initCenters[k];
	Point globalCenter(numberOfDimensions);

	for(int i=0;i< numberOfPoints; i++) {
		globalCenter.addDims(points[i].dimensions);
	globalCenter.divide(numberOfPoints);

	// find k centroids
	if(k == 1) {
		for(int i=0;i< numberOfPoints; i++) {
			for(int j=i+1;j < numberOfPoints; j++) {
				distSum += points[i].distance(points[j]);
			}
		}
	}
	else {

		for(int i=0;i<k;i++) {
			random_device rd;
			initCenters[i]=Point(numberOfDimensions);
			//cout << rd.max() << endl;
			int zz = int( (double(rd()) / rd.max()) * numberOfPoints);
			//cout << zz << endl;
			initCenters[i].setDims(points[zz].dimensions);
		}
	}
	for(int i=0;i<k;i++) {
		//cout << initCenters[i].toString() << endl;
	}

	int iter = 10000;
	while(iter--) {
		for(int i=0;i<k;i++) {
			clusterPoints[i].clear();
			clusterSums[i]=Point(numberOfDimensions);
		}

		int clusterId = -1;
		for(int i=0;i<numberOfPoints;i++) {
			bool flag = false;
			for(int j = 0 ;j < k; j++ ) {
				double tmp = initCenters[j].distance(points[i]);
				if((tmp < mx) || !flag){
					mx = tmp;
					clusterId = j;
					flag = true;
				}
			}
			clusterPoints[clusterId].push_back(i);
			clusterAssignment[i]=clusterId;
			clusterSums[clusterId].addDims(points[i].dimensions);
		}

		for(int i=0;i<k;i++) {
			clusterSums[i].divide(clusterPoints[i].size());
			initCenters[i].setDims(clusterSums[i].dimensions);
		}

	}


		double interClusterDistance = 0;
		double globalIntraClusterDistance = 0;

		for(int i=0;i<k;i++) {
			//cout << i << " " << initCenters[i].toString() << endl;
			int numberOfPointsInCluster = clusterPoints[i].size();

			for(int ii = 0; ii < numberOfPointsInCluster; ii++) {
				//cout << ii << endl;
				globalIntraClusterDistance += initCenters[i].distance(points[clusterPoints[i][ii]]);
			}
			
			interClusterDistance += numberOfPointsInCluster * (globalCenter.distance(initCenters[i]));
		}
		return interClusterDistance/globalIntraClusterDistance;
	}

}
#include<bits/stdc++.h>
using namespace std;

void readGraph(ifstream &fin, ofstream &fout, bool flag) {
	string s;
	if(flag)
		fout << "#" << endl;
	while(getline(fin,s,'\n')) {
		if(s == "#")
			return;
		if(flag)
			fout << s << endl;
	}
}

int main(int argc, char* argv[]) {
	int n=0, cnt = 0;
	if(argc != 4) {
		cout << "Kindly provide input file" << endl;
		cout << "e.g. genDFSCode training.txt active.txt inactive.txt testing.txt" << endl;
		return 1;
	}

	ifstream fin(argv[1]);
	string s;
	getline(fin,s,'\n');
	vector<int> v;
	while(fin >> n) {
		v.push_back(n);
	}
	fin.close();
	fin.open(argv[2]);
	int vSize = v.size();
	ofstream fout(argv[3]);

	for(int i=0;cnt<vSize;i++) {
		if(i==v[cnt]) {
			readGraph(fin,fout,true);
			cnt++;
		}
		else
			readGraph(fin,fout,false);
	}
	fin.close();
	fout.close();
	return 0;
}
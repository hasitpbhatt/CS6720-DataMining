#include<bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
	string outputFile = "training.hasit";
	string outputFile1 = "testing.hasit";
	string outputFile2 = "active.hasit";
	string outputFile3 = "inactive.hasit";
	string outputFile4 = "training.active.hasit";
	string outputFile5 = "training.inactive.hasit";
	string outputFile6 = "training.hasitop";

	int n=0, m=0, mc = 0, cnt = 0,a,b,c;
	if(argc != 5) {
		cout << "Kindly provide input file" << endl;
		cout << "e.g. genDFSCode training.txt active.txt inactive.txt testing.txt" << endl;
		return 1;
	}
	unordered_map<string,int> mymap;
	unordered_map<int,int> myactive;
	ifstream fi(argv[2]);
	while(fi >> n) {
		myactive[n] = 1;
	}
	fi.close();
	fi.open(argv[3]);
	while(fi >> n) {
		myactive[n] = 2;
	}
	fi.close();
	ifstream fin(argv[1]);
	ofstream fout(outputFile);
	ofstream fout1(outputFile2);
	ofstream fout2(outputFile3);
	ofstream fout3(outputFile4);
	ofstream fout4(outputFile5);
	ofstream flabel(outputFile6);
	string tmp;
	int s;
	char ch;
	while(fin >> ch >> s) {
		bool flag = (myactive[s]>0);

		if(flag) {
			if(myactive[s] == 1)
				flabel << myactive[s] << endl;
			else
				flabel << -1 << endl;
			
			if(myactive[s] == 1)
				fout1 << s << endl;
			else
				fout2 << s << endl;
		}
		if(flag) {
			fout << "t " << ch << " " << s << endl;
			if(myactive[s] == 1)
				fout3 << "t " << ch << " " << s << endl;
			else
				fout4 << "t " << ch << " " << s << endl;
		}

		fin >> n;

		for(int i=0;i<n;i++) {
			fin >> tmp;
			if( mymap[tmp] == 0 )
				mymap[tmp]=++mc;
			if(flag) {
				fout << "v " << i << " " << mymap[tmp] << endl;
				if(myactive[s] == 1)
					fout3 << "v " << i << " " << mymap[tmp] << endl;
				else
					fout4 << "v " << i << " " << mymap[tmp] << endl;
			}
		}

		fin >> m;
		for(int i=0;i<m;i++) {
			fin >> a >> b >> c;
			if(flag) {
				fout << "u " << a << " " << b << " " << c << endl;
				if(myactive[s] == 1)
					fout3 << "u " << a << " " << b << " " << c << endl;
				else
					fout4 << "u " << a << " " << b << " " << c << endl;
			}
		}
		cnt++;
	}
	cout << cnt << " in training file" << endl;

	cnt = 0;
	fin.close();
	fout.close();
	fin.open(argv[4]);
	fout.open(outputFile1);
	while(fin >> ch >> s) {

		fout << "t " << ch << " " << s << endl;
		fin >> n;

		for(int i=0;i<n;i++) {
			fin >> tmp;
			if( mymap[tmp] == 0 )
				mymap[tmp] = ++mc;
			fout << "v " << i << " " << mymap[tmp] << endl;
		}
		fin >> m;

		for(int i=0;i<m;i++) {
			fin >> a >> b >> c;
			fout << "u " << a << " " << b << " " << c << endl;
		}
		cnt++;
	}
	cout << cnt << " in testing file" << endl;
	return 0;
}
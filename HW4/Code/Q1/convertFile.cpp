#include<bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
	string outputFile = "output.txt";
	int n, m, cnt = 0,a,b,c;
	if(argc != 2) {
		cout << "Kindly provide input file" << endl;
		cout << "e.g. genDFSCode input.txt" << endl;
		return 1;
	}
	ifstream fin(argv[1]);
	ofstream fout(outputFile);
	string s,tmp;
	char ch;
	while(fin >> ch >> s) {
		cout << "..." << endl;
		fout << "t " << ch << " " << s << endl;
		fin >> n;
		cout << "n: " << n << endl;
		for(int i=0;i<n;i++) {
			fin >> tmp;
			fout << "v " << i << " " << tmp << endl;
		}
		fin >> m;
		cout << "m: " << m << endl;
		for(int i=0;i<m;i++) {
			fin >> a >> b >> c;
			fout << "u " << a << " " << b << " " << c << endl;
		}
		cnt++;
	}
	cout << cnt << endl;
	return 0;
}
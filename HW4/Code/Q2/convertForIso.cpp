#include<bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
	int n;
	char ch;
	string tmp,final="";
	int flag = 0, cnt = 0;

	ifstream fin(argv[1]);
	ofstream fout(argv[2]);
	string s="";
	while(getline(fin,s,'\n')) {

		stringstream ss(s);
		ss >> ch;
		if(ch == 't') {
			if(flag == 2) {
				fout << cnt << endl;
				if(cnt != 0)
				fout << final;
			}
			final = "";
			cnt = flag = 0;
			fout << '#' << endl;
		}
		else if(ch == 'v') {

			ss >> n;
			ss >> n;

			final += to_string(n) + "\n";

			flag = 1;
			cnt++;
		}
		else if(ch == 'u') {
			if(flag == 1) {
				fout << cnt << endl;
				fout << final;
				cnt = 0;
				final = "";
				flag = 2;
			}

			string k;
			getline(ss,k,' ');
			getline(ss,k,'\n');
			final += k + "\n";

			cnt++;
		}
	}
	if(flag) {
		fout << cnt << endl;
		if(cnt != 0)
			fout << final;
		final = "";
	}
	fin.close();
	fout.close();

	return 0;
}

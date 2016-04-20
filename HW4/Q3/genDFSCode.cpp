#include<bits/stdc++.h>
using namespace std;

string myMinT = "";

int start_time = 0;
double threshold = 0;
double maxSeconds = 0.2;

struct Edge {
	string label1, label2;
	int edgelabel,id1,id2;
	bool operator<(const Edge& e) {
		if(label1 < e.label1)
			return true;
		else if((label1 == e.label1) && (edgelabel<e.edgelabel))
			return true;
		else if((label1 == e.label1) && (edgelabel==e.edgelabel) && (label2 < e.label2))
			return true;
		return false;
	}

	bool operator== (const Edge& e) {
		if((label1 == e.label1) && (edgelabel==e.edgelabel) && (label2 == e.label2))
			return true;
		return false;
	}

	Edge(int a,int b,string l1,string l2,int el) {
		id1 = a;
		id2 = b;
		label1 = l1;
		label2 = l2;
		edgelabel = el;
	}

	string toString() {
		string s = "";
		s += to_string(id1);
		s += ',';
		s += to_string(id2);
		s += ',';
		s += label1;
		s += ',';
		s += label2;
		s += ',';
		s += to_string(edgelabel);
		return s;
	}
};

bool lesserTree(string s1,string s2) {
	stringstream in1(s1);
	stringstream in2(s2);
	char c1,c2;

	int is1,is2,js1,js2;

	int els1,els2;

	string ils1,ils2,jls1,jls2;

	bool isForward1, isForward2,t1,t2;

	while((t1=(in1 >> c1)) && (t2=(in2 >> c2))) {

		in1 >> is1;
		in2 >> is2;
		
		in1 >> c1;
		in2 >> c2;

		in1 >> js1;
		in2 >> js2;
		
		in1 >> c1;
		in2 >> c2;

		getline(in1,ils1,',');
		getline(in2,ils2,',');
		
		in1 >> els1;
		in2 >> els2;
		
		in1 >> c1;
		in2 >> c2;

		getline(in1,jls1,'>');
		getline(in2,jls2,'>');

		if((jls1==jls2) && (ils1==ils2) && (els1==els2) && (is1==is2) && (js1==js2)) {
			continue;
		}

		isForward1 = (is1 < js1);
		isForward2 = (is2 < js2);


		if(isForward1 && isForward2) {
			if(is2 < is1)
				return true;
			else if(is1 < is2)
				return false;
			if(ils1 < ils2){
				return true;
			}
			else if(ils2 < ils1)
				return false;
			if(els1 < els2) {
				return true;
			}
			else if(els2 < els1)
				return false;
			else if(jls1 < jls2)
				return true;
			else if(jls1 > jls2)
				return false;
		}

		if(isForward1 && !isForward2) {
			return false;
		}

		if(!isForward1 && isForward2) {
			return true;
		}

		if(!isForward1 && !isForward2) {
			if(js1 < js2)
				return true;
			else if(js2 < js1)
				return false;
			else if((js1 == js2) && els1 < els2)
				return true;
		}

	}
	if(t2)
		return true;
	return false;
}

struct Graph {
	int noNodes;
	int noEdges;
	int cnt;
	int *M;
	vector<string> v;
	set<string> labels;
	set<int> edgelabels;
	unordered_map<int,vector<int> > adjList;
	vector<Edge> edges;

	Graph() {
		noNodes = 0;
		noEdges = 0;
		cnt = 0;
	}

	Graph(int n): Graph() {;
		noNodes = n;
		M = new int[n*n];
		memset(M,0,sizeof(int)*n*n);
	}

	void addNode(string s) {
		v.push_back(s);
		cnt++;
		labels.insert(s);
	};

	void addEdge(int a,int b,int c) {
		put(a,b,c);
		put(b,a,c);
		edgelabels.insert(c);
		Edge k(a,b,v[a],v[b],c);
		edges.push_back(k);
		Edge m(b,a,v[b],v[a],c);
		edges.push_back(m);
		noEdges+=2;
	}

	int get(int i,int j) {
		return M[noNodes*i+j];
	}

	void put(int i,int j,int k) {
		M[noNodes*i+j]=k;
	}

	string buildStr(int a,int b,string c,string d, int e) {
		string s = "";
		s += "<";
		s += to_string(a);
		s += ",";
		s += to_string(b);
		s += ",";
		s += c;
		s += ",";
		s += to_string(e);
		s += ",";
		s += d;
		s += ">";
		return s;
	}

	struct mySort {
			vector<Edge> e;
			mySort(vector<Edge>& v) {
				e = v;
			}
			bool operator() (const int& a,const int& b){
				return e[a] < e[b];
			}
		};

	string minDfsCodeFromA(string mytry1, vector<int>& m, int level, bool explore,bool visited[],int last,int prev) {

		string q = "";
		int mSize = m.size();
		bool orvis[noNodes];
		for(int i=0;i<noNodes;i++)
			orvis[i]=visited[i];

		if(level == 0) {
			q = buildStr(0,1,v[m[0]],v[m[1]],get(m[0],m[1]));
		}

		if(clock()-start_time > threshold) {
			cout << "...." << endl;
			return "-";
		}

		// add back edges
			for(int i=0;i<last;i++) {
				int t = get(m[last],m[i]);
				if((t > 0) && i!=prev){
					q += buildStr(last,i,v[m[last]],v[m[i]],t);
				}
			}

		bool flag = false;
		int lastEdge = -1;
		string t, minT="";
		if(flag == false) {
			for(int ka=last;ka>=0;ka--) {
				vector<int>& z = adjList[m[ka]];
				for(int i=0;i<z.size();i++) {
					if(!visited[edges[z[i]].id2]) {

					if(!flag) {
						lastEdge = z[i];
						flag = true;
						int cnt=0;
						int j = i+1;
						while(j < z.size()) {
							if(!visited[edges[z[j]].id2] && (edges[lastEdge]==edges[z[j]]))
								cnt++;
							j++;
						}
					int next=edges[lastEdge].id2;
					m.push_back(next);
					visited[next] = true;
					minT = buildStr(ka,mSize,v[m[ka]],v[next],edges[lastEdge].edgelabel);

					string s = minDfsCodeFromA(mytry1+q+minT,m,level + 1, true, visited,m.size()-1,ka);
					if(s=="-")
						return "-";
					minT += s;

					while(m.size() != mSize)
						m.pop_back();
					
					// If only one, break
						if(cnt==0) {
							break;
						}
						for(int i=0;i<noNodes;i++) {
							visited[i]=orvis[i];
						}
					}

					else if(!(edges[lastEdge] < edges[z[i]])) {
						lastEdge = z[i];
						flag = true;
						int cnt=0;
						int j = i+1;
							while(j < z.size()) {
								if(!visited[edges[z[j]].id2] && !(edges[z[i]]<edges[z[j]]))
									cnt++;
								j++;
							}
						int next=edges[lastEdge].id2;
						m.push_back(next);
						visited[next] = true;
						t = buildStr(ka,mSize,v[m[ka]],v[next],edges[lastEdge].edgelabel);
						//cout << ".." << minT << endl;
						string s;
						s = minDfsCodeFromA(mytry1+q+t,m,level + 1, true, visited,m.size()-1,ka);
						while(m.size() != mSize)
							m.pop_back();
						if(s=="-")
							return "-";

						t += s;

					if((minT.length()==0) || (lesserTree(t,minT))) {
						minT = t;
					}
				}
			}
		}
			if(flag)
				break;
			}
		}
		if(!flag) {
			if(myMinT.length() == 0) {
				myMinT = mytry1+q;
			}
		}

		q += minT;
		return q;
	}

	string minDfsCode() {
		start_time = clock();
		sort(edges.begin(),edges.end());

		for(int i=0;i<noEdges;i++) {
			adjList[edges[i].id1].push_back(i);
		}

		string ans= "",t;
		for(int i=0;i<noEdges;i++) {

			if(edges[0] < edges[i]) {
				continue;
			}
			else {
				vector<int> z;
				z.push_back(edges[i].id1);
				z.push_back(edges[i].id2);
				string s;
				s=buildStr(0,1,edges[i].label1,edges[i].label2,edges[i].edgelabel);
				bool vis[noNodes];
				memset(vis,0,sizeof(bool)*noNodes);
				vis[z[0]]=vis[z[1]]=true;
				t = minDfsCodeFromA("",z,0,true,vis,1,0);

				if(t == "-") {
					if(myMinT.length() == 0)
						return "NA";
					else
						return myMinT;
				}
				if(myMinT.length() == 0)
					myMinT = t;
				else if(lesserTree(t,myMinT)) {
					myMinT = t;
				}
			}
		}
		return myMinT;
	}

	~Graph() {
		delete []M;
		adjList.clear();
	}

};

int main(int argc, char* argv[]) {
	string outputFile = "output.txt";
	int n, m, cnt = 0,a,b,c;
	if(argc != 2) {
		cout << "Kindly provide input file" << endl;
		cout << "e.g. genDFSCode input.txt" << endl;
		return 1;
	}
	threshold = CLOCKS_PER_SEC*maxSeconds;
	ifstream fin(argv[1]);
	ofstream fout(outputFile);
	string s,tmp;
	char ch;
	while(fin >> ch >> s) {
		myMinT = "";

		fin >> n;
		Graph graph(n);

		for(int i=0;i<n;i++) {
			fin >> tmp;
			graph.addNode(tmp);
		}
		fin >> m;

		for(int i=0;i<m;i++) {
			fin >> a >> b >> c;
			graph.addEdge(a,b,c);
		}
		cnt++;

		cout << "#" << s << endl;

		fout << graph.minDfsCode() << endl;

	}
	return 0;
}
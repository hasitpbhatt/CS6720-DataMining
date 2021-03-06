/*
Author : Hasit Bhatt <hasit.p.bhatt@gmail.com>
*/
#include <bits/stdc++.h>
#include "Transaction.hpp"
#include "UtilsApriori.hpp"
#include "DebugUtils.hpp"
#include <fstream>

#define endl "\n"
#define dout if(DEBUG) std::cout 

void addTransactionToFrequentTransactionList(
	std::vector<Transaction> &frequentTransactions,std::vector<std::string> &currentFrequentItemSetList);

int compareAsIntegers(
	Transaction &a, Transaction &b);

int compareAsStrings(
	Transaction &a, Transaction &b);

std::map<std::string, int> generateCandidateSet(
	std::vector<std::string> &currentFrequentItemSetList);

double getSupport(
	int argc, char* argv[]);

std::string getFileName(
	int argc, char* argv[]);

std::vector<std::string> getFilteredItemList(
	double minimumSupportFrequency,std::map<std::string,int> &itemSupportMap);

void printList(
	std::vector<std::string> &m);

void printMap(
	std::map<std::string,int> &m);

void printMapKeys(
	std::map<std::string,int> &m);

void printTransactions(
	std::vector<Transaction> &transactions, bool flag=false);

void sortTransactions(
	std::vector<Transaction> &frequentTransactions);


int main(int argc, char* argv[]) {
	double support = getSupport(argc, argv);
	dout << "Support is: " << support << endl;
	std::string filename = getFileName(argc, argv);
	dout << "Filename is: " << filename << endl;
	std::map<std::string, int> itemSupportMap, currentCandidateSetList;
	std::vector<Transaction> frequentTransactions;
	std::vector<std::string> currentFrequentItemSetList;
;
	int numberOfTransactions = UtilsApriori::initTransactions(filename,itemSupportMap);

	currentFrequentItemSetList = getFilteredItemList(support * numberOfTransactions,itemSupportMap);

	if(DEBUG) {
		std::cout << "Single itemset filtered by minSupport" << endl;
		printList(currentFrequentItemSetList);
	}

	addTransactionToFrequentTransactionList(frequentTransactions, currentFrequentItemSetList);

	for(int k=2;currentFrequentItemSetList.size();k++) {
		currentCandidateSetList = generateCandidateSet(currentFrequentItemSetList);

		dout << "Candidate list for iteration#" << k << endl;
		if(DEBUG)
			printMap(currentCandidateSetList);
		currentFrequentItemSetList.clear();

		UtilsApriori::countTransactions(filename, currentCandidateSetList);

		dout << "currentCandidateSetList size=" << currentCandidateSetList.size() << endl;
		if(DEBUG)
		printMapKeys(currentCandidateSetList);

		currentFrequentItemSetList = getFilteredItemList(support * numberOfTransactions,currentCandidateSetList);
		dout << "currentFrequentItemSetList size=" << currentFrequentItemSetList.size() << endl;

		addTransactionToFrequentTransactionList(frequentTransactions, currentFrequentItemSetList);

	}

	if((UTILS_APRIORI_DEFAULT_TYPE == "int") && std::string(argv[2])!="s")
		sortTransactions(frequentTransactions);
	
	printTransactions(frequentTransactions);
	return 0;
}

void addTransactionToFrequentTransactionList(
	std::vector<Transaction> &frequentTransactions,std::vector<std::string> &currentFrequentItemSetList) {
		for(std::vector<std::string>::iterator it =  currentFrequentItemSetList.begin(); 
			it != currentFrequentItemSetList.end(); it++) {
				Transaction t(*it);
				frequentTransactions.push_back(t);
		}
}

int compareAsIntegers(Transaction &a, Transaction &b) {
	if(a.getCount() < b.getCount()) {
		return 1;
	}
	else if(a.getCount()==b.getCount()){
		std::vector<int> va;
		std::vector<int> vb;
		for(int i=0;i<a.getCount();i++) {
			va.push_back(std::stoi(a.getItems()[i]));
		}
		for(int i=0;i<b.getCount();i++) {
			vb.push_back(std::stoi(b.getItems()[i]));
		}
		sort(va.begin(),va.end());
		sort(vb.begin(),vb.end());
		for(int i=0;i<a.getCount();i++) {
			if(va[i] < vb[i])
				return va[i]-vb[i];
			else if(va[i] > vb[i])
				return 0;
		}
	}
	return 0;
}

int compareAsStrings(Transaction &a, Transaction &b) {
	if(a.getCount() < b.getCount()) {
		return 1;
	}
	return 0;
}

std::string getFileName(int argc, char* argv[]) {
	if(argc > 2) {
		return argv[1];
	}
	else {
		std::string str;
		UtilsApriori::getDefaultFileName(str);
		return str;
	}
}

std::vector<std::string> getFilteredItemList(double minimumSupportFrequency,std::map<std::string,int> &itemSupportMap) {
	std::vector<std::string> m;

	for(std::map<std::string,int>::iterator it=itemSupportMap.begin(); it != itemSupportMap.end(); it++) {
		if(it->second >= minimumSupportFrequency) {
			m.push_back(it->first);
		}
	}

	return m;
}

double getSupport(int argc, char* argv[]) {
	if(argc > 1) {
		double tmp = std::stod(argv[argc-1]);
		if((tmp >0) && (tmp<1)){
			return tmp;
		}
	}
	return UtilsApriori::getDefaultSupport();
}

std::map<std::string, int> generateCandidateSet(std::vector<std::string> &currentFrequentItemSetList) {

	std::vector<std::string> z;
	std::map<std::string, int> m;

	int cnt = currentFrequentItemSetList.size();
	for(int i = 0 ; i < cnt ; i++ ) {
		Transaction a(currentFrequentItemSetList[i]);
		for(int j = i+1; j < cnt; j++ ) {
			Transaction b(currentFrequentItemSetList[j]);
			bool flag = true;
			for(int k=0;k<a.getCount()-1;k++) {
				if(a.getItems()[k]!=b.getItems()[k]) {
					flag = false;
					break;
				}
			}
			if(flag) {
				Transaction c(currentFrequentItemSetList[i]);
				c.add(b.getItems().back());
				z.push_back(c.toString());
			}
			else {
				dout << a.toString() << " and " << b.toString() << " are not compatible." << endl;
			}
		}

		int cntz = z.size();
		for(int i=0;i<cntz;i++) {
			bool flag = true;
			int size = z[i].size();
			for(int j=0;j<size;j++) {
				Transaction t(z[i]);
				t.getItems().erase(t.getItems().begin()+j);
				if(find(currentFrequentItemSetList.begin(),currentFrequentItemSetList.end(),t.toString()) == currentFrequentItemSetList.end()) {
					flag = false;
					break;
				}
			}
			if(flag)
				m[z[i]]=0;
		}
	}
	return m;
}

void printList(std::vector<std::string> &m) {
	for(std::vector<std::string>::iterator it=m.begin(); it != m.end(); it++)
		std::cout << *it << endl;
}

void printMap(std::map<std::string,int> &m) {
	for(std::map<std::string,int>::iterator it=m.begin(); it != m.end(); it++)
		std::cout << it->first << endl;
}

void printMapKeys(std::map<std::string,int> &m) {
	for(std::map<std::string,int>::iterator it=m.begin(); it != m.end(); it++)
		std::cout << it->first << " " << it->second << endl;
}

void printTransactions(std::vector<Transaction> &transactions, bool flag) {
	std::ofstream fout("CS15M015_1a.txt");
	for(std::vector<Transaction>::iterator it= transactions.begin() ; it != transactions.end() ; it++) {
		std::cout << (*it).toString() << endl;
		fout << (*it).toString() << endl;
	}
	fout.close();
}

void sortTransactions(std::vector<Transaction> &frequentTransactions) {
	//if(UTILS_APRIORI_DEFAULT_FILENAME == "int") {
		sort(frequentTransactions.begin(),frequentTransactions.end(),compareAsIntegers);
	//}
	//else {
	//	sort(frequentTransactions.begin(),frequentTransactions.end(),compareAsStrings);
	//}
}

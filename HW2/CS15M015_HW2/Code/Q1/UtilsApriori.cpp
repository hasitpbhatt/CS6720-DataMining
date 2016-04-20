#include "DebugUtils.hpp"
#include "Transaction.hpp"
#include "UtilsApriori.hpp"

double UtilsApriori::getDefaultSupport() {
	return UTILS_APRIORI_DEFAULT_SUPPORT;
}

int UtilsApriori::initTransactions(std::string inputFileName, std::map<std::string,int> &m) {
	std::ifstream inputStream(inputFileName);
	std::string transactionString;

	int cnt = 0;
	while(getline(inputStream,transactionString,'\n')) {
		Transaction transaction(transactionString);

		for(std::vector<std::string>::iterator it = transaction.getItems().begin() ; it != transaction.getItems().end() ; it++) {
			m[*it]++;
		}

		if(DEBUG_TRANSACTION) {
			std::cout << "Transaction size : " << transaction.getCount() << std::endl;
		}
		cnt++;
	}

	if(DEBUG_TRANSACTION)
		std::cout << "Total transactions : " << cnt << std::endl;

	return cnt;
}

int UtilsApriori::countTransactions(std::string inputFileName, std::map<std::string,int> &n) {
	std::ifstream inputStream(inputFileName);
	std::string transactionString;

	std::map<std::string,int> m;

	int cnt = 0;

	while(getline(inputStream,transactionString,'\n')) {
		//std::cout << "wwwwwwwww" << std::endl;
		Transaction transaction(transactionString);

		m.clear();
		for(std::vector<std::string>::iterator it = transaction.getItems().begin() ; it != transaction.getItems().end() ; it++) {
			m[*it]++;
		}

		//if(DEBUG)
		//	std::cout << transactionString << std::endl;

		for(std::map<std::string,int>::iterator it = n.begin() ; it != n.end() ; it++) {
			Transaction r(it->first);
			bool flag = true;
			for(int i = 0; i < r.getCount() ; i++) {
				if(m[r.getItems()[i]] != 1) {
					flag = false;
					break;
				}
			}
			if(flag) {
				(it->second)++;
			}
		}

		if(DEBUG_TRANSACTION) {
			std::cout << "Transaction size : " << transaction.getCount() << std::endl;
		}
		cnt++;
	}

	if(DEBUG_TRANSACTION)
		std::cout << "Total transactions : " << cnt << std::endl;

	return cnt;
}

void UtilsApriori::getDefaultFileName(std::string &str) {
	str = UTILS_APRIORI_DEFAULT_FILENAME;
}
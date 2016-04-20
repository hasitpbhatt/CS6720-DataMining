#ifndef UTILS_APRIORI_HPP
#define UTILS_APRIORI_HPP

#include<iostream>
#include<fstream>
#include<map>
#include<sstream>
#include<string>
#include<vector>

#define UTILS_APRIORI_DEFAULT_SUPPORT 0.1
#define UTILS_APRIORI_DEFAULT_FILENAME "retail.dat"
#define UTILS_APRIORI_DEFAULT_TYPE "int"

class UtilsApriori {
	public:
		static double getDefaultSupport();
		static void getDefaultFileName(std::string &str);
		static int initTransactions(std::string inputFileName, std::map<std::string,int> &m);
		static int countTransactions(std::string inputFileName, std::map<std::string,int> &n);
};
#endif
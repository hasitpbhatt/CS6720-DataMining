#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP
#include<vector>
#include<sstream>
#include<string>

class Transaction {
	std::vector<std::string> items;
	int itemCount;

	public:
	Transaction();
	Transaction(std::string transactionString);

	std::vector<std::string>& getItems();

	int getCount();

	bool contains(std::string item);

	std::string toString();

	bool add(std::string item);

};
#endif
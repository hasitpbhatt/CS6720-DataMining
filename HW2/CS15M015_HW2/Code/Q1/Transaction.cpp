#include"Transaction.hpp"
#include "DebugUtils.hpp"

Transaction::Transaction() {
		itemCount = 0;
	}

Transaction::Transaction(std::string transactionString) : Transaction::Transaction(){
		std::stringstream transactionStream(transactionString);
		std::string item;
		while(transactionStream) {
			transactionStream >> item;
			add(item);
		}
	}

std::vector<std::string>& Transaction::getItems() {
		return items;
	}

	int Transaction::getCount() {
		return items.size();
	}

	bool Transaction::contains(std::string item) {
		std::vector<std::string>::iterator it = lower_bound(items.begin(),items.end(),item);
		return (it!=items.end()) && (*it==item);
	}

	std::string Transaction::toString() {
		std::string s = "";
		itemCount = getCount();
		for(int i = 0 ; i < itemCount ; i++ ) {
			s += items[i];
			if(i != itemCount-1)
				s += " ";
		}
		return s;
	}

	bool Transaction::add(std::string item) {
		if(contains(item)) {
			// Trying to add the same item again
			return false;
		}
		else {
			items.push_back(item);
			itemCount++;
			return true;
		}
	}
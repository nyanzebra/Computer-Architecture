#pragma once

#ifndef _LAMBDAS_H_
#define _LAMBDAS_H_

#include <string>
#include <vector>

const auto L_makeByteVector = [](const int& n) { return std::vector<byte>(n); };
const auto L_makeMemoryAddressVector = [](const int& n) { return std::vector<memory_address>(n); };

const auto L_initStack = [](const int& n) {
	return std::list<std::string>(n);
};

const auto L_instructionAndOperand = [](const std::string& s) {
	std::vector<std::string> v;
	std::string temp = "";
	for (char c : s){
		if (c != '`') {
			temp += c;
		}
		else {
			v.push_back(temp);
			temp = "";
		}
	}
	if (temp.size() > 0) {
		v.push_back(temp);
	}
	return v;
};

const auto L_listToString = [](const std::list<byte>& l) {
	std::string s;
	for (char c : l) {
		s += c;
	}
	return s;
};

const auto L_stringToList = [](const std::string& s) {
	std::list<byte> lb;
	for (char c : s) {
		lb.push_back(c);
	}
	return lb;
};

#endif
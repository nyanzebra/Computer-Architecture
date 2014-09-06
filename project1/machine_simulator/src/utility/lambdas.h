#pragma once

//robert baldwin
//lambdas header
//may be able to be inlined??
//these are global functions mainly for conversions and static inits
//if we switch to binary encoding this can be axed
//
//if adding to this follow the format : capital L for lambda followed by detailed method description
//for example if you wanted one that was initialize static container it should be L_makeContainer

#ifndef LAMBDAS_H
#define LAMBDAS_H

#ifndef PCH_H
#include "../pch.h"
#endif

//all must have const in order to not be defined twice... or more
const auto L_makebyte_tVector = [](const int& n) { return std::vector<byte_t>(n); };
const auto L_makeMemoryAddressVector = [](const int& n) { return std::vector<memoryAddress_s>(n); };

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

const auto L_listToString = [](const std::list<byte_t>& l) {
	std::string s;
	for (char c : l) {
		s += c;
	}
	return s;
};

const auto L_stringToList = [](const std::string& s) {
	std::list<byte_t> lb;
	for (char c : s) {
		lb.push_back(c);
	}
	return lb;
};

#endif
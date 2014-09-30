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

#include <vector>
#include <array>

#include "types.h"

//all must have const in order to not be defined twice... or more
const auto L_makedata_tVector = [](const int& n) { return std::vector<data_t>(n); };

const auto L_makeRegisters = []() {
	std::array<reg_t, 32> init = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	return init;
};

#endif
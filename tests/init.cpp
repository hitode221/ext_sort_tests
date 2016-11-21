#include "ext_sort.h"
#include <catch.hpp>
#include <iostream>
#include <fstream>

SCENARIO("sort", "[sort]") {
	ext_sort("random.txt", "result.txt", 256);
	std::ifstream expected("expected.txt");
	std::ifstream output("result.txt");
	std::string first, second;
	bool flag = true;
	while (expected || output) {
		std::getline(expected, first);
		std::getline(output, second);
		if (first != second) {
			flag = false;
			break;
		}
	}
	REQUIRE(flag);
}

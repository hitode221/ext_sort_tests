#include "ext_sort.h"
#include <catch.hpp>
#include <iostream>
#include <fstream>

SCENARIO("sort 8mb", "[sort]") {
	ext_sort("8", "sort_8.txt", 1);
	std::ifstream expected("sort8.txt");
	std::ifstream output("sort_8.txt");
	/*std::string first, second;
	bool flag = true;
	while (expected || output) {
		std::getline(expected, first);
		std::getline(output, second);
		if (first != second) {
			flag = false;
			break;
		}
	}
	REQUIRE(flag);*/
	std::string temp;
	size_t t = 0;
	std::getline(output, temp);
	while(!output.eof()) {
		std::getline(output, temp);
		++t;
	}
	REQUIRE(t == 422492+1);
  	output.close();
}

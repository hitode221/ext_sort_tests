#include "ext_sort.h"
#include <catch.hpp>
#include <iostream>
#include <fstream>

SCENARIO("sort 8mb", "[sort]") {
	ext_sort("8", "sort_8.txt", 1);
	std::ifstream output("sort_8.txt");
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

SCENARIO("sort 15mb", "[sort]") {
	ext_sort("15", "sort_15.txt", 4);
	std::ifstream output("sort_15.txt");
	std::string temp;
	size_t t = 0;
	std::getline(output, temp);
	while(!output.eof()) {
		std::getline(output, temp);
		++t;
	}
	REQUIRE(t == 792011+1);
  	output.close();
}

SCENARIO("sort 32mb", "[sort]") {
	ext_sort("32", "sort_32.txt", 17);
	std::ifstream output("sort_32.txt");
	std::string temp;
	size_t t = 0;
	std::getline(output, temp);
	while(!output.eof()) {
		std::getline(output, temp);
		++t;
	}
	REQUIRE(t == 1637032+1);
  	output.close();
}


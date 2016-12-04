#include "ext_sort.h"
#include <catch.hpp>
#include <iostream>
#include <fstream>
#include <chrono>

SCENARIO("sort 8mb", "[sort]") {
	auto start_time = std::chrono::steady_clock::now();
	ext_sort("8", "sort_8.txt", 1);
	auto end_time = std::chrono::steady_clock::now();
	auto elapsed_s = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
	std::cout << "8mb: " << elapsed_s.count() << " ms" << std::endl;
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
	auto start_time = std::chrono::steady_clock::now();
	ext_sort("15", "sort_15.txt", 4);
	auto end_time = std::chrono::steady_clock::now();
	auto elapsed_s = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
	std::cout << "15mb: " << elapsed_s.count() << " ms" << std::endl;
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
	auto start_time = std::chrono::steady_clock::now();
	ext_sort("32", "sort_32.txt", 17);
	auto end_time = std::chrono::steady_clock::now();
	auto elapsed_s = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
	std::cout << "32mb: " << elapsed_s.count() << " ms" << std::endl;
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


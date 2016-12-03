#pragma once
#include <fstream>
#include <vector>
#include <string>
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <sstream>

struct man {
	std::string last_name, first_name;
	size_t year;
	bool operator <(const man & data) const{
		return  first_name < data.first_name;
	}
	bool operator<=(const man & data) const{
		return  first_name <= data.first_name;
	}
};
bool Sort(man a, man b) {
	return (a.first_name < b.first_name);
}

std::string generate_name(size_t i) {
	std::stringstream ss;
	ss << i << ".txt";
	return ss.str();
}

void merge(size_t number_of_files_, std::string result_name) {
	size_t number = number_of_files_;
	std::ofstream result(result_name);
	std::vector<std::ifstream*> files;
	std::vector<man> people;
	files.reserve(number);
	people.reserve(number);
	man temp_m;
	std::ifstream* temp_i;
	for (size_t i = 0; i < number; ++i) {
		temp_i = new std::ifstream(generate_name(i));
		files.push_back(temp_i);
		*(files[i]) >> temp_m.last_name >> temp_m.first_name >> temp_m.year;
		people.push_back(temp_m);
	}
	while (number >= 1) {
		size_t min_index = 0;
		for (size_t i = 1; i < number; ++i) {
			if (people[i] < people[min_index]) {
				min_index = i;
			}
		}
		result << people[min_index].last_name << " " << people[min_index].first_name << " " << people[min_index].year << std::endl;
		(*files[min_index]) >> people[min_index].last_name >> people[min_index].first_name >> people[min_index].year;
		if (!(*files[min_index])) {
			(*files[min_index]).close();
			files.erase(files.begin() + min_index);
			people.erase(people.begin() + min_index);
			--number;
		}
	}
	files.clear();
	people.clear();
	result.close();
	for (size_t i = 0; i < number_of_files_; ++i) {
		std::remove(generate_name(i).c_str());
	}
}

void ext_sort(std::string && file_name, std::string && result_file_name, size_t && size_of_block) {
	std::ifstream fin(file_name);
	if (!fin.is_open()) return;
	size_t number_of_files = 0, size_of_block_ = size_of_block * 1024 * 1024;
	size_t memory = size_of_block_ / 105;
	std::vector<man> people;
	people.reserve(memory);
	man temp;
	while (!fin.eof()) {
		std::ofstream fout(generate_name(number_of_files));
		for (size_t i = 0; i < memory; ++i){
			if (fin.eof()) break;
			fin >> temp.last_name >> temp.first_name >> temp.year;
			people.push_back(temp);
		} //while ((sizeof(std::vector<man>) + sizeof(man) * (people.size()+1)) < size_of_block_);
		sort(people.begin(), people.end(), Sort);
		for (size_t j = 0; j < people.size(); ++j)
			fout << people[j].last_name << " " << people[j].first_name << " " << people[j].year << std::endl;
		++number_of_files;
		people.clear();
		fout.close();
	}
	fin.close();
	merge(number_of_files, result_file_name);
}

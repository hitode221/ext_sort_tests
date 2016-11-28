#pragma once
#include <queue>
#include <fstream>
#include <vector>
#include <string>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#include <sstream>

struct man {
	std::string last_name, first_name, file_name;
	size_t year;
	std::ifstream* file;
	bool operator < (const man& b) const
	{
		return (first_name > b.first_name);
	}
};
bool Sort(man a, man b) {
	return (a.first_name < b.first_name);
}

std::string generate_name(size_t i) {
	std::stringstream ss;
	ss << i << ".txt";
	std::string result = ss.str();
	return result;
}
void merge_all_files(size_t number_of_files, std::string result_name) {
	std::ofstream result(result_name);
	std::priority_queue<man> people;
	man temp;
	int u = 0;
	for (size_t i = 0; i < number_of_files; ++i) {
		temp.file = new std::ifstream(generate_name(i));
		temp.file_name = generate_name(i);
		*temp.file >> temp.last_name >> temp.first_name >> temp.year;
		people.push(temp);
	}
	man temp1;
	while (!people.empty()) {
		temp1 = people.top();
		people.pop();
		result << temp1.last_name << " " << temp1.first_name << " " << temp1.year << std::endl;
		if (*temp1.file) {
			(*temp1.file) >> temp1.last_name >> temp1.first_name >> temp1.year;
			if (*temp1.file) {
				people.push(temp1);
			}
			else {
				(*temp1.file).close();
				remove(temp1.file_name.c_str());
			}
		}
	}
}

void merge_files(std::string first_name, std::string second_name, std::string result_file) {
	std::fstream first(first_name), second(second_name);
	std::ofstream result(result_file);
	man temp1, temp2;
	if (!first.eof()) first >> temp1.last_name >> temp1.first_name >> temp1.year;
	if (!second.eof()) second >> temp2.last_name >> temp2.first_name >> temp2.year;
	while (!first.eof() && !second.eof()) {
		if (Sort(temp1, temp2)) {
			result << temp1.last_name << " " << temp1.first_name << " " << temp1.year << std::endl;
			first >> temp1.last_name >> temp1.first_name >> temp1.year;
		}
		else {
			result << temp2.last_name << " " << temp2.first_name << " " << temp2.year << std::endl;
			second >> temp2.last_name >> temp2.first_name >> temp2.year;
		}
	}
	while (!first.eof()) {
		result << temp1.last_name << " " << temp1.first_name << " " << temp1.year << std::endl;
		first >> temp1.last_name >> temp1.first_name >> temp1.year;
	}
	while (!second.eof()) {
		result << temp2.last_name << " " << temp2.first_name << " " << temp2.year << std::endl;
		second >> temp2.last_name >> temp2.first_name >> temp2.year;
	}
	second.close();
	first.close();
	remove(first_name.c_str());
	remove(second_name.c_str());
}

void ext_sort(std::string file_name, std::string result_file_name, size_t size_of_block) {
	std::fstream fin(file_name);
	if (!fin.is_open()) return;
	size_t i = 0, size = 0, size_of_block_ = size_of_block  * 1024 * 1024;
	std::vector<man> people;
	size_t memory_ = size_of_block_/102;
	people.reserve(memory_);
	man temp;
	while (!fin.eof()) {
		size = 0;
		std::ofstream fout(generate_name(i));
		for(int k = 0; k < memory_; k++) {
			if (fin.eof()) break;
			if (k >= people.size()) break;
			fin >> temp.last_name >> temp.first_name >> temp.year;
			people.insert(people.end(), temp);
			size += sizeof(temp);
		} 
		sort(people.begin(), people.end(), Sort);
		for (size_t j = 0; j < people.size(); j++)
			fout << people[j].last_name << " " << people[j].first_name << " " << people[j].year << std::endl;
		i++;
		people.clear();
		fout.close();
	}
	fin.close();
	merge_all_files(i, result_file_name);	
}

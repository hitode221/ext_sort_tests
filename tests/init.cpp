#include "ext_sort.h"
#include <catch.hpp>
#include <iostream>
#include <fstream>

SCENARIO("sort", "[sort]") {
	ext_sort("random.txt", 256);
}
#pragma once
#include <vector>
bool StringContainsText(const std::string & haystack, const std::string& needle);

std::vector<int> SearchFileForText(const std::string &filename, const std::string &needle);

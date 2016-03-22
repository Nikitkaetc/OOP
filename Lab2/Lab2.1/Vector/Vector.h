#pragma once
#include <boost/phoenix.hpp>
#include <boost/range/algorithm/transform.hpp>
#include <vector>

std::vector<double> FillVector();

void PrintVector(const std::vector<double> &Vector);

std::vector<double> VectorTransform(std::vector<double> const& Vector);
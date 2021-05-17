#pragma once

#include <iostream>
#include <vector> 
using namespace std;

struct Input {
    vector<double> numbers;
    size_t bin_count;

};

vector<double> input_numbers(istream& in, size_t count);
Input read_input(istream& in, bool prompt);
void find_minmax(const vector<double>& numbers, double& max, double& min);
vector<size_t> make_histogram(Input data);
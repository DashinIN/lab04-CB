
#include "histogram.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;



vector<double> input_numbers(istream& in, size_t count) {
    vector<double> result(count);
    for (size_t i = 0; i < count; i++) {
        in >> result[i];
    }
    return result;
}


Input read_input(istream& in, bool prompt) {
    Input data;

    if (prompt) cerr << "Enter number count: ";
    size_t number_count;
    in >> number_count;

    if (prompt) cerr << "Enter numbers: ";
    data.numbers = input_numbers(in, number_count);

    if (prompt) cerr << "Enter bin count: ";
    in >> data.bin_count;

    return data;
}

void find_minmax(const vector<double>& numbers, double& min, double& max) {
    if (numbers.size() == 0) return;
    min = numbers[0];
    max = numbers[0];
    for (double x : numbers) {
        if (x < min) {
            min = x;
        }
         if (x > max) {
            max = x;
        }
    }
}


 vector<size_t> make_histogram(Input data) {
     const auto bin_count = data.bin_count;
     const auto numbers = data.numbers;
     double min, max;
     size_t number_count = numbers.size();
     find_minmax(numbers, min, max);
     vector<size_t> bins(bin_count);
     double bin_size = (max - min) / bin_count;
        for (size_t i = 0; i < number_count; i++) {
            bool found = false;
            for (size_t j = 0; (j < bin_count - 1) && !found; j++) {
                auto lo = min + j * bin_size;
                auto hi = min + (j + 1) * bin_size;
                if ((lo <= numbers[i]) && (numbers[i] < hi)) {
                    bins[j]++;
                    found = true;
                }
            }
            if (!found) {
                bins[bin_count - 1]++;
            }
        }
        return bins;
    }


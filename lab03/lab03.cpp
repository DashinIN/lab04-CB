#include <iostream>
#include <vector> 
#include "svg.h"
#include "histogram.h"


using namespace std;


int main() {
   
   const auto input = read_input(cin, true);
   const auto bins = make_histogram(input);
   show_histogram_svg(bins);

    return 0;

}


#include "svg.h"
#include <vector> 
#include <string> 

using namespace std;

int font_size(istream& in) {

    int size;

    cerr << "Enter font size from 8 to 36:\n";
    in >> size;

    bool wrong = true;
    while (wrong) {
        if (size >= 8 && size <= 36) {
            wrong = false;
        }
        else {
            if (size < 8) {
                cerr << "Enter again, size is too low\n";
                in >> size;
            }
            if (size > 36) {
                cerr << "Enter again, size is too big\n";
                in >> size;
            }
        }
    }
    return size;
}


void svg_begin(double width, double height) {
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}

void
svg_end() {
    cout << "</svg>\n";
}



void svg_text(double left, double baseline, string text, int size) {
    cout << "<text x = '" << left << "' y = '" << baseline << "' font-size = '" << size << "' >" << text << "</text>";
}

void svg_rect(double x, double y, double width, double height, string stroke, string fill) {
    cout << "<rect x= '" << x << "' y= '" << y << "' width= '" << width << "' height= '" << height << "' stroke= '" << stroke << "' fill= '" << fill << "' />";
}



void   show_histogram_svg(const vector<size_t>& bins) {
    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;
    const size_t MAX_ASTERISK = IMAGE_WIDTH - TEXT_WIDTH;
    const int size = font_size(cin);

    size_t max_count = bins[0];
    for (size_t bin : bins) {
        if (bin > max_count) {
            max_count = bin;
        }
    }

    const bool scaling_needed = max_count * BLOCK_WIDTH > MAX_ASTERISK;

    double scaling_factor;
    if (scaling_needed)
    {
        scaling_factor = static_cast<double>(MAX_ASTERISK) / (max_count * BLOCK_WIDTH);
    }
    else {
        scaling_factor = 1;
    }

    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);

    double top = 50;

    for (size_t bin : bins) {
        const double bin_width = BLOCK_WIDTH * bin * scaling_factor;
        svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin), size);
        svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT, "black", "#c72af7");
        top += BIN_HEIGHT;
    }
    svg_end();
}




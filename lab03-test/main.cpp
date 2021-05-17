
#include <cassert>
#include <sstream>
#include <iostream>
#include "C:\Users\igree\Desktop\lab04 CB\lab03\svg.h"
#include "C:\Users\igree\Desktop\lab04 CB\lab03\histogram.h"

using namespace std;

void test_positive() {
    double min = 0;
    double max = 0;
    find_minmax({ 1, 2, 3 }, max, min);
    assert(min == 1);
    assert(max == 3);
}
void test_negative() {
    double min = 0;
    double max = 0;
    find_minmax({ -1, -2, -3 }, max, min);
    assert(min == -3);
    assert(max == -1);
}
void test_constant() {
    double min = 0;
    double max = 0;
    find_minmax({ 99,99,99 }, max, min);
    assert(min == 99);
    assert(max == 99);
}
void test_onenumber() {
    double min = 0;
    double max = 0;
    find_minmax({ 1 }, max, min);
    assert(min == 1);
    assert(max == 1);
}
void test_empty() {
    double min = 0;
    double max = 0;
    find_minmax({}, max, min);
    assert(min == 0);
    assert(max == 0);
}

void test_big() {
    stringstream in("50 10");
    assert(font_size(in) == 10);
}

void test_low() {
    stringstream in("4 14");
    assert(font_size(in) == 14);
}

void test_lot() {
    stringstream in("1 1 1 1 1 14");
    assert(font_size(in) == 14);
}
void test_loth() {
    stringstream in("99 99 99 99 25");
    assert(font_size(in) == 25);
}

void test_8() {
    stringstream in("8");
    assert(font_size(in) == 8);

}
void test_36() {
    stringstream in("36");
    assert(font_size(in) == 36);
}

int main() {

    // Тесты для функции find_minmax
    test_positive();
    test_negative();
    test_constant();
    test_onenumber();
    test_empty();

    // Тесты для функции font_size
    test_big();
    test_low();
    test_lot();
    test_loth();
    test_8();
    test_36();

    return 0;
}

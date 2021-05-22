﻿#include <iostream>
#include <vector>
#include "svg.h"
#include "histogram.h"
#include <curl/curl.h>
#include <sstream>
#include <string>

using namespace std;

size_t write_data(void* items, size_t item_size, size_t item_count, void* ctx) {

     auto data_size = item_size * item_count;
     stringstream* buffer = reinterpret_cast<stringstream*>(ctx);
     buffer->write(reinterpret_cast<char*>(items), data_size);
      return data_size;

}


Input download(const string& address) {

      curl_global_init(CURL_GLOBAL_ALL);

    stringstream buffer;
    char *ip;

  CURL *curl = curl_easy_init();

if(curl) {
  CURLcode res;
   curl_easy_setopt(curl, CURLOPT_URL,  address.c_str());
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
  res = curl_easy_perform(curl);
   if (res != CURLE_OK) {
                cout << address<<endl;
                cout << curl_easy_strerror(res);
                exit(1);
               }
        if((res == CURLE_OK) && !curl_easy_getinfo(curl, CURLINFO_PRIMARY_IP, &ip) && ip) {
    cerr << "IP: %s\n" <<  ip ;
  }
  curl_easy_cleanup(curl);
}

    return read_input(buffer, false);
}

string
make_info_text() {
    stringstream buffer;
  const char* name = "Mass effect remastered";
int year = 2021;
printf("%s wishel v  %d.\n", name, year);
// Commander Shepard was born in 2154.
printf("n = %08x\n", 0x1234567); // 01234567
    return buffer.str();
}




int main(int argc, char* argv[]) {

    make_info_text();
    return 0;

    Input input;
    if (argc > 1) {
        input = download(argv[1]);
    } else {
        input = read_input(cin, true);
    }

   const auto bins = make_histogram(input);
   show_histogram_svg(bins);

    return 0;

}


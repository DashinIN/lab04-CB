#include <iostream>
#include <vector>
#include "svg.h"
#include "histogram.h"
#include <curl/curl.h>
#include <sstream>
#include <string>
#include <windows.h>



using namespace std;

size_t write_data(void* items, size_t item_size, size_t item_count, void* ctx) {

     auto data_size = item_size * item_count;
     stringstream* buffer = reinterpret_cast<stringstream*>(ctx);
     buffer->write(reinterpret_cast<char*>(items), data_size);
      return data_size;

}


Input download(const string& address) {

stringstream buffer;
    char *ip;

curl_global_init(CURL_GLOBAL_ALL);
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

string make_info_text() {
    stringstream buffer;
  DWORD WINAPI info = GetVersion();

  DWORD mask = 0x0000ffff;
  DWORD platform = info >> 16;
  DWORD version = info & mask;

DWORD mask2 = 0x00ff;
DWORD version_major = version >> 8;
DWORD version_minor = version & mask2;

DWORD build;
if ((info & 0x10000000) == 0) {
    build = platform;
  }

 printf("Windows v%u.%u (build %u)\n", version_minor, version_major, build );

char
length[MAX_COMPUTERNAME_LENGTH+1];
	DWORD size;
	size=sizeof(length);
	GetComputerName(length,&size);

	printf("Computer name: %s\n", length);



    return buffer.str();
}




int main(int argc, char* argv[]) {

   make_info_text();

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


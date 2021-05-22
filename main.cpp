#include <iostream>
#include <vector>
#include <string>
#include<sstream>
#include <windows.h>

#include "histogram.h"
#include "svg.h"
using namespace std;


vector<double>
input_numbers(size_t count) {
    vector<double> result(count);
    for (size_t i = 0; i < count; i++) {
        cin >> result[i];
    }
    return result;
}

string
make_info_text() {
    stringstream buffer;
    DWORD info=GetVersion();
    DWORD mask = 0b00000000'00000000'11111111'11111111;
    DWORD version = info & mask;
    DWORD version_M = version& 0x00ff;
    DWORD version_m =(version& 0x0000ffff)>>8;
    DWORD platform = info >> 16;
    DWORD build;
    if ((info & 0x8000) == 0)
        build = platform;
    DWORD DL= MAX_COMPUTERNAME_LENGTH+1;
    char ComputerName[DL];
    GetComputerNameA(ComputerName,&DL);
    buffer<< "Windows v"<< version_M<<"."<< version_m<<" (build "<< build<<")"
    <<"\nComputer name "<<ComputerName;
    return buffer.str();
}

int main() {
    make_info_text();
    /*
    size_t number_count;
    cin >> number_count;
    const auto numbers = input_numbers(number_count);
    size_t bin_count;
    cin >> bin_count;

    const auto bins = make_histogram(numbers, bin_count);
    //show_histogram_text(bins);
    show_histogram_svg(bins);
    */
    return 0;
}

#include<iostream>
#include<vector>
#include<sstream>
#include <windows.h>
using namespace std;

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

void
svg_begin(double width, double height) {
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

void
svg_text(double left, double baseline, string text) {
    cout << "<text x='" << left << "' y='" << baseline << "'>" << text << "</text>";
}

void
svg_textInfo(double left, double baseline) {
    string text=make_info_text();
    cout << "<text x='" << left << "' y='" << baseline << "'>" << text << "</text>";
}

void svg_rect(double x, double y, double width, double height,
    string stroke="black", string fill="yellow") {
    cout << "<rect x='" << x << "' y='" << y << "' width='" << width << "' height='" << height << "' stroke='" << stroke << "' fill='" << fill << "'/>";
}

void
show_histogram_svg(const vector<size_t> &bins) {
    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;
    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);

    size_t max_bin = bins[0];
    for (size_t j : bins)
    {
        if (max_bin < j)
            max_bin = j;
    }

    double top = 0;
    const double max_bin_width = BLOCK_WIDTH * max_bin;
    for (size_t bin : bins) {
             svg_text(TEXT_LEFT, top+TEXT_BASELINE, to_string(bin));
         if(bin==max_bin){
                svg_rect(TEXT_WIDTH, top,IMAGE_WIDTH, BIN_HEIGHT);
        }
             else{
                const double bin_width = BLOCK_WIDTH * bin;
                const double IMAGE_WIDTH_bin=IMAGE_WIDTH*(bin_width/max_bin_width);
                svg_rect(TEXT_WIDTH, top, IMAGE_WIDTH_bin, BIN_HEIGHT,"black","pink");
             }
        top += BIN_HEIGHT;
    }
    svg_textInfo(TEXT_LEFT, top+TEXT_BASELINE);
    svg_end();

}


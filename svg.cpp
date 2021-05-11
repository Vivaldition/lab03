#include<iostream>
#include<vector>
using namespace std;
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

void svg_rect(double x, double y, double width, double height,
    string stroke="black", string fill="red") {
    cout << "<rect x='" << x << "' y='" << y << "' width='" << width << "' height='" << height << "' stroke='" << stroke << "' fill='" << fill << "'/>";
}

void
show_histogram_svg(const vector<size_t>& bins, size_t number_count) {
    const auto IMAGE_WIDTH = 500;
    const auto IMAGE_WIDTH_H = 400;
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
        size_t percent=(bin*100)/number_count;
         if(bin==max_bin){
                svg_text(TEXT_LEFT, top+TEXT_BASELINE, to_string(max_bin));
                svg_rect(TEXT_WIDTH, top,IMAGE_WIDTH_H, BIN_HEIGHT);
                svg_text(TEXT_LEFT+BIN_HEIGHT+IMAGE_WIDTH_H,top+TEXT_BASELINE, to_string(percent)+'%');
        }
             else{

                const double bin_width = BLOCK_WIDTH * bin;
                const double IMAGE_WIDTH_bin=IMAGE_WIDTH_H*(bin_width/max_bin_width);
                svg_text(TEXT_LEFT, top+TEXT_BASELINE, to_string(bin));
                svg_rect(TEXT_WIDTH, top, IMAGE_WIDTH_bin, BIN_HEIGHT,"black","green");
                svg_text(TEXT_LEFT+BIN_HEIGHT+IMAGE_WIDTH_bin,top+TEXT_BASELINE, to_string(percent)+'%');
             }
        top += BIN_HEIGHT;
    }
    svg_end();

}


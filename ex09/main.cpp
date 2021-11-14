#include <iostream>
#include <cmath>
#include <string>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;
using namespace cv;

void uniform_midrise(Mat& input,Mat& output,int bpp){
    uchar mask= ~uchar(pow(2, sizeof(uchar)*8-bpp) -1);
    bitwise_and(input, mask, output);
}

void uniform_midtread(Mat& input,Mat& output,int bpp){
    uchar half = uchar(pow(2, sizeof(uchar)*8-bpp)/2);
    add(input, half, output);
    uniform_midrise(output, output, bpp);
}

int main(int argc, char* argv[]) {

    if(argc != 3) {
        cout << "Usage: " << argv[0] << " <input_file> <bits_per_pixel>" << endl;
        return -1;
    }

    Mat input = imread(argv[1]);

    if(!input.data) {
        cout << "No image data" << endl;
        return -2;
    }

    int numRows = input.rows;
    int numCols = input.cols;
    int type = input.type();

    Mat output_midrise = Mat(numRows, numCols, type);
    Mat output_midtread = Mat(numRows, numCols, type);

    int bpp = atoi(argv[2]);

    uniform_midrise(input, output_midrise, bpp);
    uniform_midtread(input, output_midtread, bpp);

    imshow("Original", input);
    imshow("Midrise Quantized", output_midrise);
    imshow("Midtread Quantized", output_midtread);

    string str_file = argv[1];
    size_t pos = str_file.find(".");
    string substr_file = str_file.substr(0, pos);
    string extension = str_file.substr(pos);

    string output_file_midrise = substr_file + "_midrise" + extension;
    string output_file_midtread = substr_file + "_midtread" + extension;
    
    imwrite(output_file_midrise, output_midrise);
    imwrite(output_file_midtread, output_midtread);

    cout << "output files:" << endl << output_file_midrise << endl << output_file_midtread;

    waitKey(0);

    return 0;
}
#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv ) {

    if(argc != 3){
        cout << "Usage: " << argv[0] << " <input_file> <output_file>" << endl;
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

    Mat output = Mat(numRows, numCols, type);

    for(int r=0; r<numRows; r++) {
        for(int c=0; c<numCols; c++) {
            output.at<Vec3b>(r,c) = input.at<Vec3b>(r,c);
        }
    }
    imwrite(argv[2], output);
    
    imshow("Output Image", output);
    waitKey(0);
    
    return 0;
}
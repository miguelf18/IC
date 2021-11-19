#include <iostream>
#include <cmath>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>

using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{

    if (argc != 3)
    {
        cout << "Usage: " << argv[0] << " <image_file1> <image_file2>" << endl;
        return -1;
    }
    //The function imread loads an image from the specified file and returns it.
    Mat image_file = imread(argv[1], IMREAD_COLOR); //IMREAD_COLOR->If set, always convert image to the 3 channel BGR color image.
    if (image_file.data == NULL)
    {
        cout << "No image data" << endl;
        return -2;
    }
    //The function imread loads an image from the specified file and returns it.
    Mat image_file2 = imread(argv[2], IMREAD_COLOR); //IMREAD_COLOR->If set, always convert image to the 3 channel BGR color image.
    if (image_file2.data == NULL)
    {
        cout << "No image data" << endl;
        return -3;
    }

    int numRows = image_file.rows;
    int numCols = image_file.cols;
    double sum_MSE=0;
    double MSE; //Mean Squad Error MSE= 1/(c*i*j) ∑ (I1-I2)^2  
                //Let there be two images: I1 and I2; with a two dimensional size i and j,composed of c number of channels.
    
    int numCanais=3;
    for (int nc = 0; nc < numCanais; nc++)
    {
        for (int r = 0; r < numRows; r++)
        {
            for (int c = 0; c < numCols; c++)
            {
                sum_MSE += pow(image_file.at<Vec3b>(r, c)[nc] - image_file2.at<Vec3b>(r, c)[nc],2);
            }
        }
    }

    MSE=sum_MSE/(numCanais*numRows*numCols);

    double PSNR; //Peak signal-to-noise ratio PSNR= 10*logbase10(MaxI^2/MSE);
    // MAX_I is the maximum valid value for a pixel. In case of the simple single byte image per pixel per channel this is 255
    double MAX_I=255;
    PSNR= 10*log10(pow(MAX_I,2)/MSE);

    cout << "O Peak signal-to-noise ratio de uma certa imagem em relacao ao ficheiro original sao: " << PSNR << " dB";

    return 0;
}


#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <math.h>
#include <iomanip>

using namespace std;

// display histogram for grayscale image
void show_grayscale_histogram(map<int, int> *gray_map)
{
    ofstream output_stream("gray_channel.out");
    for(auto color_value : (*gray_map))
    {
        output_stream << color_value.first << ": ";
        output_stream << color_value.second << endl;
    }
    output_stream.close();
    cout << "Grayscale: " << "gray_channel.out" << endl;
}

// display histogram for each rgb channel
void show_rgb_histogram(map<int, int> *red_map, map<int, int> *green_map, map<int, int> *blue_map, map<string, int> *pixel_map)
{
    ofstream output_stream("red_channel.out");
    for(auto color_value : (*red_map))
    {
        output_stream << color_value.first << ": ";
        output_stream << color_value.second << endl;
    }
    output_stream.close();
    output_stream.open("green_channel.out");
    for(auto color_value : (*green_map))
    {
        output_stream << color_value.first << ": ";
        output_stream << color_value.second << endl;
    }
    output_stream.close();
    output_stream.open("blue_channel.out");
    for(auto color_value : (*blue_map))
    {
        output_stream << color_value.first << ": ";
        output_stream << color_value.second << endl;
    }
    output_stream.close();
    output_stream.open("pixel_channel.out");
    for(auto color_value : (*pixel_map))
    {
        output_stream << color_value.first << ": ";
        output_stream << color_value.second << endl;
    }
    output_stream.close();
    cout << "Red channel: " << "red_channel.out" << endl;
    cout << "Green channel: " << "green_channel.out" << endl;
    cout << "Blue channel: " << "blue_channel.out" << endl;
}

// get total entropy for image
void compute_entropy(map<string, int> *map, int *total_pixels, double *entropy)
{
    for(auto item : (*map))
    {
        int item_value = item.second;
        double probability = static_cast<double>(item_value) / (*total_pixels);
        (*entropy) -= probability * log2(probability);
    }
}

// get total entropy for a image channel
void compute_entropy(map<int, int> *map, int *total_pixels, double *entropy)
{
    for(auto item : (*map))
    {
        int item_value = item.second;
        double probability = static_cast<double>(item_value) / (*total_pixels);
        (*entropy) -= probability * log2(probability);
    }
}

// read .ppm image file and convert to grayscale
void read_grayscale_file(string *file_name, map<int, int> *gray_map, int *count)
{
    // open in binary mode
    ifstream input_stream(*file_name);
    if(input_stream.fail())
    {
        cerr << "Can't read file!" << endl;
        input_stream.close();
        exit(1); 
    }
    // read .ppm file header information
    string version, width_string, height_string, max_pixel_value;
    input_stream >> version;
    input_stream >> width_string;
    input_stream >> height_string;
    input_stream >> max_pixel_value;
    if(version != "P6")
    {
        cerr << "Wrong format file. Must be a P6 .ppm image!" << endl;
        input_stream.close();
        exit(1); 
    }
    // read .ppm file pixel data
    int width = stoi(width_string);
    int height = stoi(height_string);
    // luma coding values
    const float RED_COMPONENT = 0.299f;
    const float GREEN_COMPONENT = 0.587f;
    const float BLUE_COMPONENT = 0.114f;
    unsigned char color_character;
    for(int i = 0; i < height; i++)
    {
        for(int k = 0; k < width; k++)
        {
            input_stream >> color_character;
            int gray_red = (int) color_character * RED_COMPONENT;
            input_stream >> color_character;
            int gray_green = (int) color_character * GREEN_COMPONENT;
            input_stream >> color_character;
            int gray_blue = (int) color_character * BLUE_COMPONENT;
            int grayscale = gray_red + gray_green + gray_blue;
            (*gray_map)[grayscale]++;
        }
    }
    input_stream.close();
    (*count) = width * height;
}

// read rgb values from .ppm image file
void read_file(string *file_name, map<int, int> *red_map, map<int, int> *green_map, map<int, int> *blue_map, map<string, int> *pixel_map, int *count)
{
    // open in binary mode
    ifstream input_stream(*file_name);
    if(input_stream.fail())
    {
        cerr << "Can't read file!" << endl;
        input_stream.close();
        exit(1); 
    }
    // read .ppm file header information
    string version, width_string, height_string, max_pixel_value;
    input_stream >> version;
    input_stream >> width_string;
    input_stream >> height_string;
    input_stream >> max_pixel_value;
    if(version != "P6")
    {
        cerr << "Wrong format file. Must be a P6 .ppm image!" << endl;
        input_stream.close();
        exit(1); 
    }
    // read .ppm file pixel data
    int width = stoi(width_string);
    int height = stoi(height_string);
    for(int i = 0; i < height; i++)
    {
        for(int k = 0; k < width; k++)
        {
            unsigned char color_character;
            // red channel
            input_stream >> color_character;
            (*red_map)[(int)color_character]++;
            string pixel_red = to_string((int)color_character);
            // green channel
            input_stream >> color_character;
            (*green_map)[(int)color_character]++;
            string pixel_green = to_string((int)color_character);
            // blue channel
            input_stream >> color_character;
            (*blue_map)[(int)color_character]++;
            string pixel_blue = to_string((int)color_character);
            string pixel_data = "(" + pixel_red + "," + pixel_green + "," + pixel_blue + ")";
            (*pixel_map)[pixel_data]++;
        }
    }
    input_stream.close();
    (*count) = width * height * 3;
}

int main(int argc, char **argv)
{
    
    // test input parameters
    if(argc != 2)
    {
        cerr << "NOPE! Usage: ./mainRun <input_file>.ppm" << endl;
        exit(1);
    }

    string file_input = argv[1];

    // rgb channels
    map<int, int> red_frequency_map;
    map<int, int> green_frequency_map;
    map<int, int> blue_frequency_map;
    map<string, int> pixel_frequency_map;
    int pixel_count = 0;

    read_file(&file_input, &red_frequency_map, &green_frequency_map, &blue_frequency_map, &pixel_frequency_map, &pixel_count);

    // entropy for each channel
    double red_entropy = 0;
    double green_entropy = 0;
    double blue_entropy = 0;
    double pixel_entropy = 0;

    compute_entropy(&red_frequency_map, &pixel_count, &red_entropy);
    compute_entropy(&green_frequency_map, &pixel_count, &green_entropy);
    compute_entropy(&blue_frequency_map, &pixel_count, &blue_entropy);
    compute_entropy(&pixel_frequency_map, &pixel_count, &pixel_entropy);

    cout << "=====RGB Image=====" << endl;

    cout << "Red channel entropy: " << red_entropy << endl;
    cout << "Green channel entropy: " << green_entropy << endl;
    cout << "Blue channel entropy: " << blue_entropy << endl;
    cout << "Total entropy: " << pixel_entropy << endl;

    cout << endl;

    show_rgb_histogram(&red_frequency_map, &green_frequency_map, &blue_frequency_map, &pixel_frequency_map);

    // grayscale
    map<int, int> grayscale_frequency_map;
    double gray_entropy = 0;
    read_grayscale_file(&file_input, &grayscale_frequency_map, &pixel_count);

    cout << endl << "=====Grayscale Image=====" << endl;

    compute_entropy(&grayscale_frequency_map, &pixel_count, &gray_entropy);

    cout << "Grayscale entropy: " << gray_entropy << endl;

    show_grayscale_histogram(&grayscale_frequency_map);

    return 0;
}



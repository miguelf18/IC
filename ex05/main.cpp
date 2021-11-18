#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <math.h>
#include <iomanip>

using namespace std;

// display histogram
void show_histogram(map<char, int> *map)
{
    ofstream output_stream("letter_frequency.out");
    for(auto item : (*map))
    {
        cout << item.first << ": ";
        cout << item.second << endl;
        output_stream << item.first << ": ";
        output_stream << item.second << endl;
    }
    output_stream.close();
    cout << "Data: " << "letter_frequency.out" << endl;
}

// get total entropy
void compute_entropy(map<char, int> *map, int *total_characters, double *entropy)
{
    for(auto item : (*map))
    {
        int item_value = item.second;
        double probability = static_cast<double>(item_value) / (*total_characters);
        (*entropy) -= probability * log2(probability);
    }
}

// get character frequency
void read_file(string *file_name, map<char, int> *map, int *count)
{
    ifstream input_stream(*file_name);
    // test file
    if(input_stream.fail())
    {
        cerr << "Can't read file!" << endl;
        exit(1); 
    }
    string line;
    while(getline(input_stream, line))
    {
        for(char character : line)
        {
            // assume only letters
            if(isalpha(character))
            {
                if(islower(character))
                character = toupper(character);
                (*map)[character]++;
                (*count)++;
            }
        }
    }
}

int main(int argc, char **argv)
{
    
    // test input parameters
    if(argc != 2)
    {
        cerr << "NOPE! Usage: ./mainRun <input_file>.txt" << endl;
        exit(1);
    }

    string file_input = argv[1];
    map<char, int> frequency_map;
    int character_count = 0;

    read_file(&file_input, &frequency_map, &character_count);

    double entropy = 0;

    compute_entropy(&frequency_map, &character_count, &entropy);

    cout << endl << endl << "Total entropy: " << entropy << endl << endl;

    show_histogram(&frequency_map);

    return 0;
}



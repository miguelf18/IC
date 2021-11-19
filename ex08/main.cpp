#include "AudioFile.h"

using namespace std;

int main(int argc, char **argv)
{

    if (argc != 3)
    {
        cout << "Usage: " << argv[0] << " <input_file> <output_file>" << endl;
        return -1;
    }

    //cout << "input audio file: " << argv[1] << endl;
    //cout << "output audio file: " << argv[2] << endl;

    AudioFile<double> inputFile;
    inputFile.load(argv[1]);

    int numChannels = inputFile.getNumChannels();
    int numSamples = inputFile.getNumSamplesPerChannel();

    AudioFile<double> outputFile;
    outputFile.setNumChannels(numChannels);
    outputFile.setNumSamplesPerChannel(numSamples);
    
    int nbits = 1;

    for (int i = 0; i < numChannels; i++)
    {
        for (int j = 0; j < numSamples; j++)
        {
            int currentSample = inputFile.samples[i][j];
            outputFile.samples[i][j] = (currentSample >> nbits) << nbits;
        }
    }
    outputFile.save(argv[2]);

    return 0;
}
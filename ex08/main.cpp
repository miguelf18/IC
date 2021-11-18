#include "AudioFile.h"

using namespace std;

int main(int argc, char **argv)
{

    if (argc != 3)
    {
        cout << "Usage: " << argv[0] << " <input_file> <output_file>" << endl;
        return -1;
    }

    cout << "input audio file: " << argv[1] << endl;
    cout << "output audio file: " << argv[2] << endl;

    AudioFile<double> inputFile;
    inputFile.load(argv[1]);
    // inputFile.printSummary();

    int numChannels = inputFile.getNumChannels();
    int numSamples = inputFile.getNumSamplesPerChannel();
    int bitDepth_input = inputFile.getBitDepth();

    //cout << "Input bitDepth: " << bitDepth_input << endl;

    AudioFile<double> outputFile;
    outputFile.setNumChannels(numChannels);
    outputFile.setNumSamplesPerChannel(numSamples);
    outputFile.setBitDepth(8);

    // outputFile.printSummary();

    int bitDepth_output = outputFile.getBitDepth();
    //cout << "Output bitDepth: " << bitDepth_output << endl;
    
    for (int i = 0; i < numChannels; i++)
    {
        for (int j = 0; j < numSamples; j++)
        {
            double currentSample = inputFile.samples[i][j];
            outputFile.samples[i][j] = currentSample;
        }
    }
    //inputFile.printSummary();
    //outputFile.printSummary();
    outputFile.save(argv[2]);
}

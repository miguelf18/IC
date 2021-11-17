#include "AudioFile.h"

using namespace std;

int main(int argc, char** argv) {

    if(argc != 3){
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

    AudioFile<double> outputFile;
    outputFile.setNumChannels(numChannels);
    outputFile.setNumSamplesPerChannel(numSamples);
    // outputFile.printSummary();

    for(int i=0; i<numChannels; i++) {
        for (int j=0; j<numSamples; j++) {
            double currentSample = inputFile.samples[i][j];
            outputFile.samples[i][j] = currentSample;
        }
    }

    outputFile.save(argv[2]);
}
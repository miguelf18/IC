#include "AudioFile.h"

using namespace std;

int main(int argc, char** argv) {

    if(argc != 3){
        cout << "Usage: " << argv[0] << " <input_file> <output_file>" << endl;
        return -1;
    }

    cout << "input file: " << argv[1] << endl;
    cout << "output file: " << argv[2] << endl;

    AudioFile<double> audioFile;
    audioFile.load (argv[1]);
    // audioFile.printSummary();

    AudioFile<double> outputFile;
    outputFile.setNumChannels (audioFile.getNumChannels());
    outputFile.setNumSamplesPerChannel (audioFile.getNumSamplesPerChannel());
    // outputFile.printSummary();  

    int channel = 0;
    int numSamples = audioFile.getNumSamplesPerChannel();
    for (int i=0; i<numSamples; i++)
    {
        double currentSample = audioFile.samples[channel][i];
        outputFile.samples[channel][i] = currentSample;
    }

    outputFile.save (argv[2]);
}
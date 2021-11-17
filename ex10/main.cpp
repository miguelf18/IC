#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <math.h>
#include "AudioFile.h"

using namespace std;

int main(int argc, char** argv)
{

    if(argc != 3){
        cerr << "Usage: " << argv[0] << " <original_file> <modified_file>" << endl;
        exit(1);
    }

    // load original audio file info
    AudioFile<double> input_original(argv[1]);
    int original_channels = input_original.getNumChannels();
    int original_samples_per_channel = input_original.getNumSamplesPerChannel();

    // load modified audio file info
    AudioFile<double> input_modified(argv[2]);
    int modified_channels = input_modified.getNumChannels();
    int modified_samples_per_channel = input_modified.getNumSamplesPerChannel();

    // assume that files have the same size
    if(modified_channels != original_channels)
    {
        cerr << "Files have different amount of channels: Original > " << original_channels << " Modified > " << modified_channels << endl;
        exit(1);
    }

    if(modified_channels != original_channels)
    {
        cerr << "Files have different amount of samples per channel: Original > " << original_samples_per_channel << " Modified > " << modified_samples_per_channel << endl;
        exit(1);
    }


    // compute mean squared error between original and modified files
    double sample_error_sum = 0;
    double max_signal_value = 0;
    double max_error = 0;
    for(int i = 0; i < original_channels; i++)
    {
        for(int k = 0; k < original_samples_per_channel; k++)
        {
            double original_sample = input_original.samples[i][k];
            double modified_sample = input_modified.samples[i][k];
            double current_error = pow(original_sample - modified_sample, 2);
            sample_error_sum += current_error;
            if(abs(original_sample) > max_signal_value)
                max_signal_value = abs(original_sample);
            if(abs(current_error) > max_error)
                max_error = abs(current_error);
        }
    }
    double sample_count = original_channels * original_samples_per_channel;
    double mean_squared_error = sample_error_sum / sample_count;
    
    // compute signal to noise ratio
    double signal_to_noise_ratio = 0;
    if(mean_squared_error > 0)
    {
        signal_to_noise_ratio = 10 * log10(pow(max_signal_value, 2) / mean_squared_error);
    }
    
    cout << "Original file: " << argv[1] << endl;
    cout << "Modified file: " << argv[2] << endl;
    cout << "Maximum signal value: " << max_signal_value << endl;
    cout << "Maximum absolute error: " << max_error << endl;
    cout << "SNR: " << signal_to_noise_ratio << " dB" << endl;

    return 0;
}
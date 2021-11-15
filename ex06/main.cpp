#include <iostream>
#include <stdio.h>
#include <map>
#include "AudioFile.h"


using namespace std;

int main(int argc, char **argv)
{

    if (argc != 2)
    {
        cout << "Usage: " << argv[0] << " <input_file>" << endl;
        return -1;
    }
    //cout << "input file: " << argv[1] << endl;//so para teste
    

    //Create an AudioFile object:
    AudioFile<double> audioFile;
    //Load an audio file
    audioFile.load(argv[1]);

    int numSamples = audioFile.getNumSamplesPerChannel(); //Returns the number of samples per channel
    int numChannels = audioFile.getNumChannels(); //Returns the number of audio channels in the buffer
    int i, j;

    //cout << "numSamples: " << numSamples << endl;//so para teste
    //cout << "numChannels: " << numChannels << endl;//so para teste
    
   std::map<double, int> repetitions;//mapa de occorrencias para o numero de vezes que uma determinada sample aparece
                                   //num determinado canal

  
   for (i = 0; i < numChannels; i++)
   {
       for (j = 0; j < numSamples; j++)
       {
           double currentSample = audioFile.samples[i][j];
           //cout << "sample1a1: " << currentSample << "canal"<< i << endl; //so para teste
           if (repetitions.find(currentSample) == repetitions.end())
               repetitions[currentSample] = 1;
           else
               repetitions[currentSample]++;
       }
    }
    for (auto &it : repetitions)
    {
        cout <<"Sample " << it.first << " aparece " << it.second << " vezes \n";
    }
}
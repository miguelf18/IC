#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char** argv) {

  if(argc != 3){
        cout << "Usage: " << argv[0] << " <input_file> <output_file>" << endl;
        return -1;
    }

  cout << "input text file: " << argv[1] << endl;
  cout << "output text file: " << argv[2] << endl << endl;

  ifstream ifs(argv[1]);
  ofstream ofs(argv[2]);

  string line;

  while(getline(ifs, line)) {
    cout << line << endl;
    ofs << line << endl;
  }

  // só primeira linha:
  //string x;
  //ifs >> x;
  //ofs << x << endl;

  return 0;
}
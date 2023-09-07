#include <bits/stdc++.h>
#include <stringMatching.h>

using namespace std;

class NaiveAlgorithm : public StringMatching {
  bool matchString(int indexToSearch) {
    for (int i = 0; i < lengthOfSearchString; i++) {
      if (dataString[indexToSearch + i] != searchString[i]) return false;
    }
    return true;
  }

 public:
  NaiveAlgorithm(string dataString, string searchString)
      : StringMatching(dataString, searchString) {}

  void findMatches() {
    for (int i = 0; i < lengthOfDataString - lengthOfSearchString + 1; i++) {
      if (matchString(i)) {
        printMessage(i);
        totalMatches++;
      }
    }
    cout << "Total matches are : " << totalMatches << endl;
  }
};

class HorspoolsAlgorithm : public StringMatching {
  map<char, int> shifts;
  void initializeShifts() {
    // to support all ascii characters including spaces
    for (int i = 0; i < 127; i++) {
      shifts[i] = lengthOfSearchString;
    }
    for (int i = 0; i < lengthOfSearchString - 1; i++) {
      shifts[searchString[i]] = lengthOfSearchString - i - 1;
    }
  }
  bool matchString(int indexToSearch) {
    for (int i = lengthOfSearchString - 1; i >= 0; i--) {
      if (searchString[i] != dataString[indexToSearch + i]) return false;
    }
    return true;
  }

 public:
  HorspoolsAlgorithm(string dataString, string searchString)
      : StringMatching(dataString, searchString) {
    initializeShifts();
  }
  void findMatches() {
    for (int i = 0; i < lengthOfDataString - lengthOfSearchString + 1;) {
      if (matchString(i)) {
        printMessage(i);
        totalMatches++;
      }
      i += shifts[dataString[i + lengthOfSearchString - 1]];
    }
    cout << "Total matches are : " << totalMatches << endl;
  }
};
int main() {
  string dataInput, searchInput;
  cout << "Enter Data String : ";
  getline(cin, dataInput);
  cout << "Enter String to Search in Data : ";
  getline(cin, searchInput);

  cout << endl << "By Naive Algorithm : " << endl;
  NaiveAlgorithm naiveAlgorithm(dataInput, searchInput);
  naiveAlgorithm.findMatches();
  cout << endl << "By Horspools Algorithm : " << endl;
  HorspoolsAlgorithm horspoolsAlgorithm(dataInput, searchInput);
  horspoolsAlgorithm.findMatches();

  return 0;
}

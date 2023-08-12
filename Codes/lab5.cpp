#include <bits/stdc++.h>

using namespace std;

class StringMatching {
 protected:
  int lengthOfDataString, lengthOfSearchString, totalMatches;
  string dataString, searchString;
  void printMessage(int indexOfMatching) {
    cout << "Found a match at index: " << indexOfMatching << " : ";
    for (int i = 0; i < lengthOfDataString; i++) {
      if (i == indexOfMatching) cout << "\"";
      cout << dataString[i];
      if (i == indexOfMatching + lengthOfSearchString - 1) cout << "\"";
    }
    cout << endl;
  }

 public:
  StringMatching(string dataString, string searchString) {
    this->dataString = dataString;
    this->searchString = searchString;
    lengthOfDataString = dataString.length();
    lengthOfSearchString = searchString.length();
    totalMatches = 0;
  }
};

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

  void findAllMatches() {
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
  void findAllMatches() {
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

  NaiveAlgorithm naiveAlgorithm(dataInput, searchInput);
  naiveAlgorithm.findAllMatches();

  HorspoolsAlgorithm horspoolsAlgorithm(dataInput, searchInput);
  horspoolsAlgorithm.findAllMatches();

  return 0;
}

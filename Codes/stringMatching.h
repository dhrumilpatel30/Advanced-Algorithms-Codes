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
  virtual void findMatches() = 0;
};
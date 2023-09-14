#include <../stringMatching.h>
#include <bits/stdc++.h>

using namespace std;

class RabinKarp : public StringMatching {
  int powerValue, primeNumber, numberOfDigits, i, j;
  int modOfSearchString, modOfDataString;
  int mod(string stringForMod, int lengthOfString) {
    int modValue = 0;
    for (i = 0; i < lengthOfString; i++) {
      modValue = (numberOfDigits * modValue + stringForMod[i]) % primeNumber;
    }
    return modValue;
  }

 public:
  RabinKarp(string dataString, string searchString)
      : StringMatching(dataString, searchString) {
    numberOfDigits = 128;
    primeNumber = 1011;
    powerValue =
        (int)pow(numberOfDigits, lengthOfSearchString - 1) % primeNumber;
  }

  void findMatches() {
    // generate p
    modOfSearchString = mod(searchString, lengthOfSearchString);
    // generate t0
    modOfDataString = mod(dataString, lengthOfSearchString);

    for (i = 0; i < lengthOfDataString - lengthOfSearchString + 1; i++) {
      if (modOfDataString == modOfSearchString) {
        for (j = 0; j < lengthOfSearchString; j++) {
          if (dataString[i + j] != searchString[j]) {
            break;
          }
        }
        if (j == lengthOfSearchString) {
          printMessage(i);
          totalMatches++;
        }
      }
      if (i < lengthOfDataString - lengthOfSearchString) {
        // calculate t(i+1)
        modOfDataString -= (dataString[i] * powerValue);
        modOfDataString *= numberOfDigits;
        modOfDataString += dataString[i + lengthOfSearchString];
        modOfDataString %= primeNumber;
        if (modOfDataString < 0) modOfDataString += primeNumber;
      }
    }
    cout << "Total matches: " << totalMatches << endl;
  }
};

int main() {
  string dataString, searchString;
  cout << "Enter search string: ";
  getline(cin, searchString);
  cout << "Enter data string: ";
  getline(cin, dataString);
  cout << "1. Rabin Karp Algorithm" << endl;
  StringMatching *stringMatching = new RabinKarp(dataString, searchString);
  stringMatching->findMatches();

  return 0;
}
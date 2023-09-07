#include <bits/stdc++.h>
#include <stringMatching.h>

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

class FiniteAutomaton : public StringMatching {
  vector<map<int, int>> transitionTable;
  set<int> characters;
  int i, j;

  bool isNotSameSuffix(int currState, int currValue, int currCharacter) {
    if (0 == currValue) return false;
    string currSuffix;
    if (currState == 0) return searchString[0] != currCharacter;
    currSuffix = searchString.substr(currState - currValue + 1, currValue - 1) +
                 (char)currCharacter;
    string currPrefix = searchString.substr(0, currValue);
    return currSuffix != currPrefix;
  }
  void generateTransitionTable() {
    int currValue;

    for (int currState = 0; currState <= lengthOfSearchString; currState++) {
      for (int currCharacter : characters) {
        // k is currValue
        currValue = min(lengthOfSearchString + 1, currState + 2);
        do {
          currValue--;
        } while (isNotSameSuffix(currState, currValue, currCharacter));
        transitionTable[currState].insert({currCharacter, currValue});
      }
    }
  }

 public:
  FiniteAutomaton(string dataString, string searchString)
      : StringMatching(dataString, searchString) {
    transitionTable.resize(lengthOfSearchString + 1);
    for (char a : searchString) characters.insert(a);
  }

  void findMatches() {
    generateTransitionTable();
    int state = 0;
    for (i = 0; i < lengthOfDataString; i++) {
      state = transitionTable[state][dataString[i]];
      if (state == lengthOfSearchString) {
        printMessage(i - lengthOfSearchString + 1);
        totalMatches++;
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
  cout << "Enter Which Algorithm you want to use: " << endl;
  cout << "1. Rabin Karp Algorithm" << endl;
  cout << "2. Finite Automaton Algorithm" << endl << "Enter your choice: ";
  int choice;
  cin >> choice;
  StringMatching *stringMatching;

  if (choice == 1) {
    stringMatching = new RabinKarp(dataString, searchString);
  } else if (choice == 2) {
    stringMatching = new FiniteAutomaton(dataString, searchString);
  } else {
    cout << "Wrong Choice" << endl;
    return 0;
  }

  stringMatching->findMatches();

  return 0;
}
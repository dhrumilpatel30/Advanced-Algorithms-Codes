#include <../stringMatching.h>
#include <bits/stdc++.h>

using namespace std;

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
  cout << "2. Finite Automaton Algorithm" << endl;
  StringMatching *stringMatching =
      new FiniteAutomaton(dataString, searchString);

  stringMatching->findMatches();

  return 0;
}
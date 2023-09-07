#include <bits/stdc++.h>
#include<stringMatching.h>

using namespace std;

class KnuthMorrisPrattStringMatcher : public StringMatching {
  vector<int> prefixFunction;
  void calculatePrefixFunction() {
    prefixFunction[0] = -1;
    int currMatch = -1;
    for (int i = 1; i < lengthOfSearchString; i++) {
      while (currMatch >= 0 and searchString[currMatch + 1] != searchString[i])
        currMatch = prefixFunction[currMatch];
      if (searchString[currMatch + 1] == searchString[i]) currMatch++;
      prefixFunction[i] = currMatch;
    }
  }

 public:
  KnuthMorrisPrattStringMatcher(string dataString, string searchString)
      : StringMatching(dataString, searchString) {
    prefixFunction.resize(lengthOfSearchString);
    calculatePrefixFunction();
  }
  void findMatches() {
    int currMatch = -1;
    for (int i = 0; i < lengthOfDataString; i++) {
      while (currMatch >= 0 and searchString[currMatch + 1] != dataString[i])
        currMatch = prefixFunction[currMatch];
      if (searchString[currMatch + 1] == dataString[i]) currMatch++;
      if (lengthOfSearchString - 1 == currMatch) {
        printMessage(i - lengthOfSearchString + 1);
        totalMatches++;
        currMatch = prefixFunction[currMatch];
      }
    }
    cout << "Total matches found: " << totalMatches << endl;
  }
};

class ClosestPoints {
  vector<pair<int, int>> points;
  int minDistance;
  pair<int, int> answer;
  int findDistance(pair<int, int> point1, pair<int, int> point2) {
    return pow(point1.first - point2.first, 2) +
           pow(point1.second - point2.second, 2);
  }

 public:
  ClosestPoints(vector<pair<int, int>> points) {
    this->points = points;
    minDistance = INT_MAX;
  }
  void findClosestPoints() {
    for (int i = 0; i < points.size(); i++) {
      for (int j = i + 1; j < points.size(); j++) {
        if (findDistance(points[i], points[j]) < minDistance) {
          minDistance = findDistance(points[i], points[j]);
          answer = {i, j};
        }
      }
    }
    cout << "Minimum distance: " << minDistance << endl;
    cout << "Closest points: (" << points[answer.first].first << ", "
         << points[answer.first].second << "), (" << points[answer.second].first
         << ", " << points[answer.second].second << ")" << endl;
  }
};

int main() {
  string dataString, searchString;
  cout << "Enter search string: ";
  getline(cin, searchString);
  cout << "Enter data string: ";
  getline(cin, dataString);
  KnuthMorrisPrattStringMatcher kmp(dataString, searchString);
  kmp.findMatches();
  cout << endl;
  vector<pair<int, int>> points;
  int n;
  cout << "Enter number of points: ";
  cin >> n;
  cout << "Enter points: " << endl;
  for (int i = 0; i < n; i++) {
    int x, y;
    cin >> x >> y;
    points.push_back({x, y});
  }
  ClosestPoints cp(points);
  cp.findClosestPoints();
  return 0;
}
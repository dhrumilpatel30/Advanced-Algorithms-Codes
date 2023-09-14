#include <bits/stdc++.h>
#define pointType pair<int, int>
#define pointWithSin pair<double, pointType>
using namespace std;

pointType basePoint;
static vector<pointWithSin> points;
class GrahamConvexHull {
 public:
  void findSin(pointWithSin& point) {
    if (point.second == basePoint) return;
    int y = point.second.second - basePoint.second;
    double d = sqrt(pow(point.second.first - basePoint.first, 2) + pow(y, 2));
    double sin = y / d;
    double value;
    if (point.second.first < basePoint.first)
      value = 2 - sin;
    else
      value = sin;
    point.first = value;
  }
  void generateSin() {
    for (pointWithSin& point : points) {
      findSin(point);
    }
  }
  void findBasePoint() {
    int minY = INT_MAX, minX = INT_MAX;
    for (pointWithSin point : points) {
      if (point.second.second < minY) {
        minY = point.second.second;
        minX = point.second.first;
      } else if (point.second.second == minY)
        minX = min(minX, point.second.first);
    }
    basePoint = {minX, minY};
  }

  GrahamConvexHull(vector<pointType> points1) {
    for (pointType point : points1) {
      points.push_back({-1.0, point});
    }
  }
  bool isConvexHull() {
    findBasePoint();
    generateSin();
    sort(points.begin(), points.end());
    vector<pointWithSin> convexHull;

    return false;
  }
};

int main() {
  vector<pointType> pointsInput = {{1, 1}, {1, 3}, {3, 1},  {1, 2},  {2, 1},
                                   {0, 0}, {0, 3}, {-1, 3}, {-1, 1}, {-3, 1}};
  GrahamConvexHull grahamHull(pointsInput);
  grahamHull.isConvexHull();
}

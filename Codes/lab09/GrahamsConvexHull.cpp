#include <bits/stdc++.h>
#define pointType pair<int, int>
#define pointWithSin pair<double, pointType>
using namespace std;

class GrahamConvexHull {
  pointType basePoint;
  vector<pointWithSin> points;
  void generateSin() {
    for (int i = 0; i < points.size(); i++) {
      if (points[i].second == basePoint) continue;
      int y = points[i].second.second - basePoint.second;
      double d =
          sqrt(pow(points[i].second.first - basePoint.first, 2) + pow(y, 2));
      double sin = y / d;
      double value;
      if (points[i].second.first < basePoint.first)
        value = 2 - sin;
      else
        value = sin;
      points[i].first = value;
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
  int direction(pointType p1, pointType p2, pointType p3) {
    return (p3.first - p1.first) * (p2.second - p1.second) -
           (p2.first - p1.first) * (p3.second - p1.second);
  }

 public:
  GrahamConvexHull(vector<pointType> points1) {
    for (pointType point : points1) {
      points.push_back({-1.0, point});
    }
  }
  vector<pointWithSin> getConvexHull() {
    findBasePoint();
    generateSin();
    sort(points.begin(), points.end());
    vector<pointWithSin> convexHull;
    if (3 > points.size()) return points;
    convexHull.push_back(points[0]);
    convexHull.push_back(points[1]);
    convexHull.push_back(points[2]);
    pointWithSin nextTop;
    pointWithSin top;
    for (int i = 3; i < points.size(); i++) {
      while (convexHull.size() > 1) {
        nextTop = convexHull[convexHull.size() - 2];
        top = convexHull[convexHull.size() - 1];
        if (direction(top.second, nextTop.second, points[i].second) < 0)
          convexHull.pop_back();
        else
          break;
      }
      convexHull.push_back(points[i]);
    }
    return convexHull;
  }
};

int main() {
  //   vector<pointType> pointsInput = {{0, 3}, {1, 1}, {2, 2}, {4, 4},
  //    {0, 0}, {1, 2}, {3, 1}, {3, 3}};
  vector<pointType> pointsInput = {
      {-7, 8},  {-4, 6},  {2, 6},  {6, 4},   {8, 6},   {7, -2},
      {4, -6},  {8, -7},  {0, 0},  {3, -2},  {6, -10}, {0, -6},
      {-9, -5}, {-8, -2}, {-8, 0}, {-10, 3}, {-2, 2},  {-10, 4}};
  GrahamConvexHull grahamHull(pointsInput);
  vector<pointWithSin> convexHull = grahamHull.getConvexHull();
  for (pointWithSin point : convexHull) {
    cout << "(" << point.second.first << ", " << point.second.second << ")"
         << endl;
  }
  return 0;
}

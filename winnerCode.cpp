#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>

struct Point {
    int x;
    int y;
};

double calculateDistance(const Point& p1, const Point& p2) {
    return std::sqrt(std::pow(p2.x - p1.x, 2) + std::pow(p2.y - p1.y, 2));
}

/// @brief This function starting from a point, calculates the distance with all the points and choose the closest one 
/// it will do till it reaches an endpoint, an endpoint can be the fact that we reached the maximum distance , or the fact that there is no nextPoint
/// @param distanceMax 
/// @param points 
/// @param currentPoint 
/// @return 
std::vector<int> findApproximateSolution(double distanceMax, const std::vector<Point>& points, int currentPoint) {
    int numPoints = points.size();
    std::vector<bool> visited(numPoints, false);
    std::vector<int> path;


    path.push_back(currentPoint);
    visited[currentPoint] = true;

    double currentDistance = 0.0;

    while (true) {
        double minDistance = std::numeric_limits<double>::max();
        int nextPoint = -1;

        // Find the closest unvisited point within the maximum distance
        for (int i = 0; i < numPoints; ++i) {
            if (!visited[i]) {
                double distance = calculateDistance(points[currentPoint], points[i]);
                if (distance <= distanceMax && distance < minDistance) {
                    minDistance = distance;
                    nextPoint = i;
                }
            }
        }

        // If no point found or distance exceeds maximum, stop the iteration
        if (nextPoint == -1 || currentDistance + minDistance > distanceMax) {
            break;
        }

        path.push_back(nextPoint);
        visited[nextPoint] = true;
        currentPoint = nextPoint;
        currentDistance += minDistance;
    }

    return path;
}

int main() {
    // Here we are reading the input from the file
    std::ifstream inputFile("input.txt");
    if (!inputFile) {
        std::cerr << "Error opening the input file." << std::endl;
        return 1;
    }

    // reading the maximum distance and the number of points
    double distanceMax;
    int numPoints;
    inputFile >> distanceMax >> numPoints;

    // reading the parameters of the points
    std::vector<Point> points(numPoints);
    for (int i = 0; i < numPoints; ++i) {
        inputFile >> points[i].x >> points[i].y;
    }

    inputFile.close();

    // max will contain the size of the approximate output in the end
    // maxIndex will be used to find the best start point
    int max =0;
    int maxIndex = 0;
    // iterating through all the points and applying the algorithm for each point as a start point
    for(int i=0; i< numPoints; i++){
    std::vector<int> approximateSolution = findApproximateSolution(distanceMax, points, i);
    // calculating the maximum number of points obtained and the equivalent index for the start point
    if(max < approximateSolution.size()){
     max = approximateSolution.size();
     maxIndex = i;
     }
    }

    // after finding the best start point , calculating the possible points and output
    std::vector<int> approximateSolution = findApproximateSolution(distanceMax, points, maxIndex);
    for (int index : approximateSolution) {
        std::cout << index << " ";
    }
    std::cout << std::endl;
    std::cout << approximateSolution.size() << std::endl;
    return 0;
}

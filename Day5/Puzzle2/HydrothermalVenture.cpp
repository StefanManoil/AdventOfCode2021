#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
/*
--- Day 5: Hydrothermal Venture ---
You come across a field of hydrothermal vents on the ocean floor! These vents constantly produce large, opaque clouds, so it would be best to avoid them if possible.

They tend to form in lines; the submarine helpfully produces a list of nearby lines of vents (your puzzle input) for you to review. For example:

0,9 -> 5,9
8,0 -> 0,8
9,4 -> 3,4
2,2 -> 2,1
7,0 -> 7,4
6,4 -> 2,0
0,9 -> 2,9
3,4 -> 1,4
0,0 -> 8,8
5,5 -> 8,2
Each line of vents is given as a line segment in the format x1,y1 -> x2,y2 where x1,y1 are the coordinates of one end the line segment and x2,y2 are the coordinates of the other end. These line segments include the points at both ends. In other words:

An entry like 1,1 -> 1,3 covers points 1,1, 1,2, and 1,3.
An entry like 9,7 -> 7,7 covers points 9,7, 8,7, and 7,7.
For now, only consider horizontal and vertical lines: lines where either x1 = x2 or y1 = y2.

So, the horizontal and vertical lines from the above list would produce the following diagram:

.......1..
..1....1..
..1....1..
.......1..
.112111211
..........
..........
..........
..........
222111....
In this diagram, the top left corner is 0,0 and the bottom right corner is 9,9. Each position is shown as the number of lines which cover that point or . if no line covers that point. The top-left pair of 1s, for example, comes from 2,2 -> 2,1; the very bottom row is formed by the overlapping lines 0,9 -> 5,9 and 0,9 -> 2,9.

To avoid the most dangerous areas, you need to determine the number of points where at least two lines overlap. In the above example, this is anywhere in the diagram with a 2 or larger - a total of 5 points.

Consider only horizontal and vertical lines. At how many points do at least two lines overlap?
*/

int main() {
    std::ifstream myFile("input.txt");
    if (myFile.is_open()) {
        std::string currentLine;
        int **lineGrid = new int*[1000];
        for (int i = 0; i < 1000; i++) {
            lineGrid[i] = new int[1000];
            for (int j = 0; j < 1000; j++) {
                lineGrid[i][j] = 0;
            }
        }
        int countOverlap = 0;
        while (std::getline(myFile, currentLine)) {
            std::istringstream currentLineStream(currentLine);
            char comma;
            int x1, x2, y1, y2;
            std::string arrow;
            currentLineStream >> x1 >> comma >> y1 >>  arrow >> x2 >> comma >> y2;
            if (x1 == x2) {
                int minY = std::min(y1, y2);
                for (int i = minY; i <= std::max(y1, y2); i++) {
                    if (lineGrid[i][x1] == 1) {
                        countOverlap++;
                    }
                    lineGrid[i][x1]++;
                }
            }
            else if (y1 == y2) {
                int minX = std::min(x1, x2);
                for (int i = minX; i <= std::max(x1, x2); i++) {
                    if (lineGrid[y1][i] == 1) {
                        countOverlap++;
                    }
                    lineGrid[y1][i]++;
                }
            }
            else {
                int xIncrement;
                int yIncrement;
                if (x1 > x2) {
                    xIncrement = 1;
                }
                else {
                    xIncrement = -1;
                }
                if (y1 > y2) {
                    yIncrement = 1;
                }
                else {
                    yIncrement = -1;
                }
                int difference = abs(x1 - x2);
                for (int i = 0; i <= difference; i++) {
                    if (lineGrid[y1 - (yIncrement * i)][x1 - (xIncrement * i)] == 1) {
                        countOverlap++;
                    }
                    lineGrid[y1 - (yIncrement * i)][x1 - (xIncrement * i)]++;
                }
            }
        }
        std::cout << "The number of points where at least two lines overlap: " << countOverlap << std::endl;
        for (int i = 0; i < 1000; i++) {
            delete[] lineGrid[i];
        }
        delete[] lineGrid;
    }
    else {
        std::cerr << "Unable to open file." << std::endl;
        return 1;
    }
}
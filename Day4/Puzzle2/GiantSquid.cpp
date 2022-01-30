#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <utility>
/*
--- Day 4: Giant Squid ---
--- Part Two ---
On the other hand, it might be wise to try a different strategy: let the giant squid win.

You aren't sure how many bingo boards a giant squid could play at once, so rather than waste time counting its arms, the safe thing to do is to figure out which board will win last and choose that one. That way, no matter which boards it picks, it will win for sure.

In the above example, the second board is the last to win, which happens after 13 is eventually called and its middle column is completely marked. If you were to keep playing until this point, the second board would have a sum of unmarked numbers equal to 148 for a final score of 148 * 13 = 1924.

Figure out which board will win last. Once it wins, what would its final score be?
*/

int main () {
    std::ifstream myFile("input.txt");
    if (myFile.is_open()) {
        std::string currentLine;
        char comma;
        int numberDrawn;
        std::vector<int> numbersToDraw;
        // parse the number draws
        std::getline(myFile, currentLine);
        std::istringstream currentLineStream(currentLine);
        while (currentLineStream >> numberDrawn) {
            numbersToDraw.emplace_back(numberDrawn);
            currentLineStream >> comma;
        }
        // parse the grids themselves, find a winner
        int drawnPosition = 0;
        int winningBoardSumUnmarkedNumbers = 0;
        int winningBoardLastDrawnNumberMarked;
        while (true) {
            backToWhile:
            int sumUnmarkedNumbers = 0;
            int currentNumberOnBoard;
            bool numbersMarkedInCurrentGrid[5][5];
            std::unordered_map<int, std::pair<int, int>> boardNumsAndPos;
            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 5; j++) {
                    //myFile >> currentNumberOnBoard;
                    if (!(myFile >> currentNumberOnBoard)) {
                        goto afterWhile;
                    }
                    numbersMarkedInCurrentGrid[i][j] = false;
                    sumUnmarkedNumbers += currentNumberOnBoard;
                    boardNumsAndPos.emplace(currentNumberOnBoard, std::make_pair(i, j));
                }
            }
            for (int i = 0; i < numbersToDraw.size(); i++) {
                if (boardNumsAndPos.count(numbersToDraw[i]) > 0) {
                    int rowPos = boardNumsAndPos[numbersToDraw[i]].first;
                    int colPos = boardNumsAndPos[numbersToDraw[i]].second;
                    numbersMarkedInCurrentGrid[rowPos][colPos] = true;
                    sumUnmarkedNumbers -= numbersToDraw[i];
                    // check if row of drawn number is marked
                    bool rowMarked = false;
                    for (int k = 0; k < 5; k++) {
                        if (numbersMarkedInCurrentGrid[rowPos][k] == false) {
                            break;
                        }
                        else if (k == 4) {
                            rowMarked = true;
                        }
                    }
                    if (rowMarked) {
                        if (i > drawnPosition) {
                            drawnPosition = i;
                            winningBoardSumUnmarkedNumbers = sumUnmarkedNumbers;
                            winningBoardLastDrawnNumberMarked = numbersToDraw[i];
                        }
                        goto backToWhile;
                    }
                    else {
                        // check if col of drawn number is marked
                        for (int k = 0; k < 5; k++) {
                            if (numbersMarkedInCurrentGrid[k][colPos] == false) {
                                break;
                            }
                            else if (k == 4) {
                                if (i > drawnPosition) {
                                    drawnPosition = i;
                                    winningBoardSumUnmarkedNumbers = sumUnmarkedNumbers;
                                    winningBoardLastDrawnNumberMarked = numbersToDraw[i];
                                }
                                goto backToWhile;
                            }
                        }
                    }
                }
            }
        }
        afterWhile:
        int scoreOfWinningBoard = winningBoardSumUnmarkedNumbers * winningBoardLastDrawnNumberMarked;
        std::cout << "The winning board has a score of: " << scoreOfWinningBoard << std::endl;
    }
    else {
        std::cerr << "Unable to open file." << std::endl;
        return 1;
    }
}
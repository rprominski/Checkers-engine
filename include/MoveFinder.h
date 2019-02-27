//
// Created by rafal on 27.02.19.
//

#ifndef HECKERS_ENGINE_MOVEFINDER_H
#define HECKERS_ENGINE_MOVEFINDER_H

#include <string>
#include <vector>
#include "PositionRater.h"

class MoveFinder {
    std::vector<std::vector<int>> moves;
    std::vector<int> bestMove;
    int blackPawns = 12, whitePawns = 12;
    int maxDepth;

    bool isLegal(int x, int y, std::string position, bool emptyField);

    std::string getNewPositionForMen(std::string position, int xDirection, int yDirection, char color, int field);

    void findCapturesForMen(std::string position, int field, std::vector<int> menMoves);

    void checkDirectionForCapture(std::string position, int field, int xDirection, int yDirection, char color,
                                  std::vector<int> kingMoves);

    void findCapturesForKing(std::string position, int field, std::vector<int> kingMoves);

    void findCaptures(std::string position, char color);

    void findMovesForMen(std::string position, char color);

    void checkDirectionForMove(std::string position, int field, int xDirection, int yDirection);

    void findMovesForKings(std::string position, char color);

    std::string deleteDirection(std::string position, int first, int last);

    char changeColor(char color);

public:

    std::string getPositionAfterMove(std::string position, std::vector<int> move);

    void countPawns(std::string position);

    double findBestMove(std::string position, char color, int depth);

    std::vector<std::vector<int> > findMoves(std::string position, char color);

    bool noPawns();

    std::vector<int> getBestMove();

    void setMaxDepth(int maxDepth);
};


#endif //HECKERS_ENGINE_MOVEFINDER_H

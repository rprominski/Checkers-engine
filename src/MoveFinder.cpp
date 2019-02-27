//
// Created by rafal on 27.02.19.
//

#include "../include/MoveFinder.h"

bool MoveFinder::isLegal(int x, int y, std::string position, bool emptyField) {
    if (x < 0 || y < 0 || x > 7 || y > 7)
        return false;

    if (emptyField && position[x + y * 8] != 'x')
        return false;

    return true;
}

std::string
MoveFinder::getNewPositionForMen(std::string position, int xDirection, int yDirection, char color, int field) {
    int x, y;

    x = field % 8;
    y = (field - x) / 8;

    if (color == 'b') {
        if (!(isLegal(x + (xDirection * 2), y + (yDirection * 2), position, 1) &&
              (position[field + (8 * yDirection + xDirection)] == 'c' ||
               position[field + (8 * yDirection + xDirection)] == 'C')))
            return "";

        else {
            position[field + (8 * yDirection + xDirection)] = 'x';
            position[field + 2 * (8 * yDirection + xDirection)] = position[field];
            position[field] = 'x';
            return position;
        }
    }

    if (color == 'c') {
        if (!(isLegal(x + (xDirection * 2), y + (yDirection * 2), position, 1) &&
              (position[field + (8 * yDirection + xDirection)] == 'b' ||
               position[field + (8 * yDirection + xDirection)] == 'B')))
            return "";

        else {
            position[field + (8 * yDirection + xDirection)] = 'x';
            position[field + 2 * (8 * yDirection + xDirection)] = position[field];
            position[field] = 'x';
            return position;
        }
    }
    return "";
}

void MoveFinder::findCapturesForMen(std::string position, int field, std::vector<int> menMoves) {
    menMoves.push_back(field);
    int x, y;
    char color = position[field];

    if (getNewPositionForMen(position, -1, -1, color, field) != "")
        findCapturesForMen(getNewPositionForMen(position, -1, -1, color, field), field - 18, menMoves);

    if (getNewPositionForMen(position, -1, +1, color, field) != "")
        findCapturesForMen(getNewPositionForMen(position, -1, +1, color, field), field + 14, menMoves);

    if (getNewPositionForMen(position, +1, -1, color, field) != "")
        findCapturesForMen(getNewPositionForMen(position, +1, -1, color, field), field - 14, menMoves);

    if (getNewPositionForMen(position, +1, +1, color, field) != "")
        findCapturesForMen(getNewPositionForMen(position, +1, +1, color, field), field + 18, menMoves);

    if (moves.size() == 0 && menMoves.size() != 0)
        moves.push_back(menMoves);
    else {
        if (moves[0].size() == menMoves.size())
            moves.push_back(menMoves);

        if (moves[0].size() < menMoves.size()) {
            moves.clear();
            moves.push_back(menMoves);
        }
    }
}

void MoveFinder::checkDirectionForCapture(std::string position, int field, int xDirection, int yDirection, char color,
                                          std::vector<int> kingMoves) {
    bool capture = 0;
    int captureField, x, y;
    x = field % 8;
    y = (field - x) / 8;

    if (color == 'B') {
        for (int i = 1; i < 8; i++) {
            if (!isLegal(x + i * xDirection, y + i * yDirection, position, 0))
                break;

            if (position[field + i * (yDirection * 8 + xDirection)] == 'c' ||
                position[field + i * (yDirection * 8 + xDirection)] == 'C') {
                capture = 1;
                captureField = field + i * (yDirection * 8 + xDirection);
                i++;
            }

            if (capture) {
                if (!isLegal(x + xDirection * i, y + yDirection * i, position, 1))
                    break;

                std::string newPosition = position;
                newPosition[field + i * (yDirection * 8 + xDirection)] = 'B';
                newPosition[captureField] = 'x';
                newPosition[field] = 'x';
                findCapturesForKing(newPosition, field + i * (yDirection * 8 + xDirection), kingMoves);
            }
        }
    }

    if (color == 'C') {
        for (int i = 1; i < 8; i++) {
            if (!isLegal(x + i * xDirection, y + i * yDirection, position, 0))
                break;

            if (position[field + i * (yDirection * 8 + xDirection)] == 'b' ||
                position[field + i * (yDirection * 8 + xDirection)] == 'B') {
                capture = 1;
                captureField = field + i * (yDirection * 8 + xDirection);
                i++;
            }

            if (capture) {
                if (!isLegal(x + xDirection * i, y + yDirection * i, position, 1))
                    break;

                std::string newPosition = position;
                newPosition[field + i * (yDirection * 8 + xDirection)] = 'C';
                newPosition[captureField] = 'x';
                newPosition[field] = 'x';
                findCapturesForKing(newPosition, field + i * (yDirection * 8 + xDirection), kingMoves);
            }
        }
    }
}

void MoveFinder::findCapturesForKing(std::string position, int field, std::vector<int> kingMoves) {
    kingMoves.push_back(field);
    int x, y, captureField;
    char color = position[field];
    bool capture;
    std::string newPosition;

    checkDirectionForCapture(position, field, -1, -1, color, kingMoves);
    checkDirectionForCapture(position, field, -1, +1, color, kingMoves);
    checkDirectionForCapture(position, field, +1, -1, color, kingMoves);
    checkDirectionForCapture(position, field, +1, +1, color, kingMoves);

    if (moves.size() == 0 && kingMoves.size() != 0)
        moves.push_back(kingMoves);
    else {
        if (moves[0].size() == kingMoves.size())
            moves.push_back(kingMoves);

        if (moves[0].size() < kingMoves.size()) {
            moves.clear();
            moves.push_back(kingMoves);
        }
    }
}

void MoveFinder::findCaptures(std::string position, char color) {
    for (int i = 0; i < position.size(); i++) {
        if ((position[i] == 'b' || position[i] == 'c') && position[i] == color)
            findCapturesForMen(position, i, std::vector<int>());

        if ((position[i] == 'B' || position[i] == 'C') && position[i] == (color - 32))
            findCapturesForKing(position, i, std::vector<int>());
    }
}

void MoveFinder::findMovesForMen(std::string position, char color) {
    for (int i = 0; i < position.size(); i++) {
        int x, y;
        x = i % 8;
        y = (i - x) / 8;

        if (position[i] == 'c' && position[i] == color) {

            if (isLegal(x - 1, y + 1, position, 1))
                moves.push_back(std::vector<int>{i, i + 7});

            if (isLegal(x + 1, y + 1, position, 1))
                moves.push_back(std::vector<int>{i, i + 9});
        }

        if (position[i] == 'b' && position[i] == color) {
            if (isLegal(x + 1, y - 1, position, 1))
                moves.push_back(std::vector<int>{i, i - 7});

            if (isLegal(x - 1, y - 1, position, 1))
                moves.push_back(std::vector<int>{i, i - 9});
        }
    }
}

void MoveFinder::checkDirectionForMove(std::string position, int field, int xDirection, int yDirection) {
    int x, y;
    x = field % 8;
    y = (field - x) / 8;

    for (int i = 1; i < 8; i++) {
        if (isLegal(x + i * xDirection, y + i * yDirection, position, 1))
            moves.push_back(std::vector<int>{field, field + i * (8 * yDirection + xDirection)});
        else
            return;
    }
}

void MoveFinder::findMovesForKings(std::string position, char color) {
    for (int i = 0; i < position.size(); i++) {
        if (color == position[i]) {
            checkDirectionForMove(position, i, -1, -1);
            checkDirectionForMove(position, i, -1, +1);
            checkDirectionForMove(position, i, +1, -1);
            checkDirectionForMove(position, i, +1, +1);
        }
    }
}

std::string MoveFinder::deleteDirection(std::string position, int first, int last) {
    int direction;
    direction = (((first - last) % 9 == 0) ? 9 : 7);
    direction *= ((first - last < 0) ? -1 : 1);

    position[last] = position[first];

    while (first != last) {
        position[first] = 'x';
        first -= direction;
    }
    return position;
}

char MoveFinder::changeColor(char color) {
    if (color == 'b')
        return 'c';

    if (color == 'c')
        return 'b';

    if (color == 'B')
        return 'C';

    if (color == 'C')
        return 'B';
}

std::string MoveFinder::getPositionAfterMove(std::string position, std::vector<int> move) {
    for (int i = 0; i < move.size() - 1; i++) {
        position = deleteDirection(position, move[i], move[i + 1]);
    }
    for (int i = 0; i < 8; i++)
        if (position[i] == 'b')
            position[i] = 'B';

    for (int i = 56; i < 64; i++)
        if (position[i] == 'c')
            position[i] = 'C';

    return position;
}

void MoveFinder::countPawns(std::string position) {
    whitePawns = 0;
    blackPawns = 0;
    for (int i = 0; i < position.size(); i++) {
        if (position[i] == 'c' || position[i] == 'C')
            blackPawns++;
        if (position[i] == 'b' || position[i] == 'B')
            whitePawns++;
    }
}

double MoveFinder::findBestMove(std::string position, char color, int depth) {
    double result = (color == 'b' ? -1000 : 1000);
    std::vector<std::vector<int>> currentMoves = findMoves(position, color);

    if (depth == 0 && currentMoves.size() != 0) {
        bestMove = currentMoves[0];
    }
    if (depth == maxDepth) {
        PositionRater positionRater;
        return positionRater.ratePosition(position);
    } else {
        for (int i = 0; i < currentMoves.size(); i++) {
            double d;
            d = findBestMove(getPositionAfterMove(position, currentMoves[i]), changeColor(color), depth + 1);

            if (color == 'b' || color == 'B') {
                if (d > result) {
                    if (depth == 0)
                        bestMove = currentMoves[i];

                    result = d;
                }
            }

            if (color == 'c' || color == 'C') {
                if (d < result) {
                    if (depth == 0) {
                        bestMove = currentMoves[i];
                    }
                    result = d;
                }
            }
        }
    }
    return result;
}

std::vector<std::vector<int>> MoveFinder::findMoves(std::string position, char color) {
    moves.clear();
    findCaptures(position, color);
    if (moves[0].size() == 1) {
        moves.clear();
    }
    if (moves.size() == 0) {
        findMovesForMen(position, color);
        findMovesForKings(position, color - 32);
    }
    return moves;
}

bool MoveFinder::noPawns() {
    if (whitePawns == 0 || blackPawns == 0) {
        return true;
    }
    return false;
}

std::vector<int> MoveFinder::getBestMove() {
    return bestMove;
}

void MoveFinder::setMaxDepth(int maxDepth) {
    MoveFinder::maxDepth = maxDepth;
}

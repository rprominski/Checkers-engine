//
// Created by rafal on 27.02.19.
//

#include "../include/PositionRater.h"
#include <string>

double PositionRater::fieldBonus(char color, double bonus) {
    if (color == 'c' || color == 'C') {
        return -bonus;
    }
    if (color == 'b' || color == 'B') {
        return bonus;
    }
    return 0.0;
}

double PositionRater::positionBonus(std::string position) {
    double result = 0;
    int bonus1[14] = {1, 3, 5, 7, 8, 23, 24, 39, 40, 55, 56, 58, 60, 62};
    int bonus2[10] = {10, 12, 14, 17, 30, 33, 46, 49, 51, 53};
    int bonus3[8] = {19, 21, 26, 28, 35, 37, 42, 44};

    for (int i : bonus1) {
        result += fieldBonus(position[i], 0.4);
    }

    for (int i : bonus2) {
        result += fieldBonus(position[i], 0.75);
    }

    for (int i : bonus3) {
        result += fieldBonus(position[i], 1);
    }

    for (int i = 0; i < 8; i++) {
        result += ((position[i] == 'c') ? -0.1 : (position[i] == 'b' ? 0.1 : 0));
    }

    for (int i = 8; i < 16; i++) {
        result += ((position[i] == 'c') ? -0.1 : (position[i] == 'b' ? 0.5 : 0));
    }

    for (int i = 16; i < 24; i++) {
        result += ((position[i] == 'c') ? -0.2 : (position[i] == 'b' ? 0.4 : 0));
    }

    for (int i = 24; i < 32; i++) {
        result += ((position[i] == 'c') ? -0.2 : (position[i] == 'b' ? 0.3 : 0));
    }

    for (int i = 32; i < 40; i++) {
        result += ((position[i] == 'c') ? -0.3 : (position[i] == 'b' ? 0.2 : 0));
    }

    for (int i = 40; i < 48; i++) {
        result += ((position[i] == 'c') ? -0.4 : (position[i] == 'b' ? 0.2 : 0));
    }

    for (int i = 48; i < 56; i++) {
        result += ((position[i] == 'c') ? -0.5 : (position[i] == 'b' ? 0.1 : 0));
    }

    for (int i = 56; i < 64; i++) {
        result += ((position[i] == 'c') ? 0 : (position[i] == 'b' ? 0.1 : 0));
    }

    return result;
}

double PositionRater::materialBonus(std::string position) {
    double result = 0;

    for (int i = 0; i < 64; i++) {
        if (position[i] == 'c' || position[i] == 'b')
            result += fieldBonus(position[i], 4);

        else
            result += fieldBonus(position[i], 20);
    }

    for (int i = 0; i < 8; i++) {
        if (position[i] == 'b')
            result += fieldBonus(position[i], 16);
    }

    for (int i = 56; i < 64; i++) {
        if (position[i] == 'c') {
            result += fieldBonus(position[i], 16);
        }
    }

    return result;
}


double PositionRater::ratePosition(std::string position) {
    return positionBonus(position) + materialBonus(position);
}

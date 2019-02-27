//
// Created by rafal on 27.02.19.
//

#ifndef HECKERS_ENGINE_POSITIONRATER_H
#define HECKERS_ENGINE_POSITIONRATER_H

#include <string>

class PositionRater
{
    double fieldBonus(char color, double bonus);

    double positionBonus(std::string position);

    double materialBonus(std::string position);

public:
    double ratePosition(std::string position);

};
#endif //HECKERS_ENGINE_POSITIONRATER_H
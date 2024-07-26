#pragma once
#include "GroupingStrategy.h"

class DistanceGroupingStrategy : public GroupingStrategy 
{
private:
    float startX;
    float startY;
public:
    DistanceGroupingStrategy():startX(.0f), startY(.0f) {}
    DistanceGroupingStrategy(float startX, float startY):startX(startX), startY(startY) {}

    Comparator getComparator() override;
    void groupObjects(const std::vector<Object>& objects, std::vector<Group>& groups) override;

    // Реализация функции для вычисления расстояния
    float calculateDistance(float x, float y);
};


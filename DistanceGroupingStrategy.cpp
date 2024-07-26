#include <cmath>
#include <iostream>
#include "DistanceGroupingStrategy.h"

Comparator DistanceGroupingStrategy::getComparator()
{
    auto calculateDistanceFunc = [this](float x, float y) 
    {
        return calculateDistance(x, y);
    };

    return Comparator(SortingCriterion::Distance, this->sortDirection, calculateDistanceFunc);
}

void DistanceGroupingStrategy::groupObjects(const std::vector<Object>& objects, std::vector<Group>& groups)
{
    Group* distanceGroup = findGroupByName(groups, "Расстояние");

    if (!distanceGroup) 
    {
        // Группа "Расстояние" не найдена, обработка ошибки
        throw std::runtime_error("Группа 'Расстояние' не найдена.");
    }

    Comparator distanceComparator = getComparator();

    for (Object obj : objects) 
    {
        float distance = calculateDistance(obj.getCoordinateX(), obj.getCoordinateY());

        // Выбор подгруппы на основе расстояния
        std::string subgroupName;
        if (distance < 100) 
        {
            subgroupName = "До 100 ед.";
        }
        else if (distance < 1000) 
        {
            subgroupName = "До 1000 ед.";
        }
        else if (distance < 10000) 
        {
            subgroupName = "До 10000 ед.";
        }
        else 
        {
            subgroupName = "Слишком далеко";
        }

        Subgroup* subgroup = distanceGroup->getSubgroup(subgroupName);
        if (!subgroup) 
        {
            distanceGroup->addSubgroup(subgroupName, distanceComparator);
            subgroup = distanceGroup->getSubgroup(subgroupName);
        }

        subgroup->addObject(obj);
    }
}

float DistanceGroupingStrategy::calculateDistance(float x, float y)
{
	float deltaX = x - this->startX;
	float deltaY = y - this->startY;

	return sqrt(deltaX * deltaX + deltaY * deltaY);
}

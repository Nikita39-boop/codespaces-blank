#pragma once
#include "Object.h"
#include <functional>

enum class SortingCriterion
{
    Name,
    Distance,
    Type,
    Date
};

enum class SortDirection
{
    Ascending,
    Descending
};

class Comparator
{
private:
    SortingCriterion sortingCriterion;
    SortDirection sortDirection;
    std::function<float(float, float)> calculateDistance;
public:
    Comparator() = default;
    Comparator(const SortingCriterion& sortingCriterion, const SortDirection& sortDirection)
        : sortingCriterion(sortingCriterion), sortDirection(sortDirection), calculateDistance(nullptr) {}
    Comparator(const SortingCriterion& sortingCriterion, const SortDirection& sortDirection, std::function<float(float, float)> calculateDistanceFunc)
        : sortingCriterion(sortingCriterion), sortDirection(sortDirection), calculateDistance(calculateDistanceFunc) {}

    bool operator()(const Object& obj1, const Object& obj2) const;

    // Вспомогательная функция для сравнения полей объектов
    template <typename T>
    bool compareByField(const T& field1, const T& field2) const;
};

template<typename T>
inline bool Comparator::compareByField(const T& field1, const T& field2) const
{
    if (sortDirection == SortDirection::Ascending) 
    {
        return field1 < field2;
    }
    else 
    {
        return field1 > field2;
    }
}

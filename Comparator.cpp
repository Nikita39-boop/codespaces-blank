#include "Comparator.h"

bool Comparator::operator()(const Object& obj1, const Object& obj2) const
{
    switch (sortingCriterion) 
    {
        case SortingCriterion::Name:
            return compareByField(obj1.getName(), obj2.getName());
        case SortingCriterion::Distance:
        {
            float distance1 = calculateDistance(obj1.getCoordinateX(), obj1.getCoordinateY());
            float distance2 = calculateDistance(obj2.getCoordinateX(), obj2.getCoordinateY());

            return compareByField(distance1, distance2);
        }
        case SortingCriterion::Type:
            return compareByField(obj1.getType(), obj2.getType());
        case SortingCriterion::Date:
            return compareByField(obj1.getDate(), obj2.getDate());
        default:
            return false;
    }
}

#pragma once
#include "GroupingStrategy.h"

class TypeGroupingStrategy : public GroupingStrategy
{
private:
    int minimumNumberOfTypeObjects;
public:
    TypeGroupingStrategy():minimumNumberOfTypeObjects(1) {};
    TypeGroupingStrategy(int minNumber):minimumNumberOfTypeObjects(minNumber) {}

    Comparator getComparator() override;
    void groupObjects(const std::vector<Object>& objects, std::vector<Group>& groups) override;
};


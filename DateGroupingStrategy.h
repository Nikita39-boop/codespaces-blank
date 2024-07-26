#pragma once
#include "GroupingStrategy.h"

class DateGroupingStrategy : public GroupingStrategy 
{
public:
    Comparator getComparator() override;
    void groupObjects(const std::vector<Object>& objects, std::vector<Group>& groups) override;
};

